#pragma once
#include "Trajectory.h"
#include "CNC.h"

class MultiAxisTrajectory
{
    Trajectory LongestTrajectory;
    std::list<Trajectory> TrajectoryList;
    double T;

public:
    MultiAxisTrajectory();
    MultiAxisTrajectory(CNC machine, Trajectory x, Trajectory y, Trajectory z);
    std::list<TrajectoryPoint> CalculateByTime(double time);
    std::list<TrajectoryPoint> CalculateByProgress(double percent);
    double GetTotalTime();
    void Run();
    CNC Machine;
};

MultiAxisTrajectory::MultiAxisTrajectory()
{
	
}

MultiAxisTrajectory::MultiAxisTrajectory(CNC machine, Trajectory x, Trajectory y, Trajectory z)
{
	TrajectoryList.push_back(x);
	TrajectoryList.push_back(y);
	TrajectoryList.push_back(z);

	Machine = machine;

	LongestTrajectory = x;
	T = LongestTrajectory.GetTotalTime();

	for (std::list<Trajectory>::iterator it = TrajectoryList.begin(); it != TrajectoryList.end(); ++it)
	{
		if (it->GetTotalTime() > LongestTrajectory.GetTotalTime())
		{
			LongestTrajectory = *it;
			T = it->GetTotalTime();
		}
	}
}

std::list<TrajectoryPoint> MultiAxisTrajectory::CalculateByTime(double time)
{
	std::list<TrajectoryPoint> TrajectoryPointList;

	double _U = LongestTrajectory.ConvertTimetoProgress(time);

	for (std::list<Trajectory>::iterator it = TrajectoryList.begin(); it != TrajectoryList.end(); ++it)
	{
		TrajectoryPointList.push_back(it->CalculateByProgress(_U));
	}

	return TrajectoryPointList;
}

std::list<TrajectoryPoint> MultiAxisTrajectory::CalculateByProgress(double percent)
{
	std::list<TrajectoryPoint> TrajectoryPointList;

	for (std::list<Trajectory>::iterator it = TrajectoryList.begin(); it != TrajectoryList.end(); ++it)
	{
		TrajectoryPointList.push_back(it->CalculateByProgress(percent));
	}

	return TrajectoryPointList;
}

double MultiAxisTrajectory::GetTotalTime()
{
	return T;
}

void MultiAxisTrajectory::Run()
{
	// std::fstream filestr;
	// filestr.open("test.txt", std::fstream::out | std::fstream::app);
	// double Time = 0;
	// double dt = 1e-3;
	// while (Time <= GetTotalTime())
	// {
	// 	std::list<TrajectoryPoint> Target = CalculateByTime(Time);
	// 	Machine.GoToTrajectoryPointList(Target);
	// 	//std::cout << Machine.Time + Time << "," << Machine.X << "," << Machine.Y << "," << Machine.Z << std::endl;
	// 	filestr << Machine.Time + Time << "," << Machine.X << "," << Machine.Y << "," << Machine.Z << std::endl;
	// 	Time = Time + Machine.Feed * dt;
	// }
	// filestr.close();

	Machine.Time = Machine.Time + GetTotalTime();
}

