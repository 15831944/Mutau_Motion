#pragma once

class Axis
{
public:
	Axis(double lowerlimit, double upperlimit, double home, double gearratio);
	double LowerLimit;
	double UpperLimit;
	double Home;
	double GearRatio;

	int ConvertPosition2Motor(double position);
private:
};

Axis::Axis(double lowerlimit, double upperlimit, double home, double gearratio)
{
	if (lowerlimit >= upperlimit)
	{
		throw"Invalid Lower and Upper Limit Values";
	}
	if (lowerlimit > home)
	{
		throw"Invalid Lower Limit and Home Values";
	}
	if (upperlimit < home)
	{
		throw"Invalid Upper Limit and Home Values";
	}
	if (gearratio <= 0)
	{
		throw"Invalid Gear Ratio Value";
	}

	LowerLimit = lowerlimit;
	UpperLimit = upperlimit;
	Home = home;
	GearRatio = gearratio;
}

int Axis::ConvertPosition2Motor(double position)
{
	return int(GearRatio * position);
}
