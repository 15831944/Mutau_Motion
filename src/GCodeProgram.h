#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include "GCode.h"

class GCodeProgram
{
    int NumberOfLines = 0;
    GCode GCodeLines[10000];

public:
    GCodeProgram(std::string);
    int getNumberOfLines();
    GCode getLine(int);
};

GCodeProgram::GCodeProgram(std::string inFile)
{
    std::stringstream ss(inFile);
    std::string line;
    while (std::getline(ss, line, '\n'))
    {
        GCodeLines[NumberOfLines] = GCode(line);
        NumberOfLines++;
    }
}

int GCodeProgram::getNumberOfLines()
{
    return NumberOfLines;
}

GCode GCodeProgram::getLine(int LineNumber)
{
    return GCodeLines[LineNumber];
}
