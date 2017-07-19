/* 
 * File:   CPUProgram.h
 * Author: Lütfullah Türker
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

class CPUProgram {
public:
    CPUProgram();
    CPUProgram(int runOption);
    std::string getLine(int lineNum)const;
    int size()const;
    void ReadFile(std::string fileName);
//////////////////////////Operator Overloads//////////////////////////////////
    std::string& operator [](const int lineNum);
    const std::string& operator [](const int lineNum)const;
    const CPUProgram operator +(const std::string& addStr)const;
    const CPUProgram& operator +=(const std::string& addStr);
    const CPUProgram operator +(const CPUProgram& prog2)const;
    const bool operator ==(const CPUProgram& compare)const;
    const bool operator !=(const CPUProgram& compare)const;
    const bool operator <(const CPUProgram& compare)const;
    const bool operator >(const CPUProgram& compare)const;
    const bool operator <=(const CPUProgram& compare)const;
    const bool operator >=(const CPUProgram& compare)const;
    CPUProgram& operator --();
    const CPUProgram operator --(int);
    const CPUProgram operator () (const int& num1,const int& num2)const;
    friend std::ostream& operator <<(std::ostream& output,const CPUProgram& printThis);
private:
    int option;
    int fileSize;
    std::vector <std::string> progLines;
};

#endif /* CPUPROGRAM_H */

