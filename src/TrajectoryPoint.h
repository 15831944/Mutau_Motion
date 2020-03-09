#pragma once
class TrajectoryPoint
{
public:
	TrajectoryPoint();
	TrajectoryPoint(double p, double v, double a, double j, int state);
	double getPosition();
	double getVelocity();
	double getAcceleration();
	double getJerk();
	int getState();

private:
	double Position = 0;
	double Velocity = 0;
	double Acceleration = 0;
	double Jerk = 0;
	int State;
};

TrajectoryPoint::TrajectoryPoint(double p, double v, double a, double j, int state)
{
	Position = p;
	Velocity = v;
	Acceleration = a;
	Jerk = j;
	State = state;
}

double TrajectoryPoint::getPosition()
{
	return Position;
}

double TrajectoryPoint::getVelocity()
{
	return Velocity;
}

double TrajectoryPoint::getAcceleration()
{
	return Acceleration;
}

double TrajectoryPoint::getJerk()
{
	return Jerk;
}

int TrajectoryPoint::getState()
{
	return State;
}
