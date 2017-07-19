/* 
 * File:   Memory.cpp
 * Author: Lütfullah TÜRKER
 * 
 * Created on 27 October 2016, 17:13
 */

#include "Memory.h"

using namespace std;


Memory::Memory()
{
    for (int i=0;i < 50 ; i++)
        memory[i] = 0;
}

Memory::Memory(int option) 
{
    runOption = option;
    for (int i=0;i < 50 ; i++)
        memory[i] = 0;
}

const unsigned int Memory::getMem(int memNum)const 
{
    if (memNum >= 50 || memNum < 0)
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
    return memory[memNum];
    // getMemory fonksiyonunu memory arrayinden istenilen elemanı const şekilde getiriyor.
}

void Memory::setMem(unsigned int memoryNum,int assign){memory[memoryNum] = assign ;}
void Memory::printAll()const
{
    cout << "Memory >> ";
    for (int i = 0 ;i<50;i++)
        cout << "#" << i << " "<< getMem(i) << " ";
    cout << endl << endl;
}
