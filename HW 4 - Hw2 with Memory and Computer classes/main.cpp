/* 
 * File:   main.cpp
 * Author: Lütfullah TÜRKER
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#include "CPU.h"
#include "CPUProgram.h"
#include "Computer.h"

// Class larımızı include ediyoruz.Bu class larda iostream ,fstream, string gibi
//include işlemleri zaten yapıldığı için main de de kullanabiliyoruz.
// Bu yüzden burda tekrar iostream gibi gerekli include leri yazmadık.
using namespace std;



int main(int argc, char** argv) 
{
    if ( argc != 3)
    {// dosya adının veya run option ın girilmediği durumda argc 2 veya 1 
        // olacağından bunu kontrol ediyoruz.
        cerr << "Please Enter Run Parameters !" << endl;
        return 1;
    }
    if (argv[2][1] >0)
    {// run parametresinin  1  dışında 15 gibi bir sayı girildiğinde de ilk 
//karakterindeki sayıya bakıldığı için 1 i alıp hatasız çalışmak yerine hata veriyor.
        cerr << "Invalid input" << endl;
        exit(1);
    }
    int option = argv[2][0] -48;
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    Memory myMemory(option);
    myCPUProgram.ReadFile((string)argv [1]);
    Computer myComputer(myCPU,myCPUProgram,myMemory,option);
    string instruction;
    if (option != 0 && option != 1 && option!= 2)
    {// run option ın 0 , 1 ve 2 dışında olmaması gereken bir değer girilmesi durumu
        cerr << "Run Option Can Be Only 0 , 1 or 2 !" << endl;
        return 1;
    }
    myComputer.execute();
////////////////////////////////NOT////////////////////////////////////////////
// PDF de verilen test örneğinde myCPU.execute fonksiyonuna myCPU.execute("MOV #0, R1", myMemory);
// şeklinde string gönderilmiş.Fakat ben ödevin amacı dosyadan okuyup istenen işlemleri
// yapmak olduğu için instruction stringinin temizlenme(boşlukları silme vb.) işlemlerini
// readFile fonksiyonunda yapıp MOV#0,R1 şeklinde boşluksuz olarak array e yazıyorum.
// Bu sebepten test için gönderilen boşluklu instruction bende hata verir.Ve bu
// hatayı düzeltmek için CPUProgramda yazdığım fixInstruction fonksiyonunu CPU
// class ına almam gerekiyor.Fakat PDF deki şekilde kullanımı bana uygun gelmediği
// için değiştirmedim.
///////////////////////////////////////////////////////////////////////////////
    return 0;
}