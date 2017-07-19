/* 
 * File:   CPU.cpp
 * Author: Lütfullah Türker
 * 
 * Created on 19 October 2016, 20:34
 */

#include "CPU.h"
#include "CPUProgram.h"


CPU::CPU() {
}

void CPU::print()const
{
    std::cout << "Registers >>\n";
    for (int i=0;i<5;i++)
        std::cout << "R" << i+1 << " = " << registers[i] << "  ";
    std::cout << "\nProgram Counter >>\n" << programCounter << std::endl;
}
bool CPU::halted()const
{// HLT okunduğunda halted olması için true return ediyoruz.
    if (curInstruction == "HLT")
        return true;
    return false;
}

void CPU::execute (std::string instruction)
{
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
        runInst.Mov(registers,instruction);
    else if (curInstruction == "ADD")
        runInst.Add(registers,instruction);
    else if (curInstruction == "SUB")
        runInst.Sub(registers,instruction);
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
    else if (curInstruction == "PRN")
        runInst.Prn(registers,instruction);
    else if (curInstruction == "HLT")
        runInst.Hlt(registers);
    else
    {
        std::cerr << "Invalid Instruction !" << std::endl;
        exit (-1);
    }
    if (curInstruction != "JMP")
        // JMP nin PC işlemleri yukardaki if de yapıldığı için burda bakmıyoruz.
        set_PC(get_PC()+1);
}

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

int CPU::get_reg1()const{return registers[0];}
int CPU::get_reg2()const{return registers[1];}
int CPU::get_reg3()const{return registers[2];}
int CPU::get_reg4()const{return registers[3];}
int CPU::get_reg5()const{return registers[4];}
int CPU::get_PC()const{return programCounter;}