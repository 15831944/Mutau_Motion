#include <limits>
double const inf = std::numeric_limits<float>::max();

class Robot
{
	int NumberofAxis;
	bool isParallel;

public:

	enum RobotTypes
	{
		SCARA,
		ArticulatedArm,
		Stewart,
		Delta
	};

	RobotTypes RobotType;
	float JointMaxLimit[6] = {+inf};								// Unit: Deg
	float JointMinLimit[6] = {-inf};								// Unit: Deg
	float JointHome[6] = {0, 0, 0, 0, 0, 0};						// Unit: Deg
	float JointMaxSpeed[6] = {100, 100, 100, 100, 100, 100};		// Unit: Deg/s
	float JointMaxAcceleration[6] = {500, 500, 500, 500, 500, 500}; // Unit: Deg/s^2
	float JointMaxJerk[6] = {1000, 1000, 1000, 1000, 1000, 1000};   // Unit: Deg/s^3

	Robot(RobotTypes);
};

Robot::Robot(Robot::RobotTypes type)
{
	RobotType = type;

	switch (type)
	{
	case SCARA:
		NumberofAxis = 4;
		isParallel = false;
		break;
	case ArticulatedArm:
		NumberofAxis = 6;
		isParallel = false;
		break;
	case Stewart:
		NumberofAxis = 6;
		isParallel = true;
		break;
	case Delta:
		NumberofAxis = 4;
		isParallel = true;
		break;
	default:
		break;
	}
}