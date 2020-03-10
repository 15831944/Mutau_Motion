#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

class GCodeProgram
{
    int NumberOfLines = 0;
    // GCode TextLines[10000];
public:
    GCodeProgram();
    int getNumberOfLines();
    std::string getLine(int LineNumber);
};

GCodeProgram::GCodeProgram()
{
    std::ifstream inFile;
    std::string line;
    inFile.open("test.txt");

    while (std::getline(inFile, line))
    {
        // TextLines[NumberOfLines] = GCode(line);
        NumberOfLines++;
    }

    inFile.close();
}

int GCodeProgram::getNumberOfLines()
{
    return NumberOfLines;
}

std::string GCodeProgram::getLine(int LineNumber)
{
    // return TextLines[LineNumber].getText();
}
