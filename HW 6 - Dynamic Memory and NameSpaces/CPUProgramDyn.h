/* 
 * File:   CPUProgramDyn.h
 * Author: Lütfulah TÜRKER
 *
 * Created on 25 November 2016, 14:09
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
namespace DynamicCPUProg
{
class CPUProgramDyn {
public:
    CPUProgramDyn();
    CPUProgramDyn(int runOption);
    CPUProgramDyn(const CPUProgramDyn& prog2);
    ~CPUProgramDyn();
    std::string getLine(int lineNum)const;
    int size()const;
    void ReadFile(std::string fileName);
//////////////////////////Operator Overloads//////////////////////////////////
    std::string operator [](const int lineNum);
    const std::string operator [](const int lineNum)const;
    const CPUProgramDyn operator +(const std::string& addStr)const;
    const CPUProgramDyn& operator +=(const std::string& addStr);
    const CPUProgramDyn operator +(const CPUProgramDyn& prog2)const;
    const bool operator ==(const CPUProgramDyn& compare)const;
    const bool operator !=(const CPUProgramDyn& compare)const;
    const bool operator <(const CPUProgramDyn& compare)const;
    const bool operator >(const CPUProgramDyn& compare)const;
    const bool operator <=(const CPUProgramDyn& compare)const;
    const bool operator >=(const CPUProgramDyn& compare)const;
    CPUProgramDyn& operator --();
    const CPUProgramDyn operator --(int);
    const CPUProgramDyn operator () (const int& num1,const int& num2)const;
    CPUProgramDyn& operator =(const CPUProgramDyn& prog2);
    friend std::ostream& operator <<(std::ostream& output,const CPUProgramDyn& printThis);
private:
    int option;
    int fileSize;
    int capacity;
    int used;
    std::string *progLines;
};
}
#endif /* CPUPROGRAMDYN_H */

