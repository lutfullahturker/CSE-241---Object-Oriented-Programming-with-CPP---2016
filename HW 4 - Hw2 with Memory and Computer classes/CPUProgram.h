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
    CPUProgram(int option);
    std::string getLine(int lineNum)const;
    int size()const;
    void ReadFile(std::string fileName);
private:
    std::string convertCapitalLetter (std::string str);
    std::string fixInstruction(std::string fixIt);
    int fileSize;
    std::vector <std::string> progLines;
};

#endif /* CPUPROGRAM_H */

