#pragma once
class TrajectoryPoint
{
public:
	TrajectoryPoint(float, float, float, float, int);
	float Position = 0;
	float Velocity = 0;
	float Acceleration = 0;
	float Jerk = 0;
	int State = 0;
};

TrajectoryPoint::TrajectoryPoint(float p, float v, float a, float j, int state)
{
	Position = p;
	Velocity = v;
	Acceleration = a;
	Jerk = j;
	State = state;
}
