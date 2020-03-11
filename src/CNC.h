#pragma once
#include "Axis.h"
#include "TrajectoryPoint.h"
#include "GCodeProgram.h"
#include "GCode.h"
#include <list>
#include <string>

enum CirclePlane {XY, ZX, YZ};
enum LengthUnit { mm, inch };
class CNC
{
public:
	CNC();
	CNC(Axis A1, Axis A2, Axis A3);
	CNC(Axis A1, Axis A2, Axis A3, Axis A4);
	CNC(Axis A1, Axis A2, Axis A3, Axis A4, Axis A5);
	CNC(Axis A1, Axis A2, Axis A3, Axis A4, Axis A5, Axis A6);
	void Execute(GCodeProgram myGCode);
	void GoToTrajectoryPointList(std::list<TrajectoryPoint> Target);

	int NumberOfAxes();

	double Feed = 1;

	double MaxLinearSpeed = 0;
	double MaxLinearAcceleration = 0;
	double MaxLinearJerk = 0;

	double MaxAngularSpeed = 0;
	double MaxAngularAcceleration = 0;
	double MaxAnglarJerk = 0;

	double X = 0;
	double Y = 0;
	double Z = 0;
	double Roll = 0;
	double Pitch = 0;
	double Yaw = 0;

	bool Relative = false;

	CirclePlane Plane = XY;

	double Time = 0;
	LengthUnit Unit = mm;

private:
	std::list<Axis> CNCAxes;
	int numberofaxes;

};

CNC::CNC()
{
}

CNC::CNC(Axis A1, Axis A2, Axis A3)
{
	CNCAxes.push_back(A1);
	CNCAxes.push_back(A2);
	CNCAxes.push_back(A3);
	numberofaxes = 3;
}

CNC::CNC(Axis A1, Axis A2, Axis A3, Axis A4)
{
	CNCAxes.push_back(A1);
	CNCAxes.push_back(A2);
	CNCAxes.push_back(A3);
	CNCAxes.push_back(A4);
	numberofaxes = 4;
}

CNC::CNC(Axis A1, Axis A2, Axis A3, Axis A4, Axis A5)
{
	CNCAxes.push_back(A1);
	CNCAxes.push_back(A2);
	CNCAxes.push_back(A3);
	CNCAxes.push_back(A4);
	CNCAxes.push_back(A5);
	numberofaxes = 5;
}

CNC::CNC(Axis A1, Axis A2, Axis A3, Axis A4, Axis A5, Axis A6)
{
	CNCAxes.push_back(A1);
	CNCAxes.push_back(A2);
	CNCAxes.push_back(A3);
	CNCAxes.push_back(A4);
	CNCAxes.push_back(A5);
	CNCAxes.push_back(A6);
	numberofaxes = 6;
}

int CNC::NumberOfAxes()
{
	return numberofaxes;
}

void CNC::GoToTrajectoryPointList(std::list<TrajectoryPoint> Target)
{
	std::list<TrajectoryPoint>::iterator it = Target.begin();
	std::list<Axis>::iterator Axit = CNCAxes.begin();
	X = it->getPosition() * Axit->GearRatio;
	it++; Axit++;
	Y = it->getPosition() * Axit->GearRatio;
	it++; 
	Z = it->getPosition() * Axit->GearRatio;

	if (numberofaxes == 4)
	{
		it++; Axit++;
		Roll = it->getPosition() * Axit->GearRatio;
	}
	else if (numberofaxes == 5)
	{
		it++; Axit++;
		Roll = it->getPosition() * Axit->GearRatio;
		it++; Axit++;
		Pitch = it->getPosition() * Axit->GearRatio;
	}
	else if (numberofaxes == 6)
	{
		it++; Axit++;
		Roll = it->getPosition() * Axit->GearRatio;
		it++; Axit++;
		Pitch = it->getPosition() * Axit->GearRatio;
		it++; Axit++;
		Yaw = it->getPosition() * Axit->GearRatio;
	}
}

