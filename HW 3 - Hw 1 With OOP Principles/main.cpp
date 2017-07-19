/* 
 * File:   main.cpp
 * Author: Lütfullah TÜRKER
 * No: 141044050         CPP HW3
 * Created on 19 October 2016, 19:52
 */

#include "CPU.h"
#include "CPUProgram.h"
// Class larımızı include ediyoruz.Bu class larda iostream ,fstream, string gibi
//include işlemleri zaten yapıldığı için main de de kullanabiliyoruz.
// Bu yüzden burda tekrar iostream gibi gerekli include leri yazmadık.
using namespace std;

void Option (char* parameter,string str,CPU myCPU);
// argv[2] run optionı nın kontrolü yapılıp bu optiona göre ekrana registerler basılıyor.

int main(int argc, char** argv) 
{
    CPU myCPU;
    CPUProgram myProg(argv[1]);
    string instruction;
    if ( argc != 3)
    {// dosya adının veya run option ın girilmediği durumda argc 2 veya 1 
        // olacağından bunu kontrol ediyoruz.
        cerr << "Please Enter Run Parameters !" << endl;
        return 1;
    }
    if ((string) argv[2] != "0" && (string) argv[2] != "1")
    {// run option ın 0 ve 1 dışında olmaması gereken bir değer girilmesi durumu
        cerr << "Run Option Can Be Only 0 or 1 !" << endl;
        return 1;
    }
    while(!myCPU.halted())
    {
        instruction = myProg.getLine(myCPU.get_PC());
        if(instruction.substr(0,3) == "HLT" && (string)argv[2] == "1")
        // instruction stringinin ilk 3 harfini alıp HLT mi diye kontrol ediyoruz.
        // ve option 1 ken HLT yi yazdırıyoruz.Bunu HLT fonksiyonu program 0 ile
        // çalıştırıldığında da registerler yazıldığı için iki kere yazılmaması
        // amacıyla yapıyoruz.
            cout << "HLT - " ;
        myCPU.execute(instruction);
        Option (argv[2],instruction,myCPU);
    }
    return 0;
}

void Option (char* parameter,string str,CPU myCPU)
{// argv[2] yi kontrol edip ekrana gerekli yazıları basan fonksiyonumuz.
    string forIf = parameter;//char* şeklindeyken if içinde ==  çalışmadığı için böyle yapıyoruz.
    if (forIf == "1" && str.substr(0,3) != "HLT" )
    {// HLT durumunu mainde kontrol ettiğimiz için burda bakmıyoruz.
        cout<<str<<" - Registers : R1="<<myCPU.get_reg1()<<",R2="<<myCPU.get_reg2();
        cout <<",R3="<<myCPU.get_reg3()<<",R4="<<myCPU.get_reg4()<<",R5=";
        cout <<myCPU.get_reg5()<<endl;
    }
}