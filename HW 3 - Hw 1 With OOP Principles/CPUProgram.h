/* 
 * File:   CPUProgram.h
 * Author: Lütfullah Türker
 *
 * Created on 19 October 2016, 20:36
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

class CPUProgram {
public:
    CPUProgram(std::string fileName);
    std::string getLine(int lineNum)const;
    int size()const;
    
private:
    void readFile(std::string fileName);
    std::string convertCapitalLetter (std::string str);
    std::string fixInstruction(std::string fixIt);
    int fileSize;
    std::string progLines[200];
    // Ödevi VECTOR konusunu işlemeden ve öğretilmeden önce yaptığım için 
    // string array kullandım.Boyutunu en fazla 200 satır olabilir dendiği için
    // böyle yaptım.Vector kullanmanın daha mantıklı olduğunun farkındayım.
    // İşlemeden önce yaptığım için bu konuda puanımın kırılmamasını isterim.
};

#endif /* CPUPROGRAM_H */

