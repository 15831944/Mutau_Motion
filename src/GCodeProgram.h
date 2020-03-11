#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include "GCode.h"
#include "CNC.h"

class GCodeProgram
{
    int NumberOfLines = 0;
    GCode GCodeLines[10000];

public:
    GCodeProgram(std::string inFile);
    int getNumberOfLines();
    std::string getLine(int LineNumber);
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

std::string GCodeProgram::getLine(int LineNumber)
{
    return GCodeLines[LineNumber].getText();
}
