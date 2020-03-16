#pragma once
#include <math.h>
#include "TrajectoryPoint.h"

class Trajectory
{
	float X0 = 0;
	float X1 = 0;

	float V0 = 0;
	float V1 = 0;

	float Vmax = 0;
	float Amax = 0;
	float Jmax = 0;

	float Vlim = 0;
	float Alima = 0;
	float Alimd = 0;

	float Tj1 = 0;
	float Ta = 0;
	float Tv = 0;
	float Td = 0;
	float Tj2 = 0;
	float T = 0;

	float Ratio = 1;

	bool VmaxReached = true;
	bool AmaxReached = true;
	bool AminReached = true;

public:
	Trajectory(float, float, float, float, float, float, float);
	TrajectoryPoint CalculateByTime(float);
	TrajectoryPoint CalculateByProgress(float);
	float ConvertTimetoProgress(float);
	float GetTotalTime();
};

Trajectory::Trajectory(float x0, float x1, float v0, float v1, float v_max, float a_max, float j_max)
{
	X0 = x0;
	X1 = x1;
	V0 = v0;
	V1 = v1;
	const auto delta = x0 > x1;

	if (delta)
	{
		x0 = -x0;
		x1 = -x1;
		v0 = -v0;
		v1 = -v1;
	}

	//Case 1 v_lim = v_max
	if ((v_max - v0) * j_max < a_max * a_max)
	{
		//a_max is not reached
		AmaxReached = false;
		Tj1 = sqrt((v_max - v0) / j_max);
		Ta = 2 * Tj1;
		Alima = j_max * Tj1;
	}
	else
	{
		//a_max is reached
		AmaxReached = true;
		Tj1 = a_max / j_max;
		Ta = Tj1 + (v_max - v0) / a_max;
		Alima = a_max;
	}

	if ((v_max - v1) * j_max < a_max * a_max)
	{
		//a_min is not reached
		AminReached = false;
		Tj2 = sqrt((v_max - v1) / j_max);
		Td = 2 * Tj2;
		Alimd = -j_max * Tj2;
	}
	else
	{
		//a_min is reached
		AminReached = true;
		Tj2 = a_max / j_max;
		Td = Tj2 + (v_max - v1) / a_max;
		Alimd = -a_max;
	}

	Tv = (x1 - x0) / v_max - Ta * (1 + v0 / v_max) / 2 - Td * (1 + v1 / v_max) / 2;

	if (Tv > 0)
	{
		VmaxReached = true;
		Vlim = v_max;

		Vmax = v_max;
		Amax = a_max;
		Jmax = j_max;

		if (delta)
		{
			x0 = -x0;
			x1 = -x1;
			v0 = -v0;
			v1 = -v1;
		}
		T = Ta + Tv + Td;
		return;
	}

	VmaxReached = false;
	Tv = 0;

	float ratio_limit[2] = {0, 1};
	auto first = true;

	for (auto i = 0; i < 10; i++)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			Ratio = (ratio_limit[0] + ratio_limit[1]) / 2;
		}

		const auto tmp_a_max = Ratio * a_max;

		Tj1 = tmp_a_max / j_max;
		Tj2 = Tj1;

		const auto s_del = sqrt(
			(tmp_a_max * tmp_a_max * tmp_a_max * tmp_a_max / (j_max * j_max)) + 2 * (v0 * v0 + v1 * v1) + tmp_a_max * (4 * (x1 - x0) - 2 * (tmp_a_max / j_max) * (v0 + v1)));

		Ta = ((tmp_a_max * tmp_a_max / j_max) - 2 * v0 + s_del) / (2 * tmp_a_max);
		Td = ((tmp_a_max * tmp_a_max / j_max) - 2 * v1 + s_del) / (2 * tmp_a_max);

		if ((Ta < 0 && Td < 0))
		{
			ratio_limit[1] = Ratio;
		}
		else
		{
			if (Ta < 0)
			{
				Tj1 = 0;
				Ta = 0;
				Tj2 = (j_max * (x1 - x0) - sqrt(
											   j_max * (j_max * (x1 - x0) * (x1 - x0) + (v1 + v0) * (v1 + v0) * (v1 - v0)))) /
					  (j_max * (v1 + v0));
				Td = 2 * (x1 - x0) / (v1 + v0);
			}

			if (Td < 0)
			{
				Tj1 = (j_max * (x1 - x0) - sqrt(
											   j_max * (j_max * (x1 - x0) * (x1 - x0) - (v1 + v0) * (v1 + v0) * (v1 - v0)))) /
					  (j_max * (v1 + v0));
				Ta = 2 * (x1 - x0) / (v1 + v0);
				Tj2 = 0;
				Td = 0;
			}

			if (Ta > 2 * Tj1)
			{
				AmaxReached = true;
			}
			else
			{
				AmaxReached = false;
			}

			if (Td > 2 * Tj2)
			{
				AminReached = true;
			}
			else
			{
				AminReached = false;
			}

			if (Ta <= 2 * Tj1 || Td <= 2 * Tj2)
			{
				ratio_limit[1] = Ratio;
			}
			else
			{
				ratio_limit[0] = Ratio;
			}
		}
	}

	Ratio = ratio_limit[0];

	if (delta)
	{
		x0 = -x0;
		x1 = -x1;
		v0 = -v0;
		v1 = -v1;
	}

	Alima = j_max * Tj1;
	Alimd = -j_max * Tj2;
	Vlim = v0 + (Ta - Tj1) * Alima;

	Vmax = v_max;
	Amax = a_max;
	Jmax = j_max;

	T = Ta + Tv + Td;

	return;
}

TrajectoryPoint Trajectory::CalculateByTime(float time)
{
	float p;
	float v;
	float a;
	float j;

	const auto delta = X0 > X1;

	if (delta)
	{
		X0 = -X0;
		X1 = -X1;
		V0 = -V0;
		V1 = -V1;
	}

	if (time < 0)
	{
		throw "Invalid input. Time less than 0.";
	}

	if (time < Tj1)
	{
		p = X0 + V0 * time + Jmax * time * time * time / 6;
		v = V0 + Jmax * time * time / 2;
		a = Jmax * time;
		j = Jmax;
	}
	else if (time < Ta - Tj1)
	{
		p = X0 + V0 * time + Alima * (3 * time * time - 3 * Tj1 * time + Tj1 * Tj1) / 6;
		v = V0 + Alima * (time - Tj1 / 2);
		a = Alima;
		j = 0;
	}
	else if (time < Ta)
	{
		p = X0 + (Vlim + V0) * Ta / 2 - Vlim * (Ta - time) + Jmax * (Ta - time) * (Ta - time) * (Ta - time) / 6;
		v = Vlim - Jmax * (Ta - time) * (Ta - time) / 2;
		a = Jmax * (Ta - time);
		j = -Jmax;
	}
	else if (time < Ta + Tv)
	{
		p = X0 + (Vlim + V0) * Ta / 2 + Vlim * (time - Ta);
		v = Vlim;
		a = 0;
		j = 0;
	}
	else if (time < T - Td + Tj2)
	{
		p = X1 - (Vlim + V1) * Td / 2 + Vlim * (time - T + Td) - Jmax * (time - T + Td) * (time - T + Td) * (time - T + Td) / 6;
		v = Vlim - Jmax * (time - T + Td) * (time - T + Td) / 2;
		a = -Jmax * (time - T + Td);
		j = -Jmax;
	}
	else if (time < T - Tj2)
	{
		p = X1 - (Vlim + V1) * Td / 2 + Vlim * (time - T + Td) + Alimd * (3 * (time - T + Td) * (time - T + Td) - 3 * Tj2 * (time - T + Td) + Tj2 * Tj2) / 6;
		v = Vlim + Alimd * (time - T + Td - Tj2 / 2);
		a = Alimd;
		j = 0;
	}
	else if (time < +T)
	{
		p = X1 - V1 * (T - time) - Jmax * (T - time) * (T - time) * (T - time) / 6;
		v = V1 - Jmax * (T - time) * (T - time) / 2;
		a = -Jmax * (T - time);
		j = Jmax;
	}
	else
	{
		throw "Invalid input. Time more than T";
	}

	if (delta)
	{
		X0 = -X0;
		X1 = -X1;
		V0 = -V0;
		V1 = -V1;

		p = -p;
		v = -v;
		a = -a;
		j = -j;
	}

	TrajectoryPoint tmp(p,v,a,j,0);

	return tmp;
}

TrajectoryPoint Trajectory::CalculateByProgress(float percent)
{
	if (percent < 0)
	{
		return {X0, 0, 0, 0, -1};
	}
	else if (percent > 1)
	{
		return {X0, 0, 0, 0, +1};
	}
	else
	{
		return {X0 + percent * (X1 - X0), 0, 0, 0, 0};
	}
}

float Trajectory::ConvertTimetoProgress(float time)
{
	TrajectoryPoint _P = CalculateByTime(time);

	switch (_P.State)
	{
	case -1:
		return 0;
		break;
	case 1:
		return 1;
		break;
	default:
		return (_P.Position - X0) / (X1 - X0);
		break;
	}
}

float Trajectory::GetTotalTime()
{
	return T;
}
