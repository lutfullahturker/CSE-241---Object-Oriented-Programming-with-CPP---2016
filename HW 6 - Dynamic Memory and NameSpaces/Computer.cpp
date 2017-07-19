/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.cpp
 * Author: Lütfullah TÜRKER
 * 
 * Created on 27 October 2016, 17:38
 */

#include "Computer.h"

using namespace std;


Computer::Computer(CPU& cpu,CPUProgram& cpuProgram,Memory& memory,int runOption)
{
    myCPU = cpu;
    myCPUProgram = cpuProgram;
    myMemory = memory;
    option = runOption;
}
Computer::Computer(int runOption)
{
    option = runOption;
}
Computer::Computer(){option =0;}
//////////////////////////////////SETTERS//////////////////////////////////////
void Computer::setCPU(CPU newCPU)
{
    myCPU = newCPU;
}
void Computer::setCPUProgram(CPUProgram newCPUProgram)
{
    myCPUProgram = newCPUProgram;
}
void Computer::setMemory(Memory newMemory)
{
    myMemory = newMemory;
}
//////////////////////////////////GETTERS//////////////////////////////////////
Memory Computer::getMemory()const {return myMemory;}
CPUProgram Computer::getCPUProgram()const {return myCPUProgram;}
CPU Computer::getCPU()const {return myCPU;}

void Computer::execute()
{
    string instruction;
    myCPU.setOption(option);
    while(!myCPU.halted())
    {
        instruction = myCPUProgram.getLine(myCPU.get_PC()-1);
        myCPU.execute(instruction,myMemory);
        if(option == 1  || option == 2)
        {
            myCPU.print();
            if (option == 2 || instruction.substr(0,3) == "HLT")
                myMemory.printAll();
        }
        else if (option == 0 && instruction.substr(0,3) == "HLT")
        {
            myCPU.print();
            myMemory.printAll();
        }
    }

}
