/* 
 * File:   instructionFuctions.cpp
 * Author: Lütfullah TÜRKER
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#include "instructionFuctions.h"

using namespace std;

instructionFuctions::instructionFuctions() {}

void instructionFuctions::Mov (int R[],std::string instruction,Memory* myMemory)
{
    int regNo,regNo2,adress,find = instruction.find(",");
    if ((instruction[2] != ',' && instruction[3] != ',') || (instruction[0] != 'R' && instruction[0] != '#')
            || !((int) (instruction[1]) <= 57 && (int) (instruction[1]) >= 48))
//Mov fonksiyonunda ilk eleman Register olmak zorunda olduğu için kontrol ediyoruz.
// ve gelen string R1,R2 şeklinde olacağı için 3. harf , olmak zorunda.
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
    regNo = static_cast <int> (instruction[1]) - 48 -1;//Register Arrayimizde kullanacağımız
//index sayısını R1 in 2. harfini yani 1 i okuyup integer  1 e çevirmek için
// 48 çıkarıyoruz ve array elemanları 0 dan başlayıp R5 in arrayde R[4] de olması
//sebebiyle -1  çıkartarak indexi buluyoruz.
    if (instruction[0] == '#')
    {
        adress=ConvertInteger(instruction.substr(1,find-1));
        if (static_cast <int> (instruction[find+1]) <= 57 && static_cast <int> (instruction[find+1]) >= 48)
        // ilk elemanın sayı olup olmadığını kontrol edip sayı ise ona göre işlemler yapıyoruz.
            myMemory->setMem(adress,ConvertInteger(instruction.substr(find+1)));
        else if (instruction[find+1] == 'R' && (static_cast <int> (instruction[find+2]) <= 57 && static_cast <int> (instruction[find+2]) >= 48))
        {
            regNo = static_cast <int> (instruction[find+2]) - 48 -1;
            R[regNo] = myMemory->getMem(adress) ;
        }
    }
    else if (static_cast <int> (instruction[3]) <= 57 && static_cast <int> (instruction[3]) >= 48)
    {// işlem yapılacak 2. elemanın sayı olup olmadığını kontrol edip sayı ise ona göre işlemler yapıyoruz.
        R[regNo] = ConvertInteger(instruction.substr(3));
    }
    else if (instruction[3] == 'R' && (static_cast <int> (instruction[4]) <= 57 && static_cast <int> (instruction[4]) >= 48))
    {// bir registerse de ona göre işlemleri yapıyoruz.
        regNo2 = static_cast <int> (instruction[4]) -48 -1 ;//register arrayimizdeki indexi buluyoruz.
        R[regNo2] = R[regNo]; // 2. yazılan registeri ilkinin üstüne yazıyoruz.
    }
    else if (instruction[3] == '#' && (static_cast <int> (instruction[4]) <= 57 && static_cast <int> (instruction[4]) >= 48))
    {
        adress=ConvertInteger(instruction.substr(4));
        myMemory->setMem(adress,R[regNo]);
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
}
void instructionFuctions::Prn (int R[],std::string instruction,Memory* myMemory)
{
    int regNo,adress;
    if (static_cast <int> (instruction[0]) <= 57 && static_cast <int> (instruction[0]) >= 48)
        cout << instruction <<endl;//PRN den sonra gelen karakter sayı ise direk basıyoruz.
    else if (instruction[0] == 'R' && (static_cast <int> (instruction[1]) <= 57 && static_cast <int> (instruction[1]) >= 48))
    {//bir Register ise kontrol edip sayıya çevirip indexini bulup basıyoruz.
        regNo = static_cast <int> (instruction[1]) -48 -1 ;
        cout << R[regNo] << endl;
    }
    else if ( instruction[0] == '#')
    {
        adress=ConvertInteger(instruction.substr(1));
        cout << myMemory->getMem(adress) <<endl;
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
    
}
void instructionFuctions::Sub (int R[],std::string instruction,Memory* myMemory)
{
    int regNo,regNo2,number,adress;
    if (instruction[2] != ',' || (instruction[0] != 'R' && instruction[0] != '#')
            || !((int) (instruction[1]) <= 57 && (int) (instruction[1]) >= 48))
    {// instruction, boşluklar ve ilk 3 harfteki instruction silinerek geldiği için
        // ve Sub da başta register olmak zorunda olduğu için 3. karakterde de 
        // , olmak zorunda
        cerr << "Invalid input" << endl;
        exit(1);
    }
    regNo = static_cast <int> (instruction[1]) - 48 -1;
    if (static_cast <int> (instruction[3]) <= 57 && static_cast <int> (instruction[3]) >= 48)
    {// ikinci değerin sayı olup olmadığı kontrolü yapılıyor.
        number = ConvertInteger(instruction.substr(3));
    // sayı ise stringin içinden sayıyı alıp int e çevirmek için fonksiyon çağrıyoruz.
        R[regNo] -= number;
    }
    else if (instruction[3] == 'R' && (static_cast <int> (instruction[4]) <= 57 && static_cast <int> (instruction[4]) >= 48))
    {// register mi değil mi kontrolü yapılıyor.
        regNo2 = static_cast <int> (instruction[4]) -48 -1 ;
        R[regNo] -= R[regNo2];
    }
    else if (instruction[3] == '#')
    {
        adress=ConvertInteger(instruction.substr(4));
        R[regNo] -= myMemory->getMem(adress);
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
}
void instructionFuctions::Add (int R[],std::string instruction,Memory* myMemory)
{
    int regNo,regNo2,number,adress;
    if (instruction[2] != ',' || instruction[0] != 'R' || !(static_cast <int> (instruction[1]) <= 57 && static_cast <int> (instruction[1]) >= 48))
    {// Sub daki aynı işlemler yapılıyor.
        cerr << "Invalid input" << endl;
        exit(1);
    }
    regNo = static_cast <int> (instruction[1]) - 48 -1;
    if (static_cast <int> (instruction[3]) <= 57 && static_cast <int> (instruction[3]) >= 48)
    {// sayı mı değil mi kontrolü yapılıyor.
        number = ConvertInteger(instruction.substr(3));
        R[regNo] += number;
    }
    else if (instruction[3] == 'R' && (static_cast <int> (instruction[4]) <= 57 && static_cast <int> (instruction[4]) >= 48))
    {// register mi değil mi kontrolü yapılıyor.
        regNo2 = static_cast <int> (instruction[4]) -48 -1 ;
        R[regNo] += R[regNo2];
    }
    else if (instruction[3] == '#')
    {
        adress=ConvertInteger(instruction.substr(4));
        R[regNo] += myMemory->getMem(adress);
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
}
int instructionFuctions::Jmp (int R[],std::string instruction)
{
    int regNo,lineNum;
    if (static_cast <int> (instruction[0]) <= 57 && static_cast <int> (instruction[0]) >= 48)
    {// JMP den sonra sayı girildiyse bu if e giriyor.
        lineNum = ConvertInteger(instruction);
//atlanılmak istenen satır numarasını değişkene atadıktan sonra ProgramCounter ın istenen
//  satırı göstermesi için bu sayıyı return ediyoruz ve execute fonk. da PC ye atıyoruz.
        return lineNum;
    //girilen sayının elimizde kalmasını istediğimiz için bunu integere çevirip
    //return ediyoruz ki set_PC yi bu sayıya eşitleyip istenen satıra gidelim.
    }
    else if (instruction[0] == 'R' && (static_cast <int> (instruction[1]) <= 57 && static_cast <int> (instruction[1]) >= 48))
    {// JMP den sonra Registerin 0 olma şartı var ise onu kontrol ediyoruz.
        if (instruction[2] != ',')
        {
            cerr << "Invalid input" << endl;
            exit (1);
        }
        regNo=static_cast <int> (instruction[1]) -48 -1 ;
        if (R[regNo] == 0)
        {// girilen Register 0 ise aynı şekilde istenen sayıyı okuyup işlemleri yapıyoruz.
            lineNum = ConvertInteger(instruction.substr(3));
            return lineNum;
        }
        else 
        //girilen Register 0 değil ise istenilen satıra gidilmeyeceği için -1 return ediyoruz.
            return -1;
    }
    else
    {
         cerr << "Invalid input" << endl;
         exit (1);
    } 
}

int instructionFuctions::Jpn (int R[],std::string instruction)
{
    int regNo,lineNum;
    if (instruction[0] == 'R' && (static_cast <int> (instruction[1]) <= 57 && static_cast <int> (instruction[1]) >= 48))
    {// JMP den sonra Registerin 0 olma şartı var ise onu kontrol ediyoruz.
        if (instruction[2] != ',')
        {
            cerr << "Invalid input" << endl;
            exit (1);
        }
        regNo=static_cast <int> (instruction[1]) -48 -1 ;
        if (R[regNo] <= 0)
        {// girilen Register 0 ise aynı şekilde istenen sayıyı okuyup işlemleri yapıyoruz.
            lineNum = ConvertInteger(instruction.substr(3));
            return lineNum;
        }
        else 
        //girilen Register 0 değil ise istenilen satıra gidilmeyeceği için -1 return ediyoruz.
            return -1;
    }
    else
    {
         cerr << "Invalid input" << endl;
         exit (1);
    } 
}
int instructionFuctions::Power(int number,int exponent)
{
    // sıradan bir üst alma fonksiyonu.
    int i,result=1 ;
    for(i=0 ;i<exponent ;i++)
        result *= number ;
    return result ;
}
int instructionFuctions::ConvertInteger(std::string str)
{
    int size,total=0,convertedInt,newNum,i ;
    size=str.size() ;//stringin uzunluğunu buluyoruz.   
    for(i=0 ;i<size ;i++)
    {
        if (i != size-1 || str[size-1] != ',')
        {
            convertedInt=str[i]-48 ;//karakteri integera çevirdik.
            if (str[size-1] == ',')
                newNum=convertedInt*Power(10,size-(i+2));
            // son harfin , olduğu durumda basamak sayısını 1 fazla alıp 35 i 350
            //bulmaması için üs fonksiyonunda , olduğu durumda bir eksiğini üs alıyoruz.
            else 
                newNum=convertedInt*Power(10,size-(i+1));
            //math kütüphanesi kullanmamak için yazdığımız (power) üst alma fonksiyonu
            // ile her karakterin basamak sayısına göre üssünü alıp işlemleri yapıyoruz.               
            total += newNum ;//bulduğumuz sonuçları toplayarak sayıyı tam olarak çevirmiş oluyoruz.
        }
    }
    return total ;
}