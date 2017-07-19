/* 
 * File:   Memory.h
 * Author: Lütfullah TÜRKER
 *
 * Created on 27 October 2016, 17:13
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class Memory {
public:
    Memory();
    Memory(int runOption);
    
    const unsigned int getMem(int memNum)const;
    void setMem(unsigned int memoryNum,int assign);
    void printAll()const;
private:
    unsigned int memory[50];
    int runOption;
};

#endif /* MEMORY_H */

