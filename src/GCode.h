#pragma once
#include "TrajectoryPoint.h"
#include "MultiAxisTrajectory.h"
#include "CNC.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>

enum GCodeType { G, M, S, T };

class GCode
{
public:
	GCode(std::string command);
	MultiAxisTrajectory Handle(CNC machine, GCodeType type, int number, double x, double y, double z, double f);
	void Parse();
private:
	std::string Text;
	GCodeType Type;
	std::string Number;
	std::map<char,double> Modules;
};

GCode::GCode(std::string command)
{
	Text = command;
}

void GCode::Parse()
{
	char Key;
	double Value;

	while (std::getline(Text," ")
	{
		/* code */
	}
	


	while (std::getline(iss, token, ','))
	{

	}
}

MultiAxisTrajectory GCode::Handle(CNC machine, GCodeType type, int number, double x, double y, double z, double f)
{
	Type = type;
	Number = number;
	
	switch (Type)
	{
	case G:
		switch (number)
		{
		//case 0:
			//break;
		case 1:
			double AllowableLinearVelocity = fmin(machine.MaxLinearSpeed, f);
			double dx = x - machine.X;
			double dy = y - machine.Y;
			double dz = z - machine.Z;

			double LinearLength = sqrt(dx * dx + dy * dy + dz * dz);

			double vx = AllowableLinearVelocity * (abs(dx) / LinearLength);
			double vy = AllowableLinearVelocity * (abs(dy) / LinearLength);
			double vz = AllowableLinearVelocity * (abs(dz) / LinearLength);

			double ax = machine.MaxLinearAcceleration * (abs(dx) / LinearLength);
			double ay = machine.MaxLinearAcceleration * (abs(dy) / LinearLength);
			double az = machine.MaxLinearAcceleration * (abs(dz) / LinearLength);

			double jx = machine.MaxLinearJerk * (abs(dx) / LinearLength);
			double jy = machine.MaxLinearJerk * (abs(dy) / LinearLength);
			double jz = machine.MaxLinearJerk * (abs(dz) / LinearLength);

			Trajectory X(machine.X, x, 0, 0, vx, ax, jx);
			Trajectory Y(machine.Y, y, 0, 0, vy, ay, jy);
			Trajectory Z(machine.Z, z, 0, 0, vz, az, jz);

			return MultiAxisTrajectory(machine, X, Y, Z);
			break;
		/*case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 10:
			break;
		case 12:
			break;
		case 13:
			break;*/
		/*case 17:
			machine.Plane = XY;
			break;
		case 18:
			machine.Plane = ZX;
			break;
		case 19:
			machine.Plane = YZ;
			break;
		case 20:
			machine.Unit = mm;
			break;
		case 21:
			machine.Unit = inch;
			break;*/
		/*case 28:
			break;
		case 34:
			break;
		case 35:
			break;
		case 36:
			break;
		case 37:
			break;
		case 40:
			break;
		case 41:
			break;
		case 42:
			break;
		case 43:
			break;
		case 44:
			break;
		case 45:
			break;
		case 46:
			break;
		case 501:
			break;
		case 511:
			break;
		case 52:
			break;
		case 54:
			break;
		case 55:
			break;
		case 56:
			break;
		case 57:
			break;
		case 58:
			break;
		case 59:
			break;
		case 60:
			break;
		case 61:
			break;
		case 65:
			break;
		case 66:
			break;
		case 68:
			break;
		case 69:
			break;
		case 73:
			break;
		case 74:
			break;
		case 76:
			break;
		case 80:
			break;
		case 81:
			break;
		case 82:
			break;
		case 83:
			break;
		case 84:
			break;
		case 85:
			break;
		case 86:
			break;
		case 87:
			break;
		case 88:
			break;
		case 89:
			break;*/
		/*case 90:
			machine.Relative = false;
			break;
		case 91:
			machine.Relative = true;
			break;
		case 92:
			break;*/
		/*default:
			throw"Invalid GCode Number";
			break;*/
		}
		break;
	/*case M:
		break;
	case T:
		break;*/

	default:
		break;
	}
}
