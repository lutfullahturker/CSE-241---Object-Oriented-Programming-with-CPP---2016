/* 
 * File:   Computer.h
 * Author: Lütfullah TÜRKER
 *
 * Created on 27 October 2016, 17:38
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer {
public:
    Computer(CPU& cpu,CPUProgram& cpuProgram,Memory& memory,int runOption);
    Computer(int runOption);
    Computer();
    
    void execute();
    
    void setCPU(CPU newCPU);
    void setCPUProgram(CPUProgram newCPUProgram);
    void setMemory(Memory newMemory);
    
    Memory getMemory()const;
    CPUProgram getCPUProgram()const;
    CPU getCPU()const;
private:
    CPU myCPU;
    CPUProgram myCPUProgram;
    Memory myMemory;
    int option;
};

#endif /* COMPUTER_H */

