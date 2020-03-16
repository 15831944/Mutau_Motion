#pragma once
class Axis
{
public:
	Axis(float lowerlimit, float upperlimit, float home, float gearratio);
	float LowerLimit;
	float UpperLimit;
	float Home;
	float GearRatio;
	int ConvertPosition2Motor(float position);
};

Axis::Axis(float lowerlimit, float upperlimit, float home, float gearratio)
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

int Axis::ConvertPosition2Motor(float position)
{
	return int(GearRatio * position);
}