#include "Axis.h"
#include "CNC.h"
#include "GCode.h"
#include "MultiAxisTrajectory.h"
#include "Trajectory.h"
#include "TrajectoryPoint.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char *args[])
{
    Axis A1(-1000, 1000, 0, 1);
    Axis A2 = A1;
    Axis A3 = A1;

    CNC myCNC(A1, A2, A3);

    GCode aa("G01 X10 Y20");
    std::cout << "Hello";
    std::cout << "Hello";
    return 0;
}