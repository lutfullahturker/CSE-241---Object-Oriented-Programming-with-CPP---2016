/* 
 * File:   instructionFuctions.h
 * Author: Lütfullah TÜRKER
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#ifndef INSTRUCTIONFUCTIONS_H
#define INSTRUCTIONFUCTIONS_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "Memory.h"

class instructionFuctions {
public:
    instructionFuctions();
    
    void Mov (int R[],std::string instruction,Memory* myMemory);
    void Prn (int R[],std::string instruction,Memory* myMemory);
    void Sub (int R[],std::string instruction,Memory* myMemory);
    void Add (int R[],std::string instruction,Memory* myMemory);
    int Jmp (int R[],std::string instruction);
    int Jpn (int R[],std::string instruction);
private:
    int Power(int number,int exponent);
    int ConvertInteger(std::string str);
};

#endif /* INSTRUCTIONFUCTIONS_H */

