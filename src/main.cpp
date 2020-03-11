#include "Axis.h"
#include "CNC.h"
#include "GCode.h"
#include "GCodeProgram.h"
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
    Axis A4 = A1;

    CNC myCNC(A1, A2, A3);

    std::string myTXT = "G01 X10 Y0\n"
    "G01 X10 Y10\n"
    "G01 X0 Y10\n"
    "G01 X0 Y0\n";
    GCodeProgram myCode(myTXT);

    std::cout << "Hello" << std::endl;

    return 0;
}