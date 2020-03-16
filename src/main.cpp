#include "Axis.h"
// #include "CNC.h"
#include "GCode.h"
#include "GCodeProgram.h"
// #include "MultiAxisTrajectory.h"
#include "Trajectory.h"
#include "TrajectoryPoint.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char *args[])
{
    Axis A1(-1000, 1000, 0, 1);
    Axis A2 = A1;
    Axis A3 = A1;

    TrajectoryPoint P1(0, 0, 0, 0, 0);

    Trajectory T1(0, 1, 0, 0, 1, 2, 3);

    GCode G1("g01 x-3.75 y-20 z0.25");

    std::string ttt = "g01 x-3.75 y-20 z0.25\n"
    "g01 x-3.75 y-20 z0.25\n"
    "g01 x-3.75 y-20 z0.25\n"
    "g01 x-3.75 y-20 z0.25\n"
    "g01 x-3.75 y-20 z0.25\n"
    "g01 x-3.75 y-20 z0.25";
    // GCodeProgram GP1(ttt);

    std::cout << "Hello";

    return 0;
}