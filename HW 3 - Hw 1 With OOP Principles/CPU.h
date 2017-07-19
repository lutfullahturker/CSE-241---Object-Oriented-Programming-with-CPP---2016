/* 
 * File:   CPU.h
 * Author: Lütfullah Türker
 *
 * Created on 19 October 2016, 20:34
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include "instructionFuctions.h"
#include "CPUProgram.h"
#include <cstdlib>

class CPU {
public:
    CPU();
    
    void print()const;
    bool halted()const;
    void execute (std::string instruction);
    
    void set_reg1(int reg);
    void set_reg2(int reg);
    void set_reg3(int reg);
    void set_reg4(int reg);
    void set_reg5(int reg);
    void set_PC(int PC);
    
    int get_reg1()const;
    int get_reg2()const;
    int get_reg3()const;
    int get_reg4()const;
    int get_reg5()const;
    int get_PC()const;
private:
    int registers[5] = {0,0,0,0,0};
    // ilk atamaları burada yaptığımız için constructor fonksiyonlarında
    // herhangi bir atama yapmaya gerek duymuyoruz.
    int programCounter = 1;
    std::string curInstruction;
    // curInstruction da execute a gelen satırdaki kullanılacak inst. tutuluyor.
    instructionFuctions runInst;
    // execute fonk. da kullanacağımız inst. fonksiyonlarını yazdığımız
    // class object ini tanımlıyoruz.
};

#endif /* CPU_H */