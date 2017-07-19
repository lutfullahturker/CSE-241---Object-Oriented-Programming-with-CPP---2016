/* 
 * File:   CPU.cpp
 * Author: Lütfullah Türker
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#include "CPU.h"


CPU::CPU(){}

CPU::CPU(int option)
{
    runOption = option ;
}

void CPU::setOption(int option){runOption = option;}

void CPU::print()const
{
    std::cout << "Registers >>\n";
    for (int i=0;i<5;i++)
        std::cout << "R" << i+1 << " = " << registers[i] << "  ";
    std::cout << "\nProgram Counter >>  " << programCounter << std::endl;
}
bool CPU::halted()const
{// HLT okunduğunda halted olması için true return ediyoruz.
    if (curInstruction == "HLT")
        return true;
    return false;
}

void CPU::execute (std::string instruction,Memory& myMemory)
{
    instruction = convertCapitalLetter (instruction);
// instruction aldıktan sonra tüm harfleri büyük harfe çeviriyoruz.
    instruction = fixInstruction(instruction);
    // ve boşlukları silip okuduğumuz satırdaki yorumları da temizleyip
// MOVR1,R2  şeklinde yapışık temiz bir string haline getiriyoruz.
    if (instruction.size() < 3)
    {// en kısa instruction HLT yani 3 harf olması gerektiği için boş satır
     // gibi yanlış kullanımları kontrol ediyoruz.
        std::cerr << "Invalid input" << std::endl;
        exit (1);
    }
    int jumpLine;
    curInstruction = instruction.substr(0,3);
    // instructionların hepsi 3 harf olduğu için stringin ilk 3 harfini alıp
    // curInstruction a eşitliyoruz.halted fonk. da da buna göre Halt işlemini yapıyoruz.
    instruction.erase(instruction.begin(),instruction.begin()+3);
    // ilk 3 harfini aldıktan sonra instruction fonksiyounlarında işlemleri daha
    // rahat yapmak için ilk 3 harfi instruction stringinden siliyoruz.
    if (curInstruction == "MOV")
        runInst.Mov(registers,instruction,&myMemory);
    else if (curInstruction == "ADD")
        runInst.Add(registers,instruction,&myMemory);
    else if (curInstruction == "SUB")
        runInst.Sub(registers,instruction,&myMemory);
    else if (curInstruction == "JMP")
    {// Jmp fonksiyonu diğerleri gibi void değil.gidilmek istenen satır sayısını
        // return ediyor.Bir registerle çağrıldığında ve register 0 değilse de
        // belirtilen satıra atlanılmayacağı için -1 return ediyor.Aşağıda da
        // -1 return ettiği durumda normal şekilde bir sonraki satıra geçiyor.
        // atlanılması gerekiyorsa return edilen satır değeri PC ye atanıyor.
        jumpLine = runInst.Jmp(registers,instruction);
        if (jumpLine != -1)
            set_PC(jumpLine);
        else 
            set_PC(get_PC()+1);
    }
    else if (curInstruction == "JPN")
    {
        jumpLine = runInst.Jpn(registers,instruction);
        if (jumpLine != -1)
                set_PC(jumpLine);
            else 
                set_PC(get_PC()+1);
    }
    else if (curInstruction == "PRN")
        runInst.Prn(registers,instruction,&myMemory);
    else if (curInstruction == "HLT") {}
    else
    {
        std::cerr << "Invalid Instruction !" << std::endl;
        exit (-1);
    }
    if (curInstruction != "JMP" && curInstruction != "JPN")
        // JMP nin PC işlemleri yukardaki if de yapıldığı için burda bakmıyoruz.
        set_PC(get_PC()+1);
    if (runOption == 1 || runOption == 2)
        std::cout<<curInstruction<<" "<<instruction<<" - ";
}

std::string CPU::convertCapitalLetter (std::string str)
{// örneğin MOV fonksiyonunun dosyada mOv şeklinde yazılması gibi durumlarda da
 //programımızın doğru çalışması için yazılan yazının tamamını büyük harfe çeviriyoruz.
    int i;
    for (i=0;i<str.size();i++)
        if (str[i] >= 'a' && str[i] <= 'z' )
            str[i] -= 'a' -'A' ;
    // her harfi tek tek küçük harf mi diye kontrol ederek küçükse büyüğe çeviriyoruz.
    return str;
}
std::string CPU::fixInstruction(std::string fixIt)
{
    for (int i=0;i<fixIt.size() ; i++)
    {// instruction satırındaki tüm boşlukları siliyoruz.
        if (fixIt[i] == ' ')
        {
            fixIt.erase(fixIt.begin()+i);
            i--;
            // boşluk görünce girip siliyoruz.i yi 1 azaltıyoruz. çünkü boşluğu
            // silince i indexi boşluktan sonraki karaktere kayıyor.o karakteri
            // de okuyup bakmak için i yi azaltıyoruz.
        }
        else if (fixIt[i] == ';')
        {
            fixIt.erase(fixIt.begin()+i , fixIt.end());
            return fixIt;
        }
    }
    return fixIt; 
}
//////////////////////////////////SETTERS//////////////////////////////////////
void CPU::set_reg1(int reg)
{
    registers[0] = reg;
}
void CPU::set_reg2(int reg)
{
    registers[1] = reg;
}
void CPU::set_reg3(int reg)
{
    registers[2] = reg;
}
void CPU::set_reg4(int reg)
{
    registers[3] = reg;
}
void CPU::set_reg5(int reg)
{
    registers[4] = reg;
}
void CPU::set_PC(int PC)
{
    programCounter = PC;
}
//////////////////////////////////GETTERS//////////////////////////////////////
int CPU::get_reg1()const{return registers[0];}
int CPU::get_reg2()const{return registers[1];}
int CPU::get_reg3()const{return registers[2];}
int CPU::get_reg4()const{return registers[3];}
int CPU::get_reg5()const{return registers[4];}
int CPU::get_PC()const{return programCounter;}