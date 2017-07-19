/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   instructionFuctions.h
 * Author: osboxes
 *
 * Created on 20 October 2016, 23:19
 */

#ifndef INSTRUCTIONFUCTIONS_H
#define INSTRUCTIONFUCTIONS_H

#include <string>
#include <iostream>
#include <cstdlib>

class instructionFuctions {
public:
    instructionFuctions();
    
    void Mov (int R[],std::string instruction);
    void Prn (int R[],std::string instruction);
    void Sub (int R[],std::string instruction);
    void Add (int R[],std::string instruction);
    void Hlt (int R[]);
    int Jmp (int R[],std::string instruction); 
private:
    int Power(int number,int exponent);
    int ConvertInteger(std::string str);
};

#endif /* INSTRUCTIONFUCTIONS_H */

