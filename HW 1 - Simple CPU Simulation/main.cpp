/* 
 * File:   main.cpp
 * Author: Lutfullah Turker
 * No: 141044050
 * Created on 27 September 2016, 18:01
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

void Mov (fstream& cpuFile,int R[],char* parameter);
void Prn (fstream& cpuFile,int R[],char* parameter);
void Sub (fstream& cpuFile,int R[],char* parameter);
void Add (fstream& cpuFile,int R[],char* parameter);
void Hlt (fstream& cpuFile,int R[],char* parameter);
void Jmp (fstream& cpuFile,int R[],char* fileParameter,char* parameter);
void Option1 (char* parameter,string str);
string ConvertCapitalLetter (string str);
int Power(int number,int exponent);
int ConvertInteger(string str);
/*
 * Fonksiyonlarda dosyadan okumaya devam edebilmek için dosyayı gönderiyoruz.
 * Ve register arrayimizde değişiklik yapabilmemiz için arrayi gönderiyoruz.
 * Ve argv nin 1 ile çalıştırılıp çalıştırılmadığını kontrol edip ona göre
 * ekrana basmak için argv[2] yi parameter olarak gönderiyoruz.
 */
int main(int argc, char** argv) {
    fstream cpuFile;
    string readStr,option=argv[2];
    int R[5]={0,0,0,0,0}; //Başlangıçta tüm registerleri 0 a eşitliyoruz.
    if (option != "0" && option != "1")// programın doğru parametrelerle
    // çalıştırılıp çalıştırılmadığını kontrol ediyoruz.
    {
        cerr << "Invalid Run  Option" << endl;
        return -1;
    }
    cpuFile.open(argv[1]);
    cpuFile >> readStr;
    readStr = ConvertCapitalLetter (readStr);
    //okunan Instruction ın tüm harflerini büyük harfe çevirip işlemlere bu
    // şekilde başlıyoruz.
    Option1 (argv[2],readStr);
    // argv[2] nin 1 olup olmadığını kontrol ederek 1 ise ekrana basma işlemlerini gerçekleştiriyor.
    while (readStr != "HLT" && !cpuFile.eof())
    {// HLT okumadığı sürece program çalışmaya devam ediyor.
        if (readStr =="MOV")
            Mov(cpuFile,R,argv[2]);
        else if (readStr == "PRN")
            Prn(cpuFile,R,argv[2]);
        else if (readStr == "SUB")
            Sub(cpuFile,R,argv[2]);
        else if (readStr == "ADD")
            Add(cpuFile,R,argv[2]);
        else if (readStr == "JMP")
            Jmp(cpuFile,R,argv[1],argv[2]);
        else
        {
            cerr <<"Invalid Input" << endl;
            exit (-1);
        }//yanlış yazılmış bir instruction tespit edilince program sonlandırılıyor.
        cpuFile >> readStr;
        readStr = ConvertCapitalLetter (readStr);
        //döngü başındaki 3 işlemi tekrar yaparak yeni instruction okuyup harflerini
        // büyük harfe çevirip option a göre instuctionu ekrana basıyoruz.
        if (readStr != "PRN")
            Option1 (argv[2],readStr);
    }
    if (readStr == "HLT")
        Hlt(cpuFile,R,argv[2]);
    else
        cerr << "Invalid Input" << endl;
    cpuFile.close();
    return 0;
}
void Mov (fstream& cpuFile,int R[],char* parameter)
{
    string str;
    int regNo,regNo2;
    cpuFile >> str;
    str = ConvertCapitalLetter (str);//Registerin de R1 yerine r1 yazılma ihtimaline karşın
    // harflerini büyük harfe çeviriyoruz.
    Option1(parameter,str);// argv[2] option u 1 ise ekrana yazma işlemini gerçekleştiriyoruz.
    regNo = static_cast <int> (str[1]) - 48 -1;//Register Arrayimizde kullanacağımız
    //index sayısını R1 in 2. harfini yani 1 i okuyup integer  1 e çevirmek için
    // 48 çıkarıyoruz ve array elemanları 0 dan başlayıp R5 in arrayde R[4] de olması
    //sebebiyle -1  çıkartarak indexi buluyoruz.
    if (str[0] != 'R' || !(static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))//Mov fonksiyonunda ilk eleman Register olmak zorunda olduğu için kontrol ediyoruz.
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    if (static_cast <int> (str[0]) <= 57 && static_cast <int> (str[0]) >= 48)
    {// ilk elemanın sayı olup olmadığını kontrol edip sayı ise ona göre işlemler yapıyoruz.
        R[regNo] = ConvertInteger(str);
    }
    else if (str[0] == 'R' && (static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {// bir registerse de ona göre işlemleri yapıyoruz.
        regNo2 = static_cast <int> (str[1]) -48 -1 ;//register arrayimizdeki indexi buluyoruz.
        R[regNo2] = R[regNo]; // 2. yazılan registeri ilkinin üstüne yazıyoruz.
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
    getline(cpuFile,str);// instruction lardan sonra yorum olabilme ihtimaline karşı
    //bulunulan satırı yorum olsa da olmasa da direk atlıyoruz ki sıraki inst. a geçelim.
    if ((string)parameter =="1")// argv[2] 1 ise işlem bitince ekrana registerlerimizi basıyoruz.
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<<endl;
}
void Prn (fstream& cpuFile,int R[],char* parameter)
{
    string str;
    int regNo;
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    if (static_cast <int> (str[0]) <= 57 && static_cast <int> (str[0]) >= 48)
        cout << str <<endl;//PRN den sonra gelen karakter sayı ise direk basıyoruz.
    else if (str[0] == 'R' || str[0] == 'r')
    {//bir Register ise kontrol edip sayıya çevirip indexini bulup basıyoruz.
        regNo = static_cast <int> (str[1]) -48 -1 ;
        cout << R[regNo] << endl;
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit (1);
    }
    if ((string)parameter =="1")
    {
        cout << "PRN ";//argv[2] 1 ise önce instruction u execute edeceğimiz için
        // yukarda PRN işlemini yapıp str de PRN den sonraki string olduğu için
        // PRN yi elle yazıp devam ediyoruz.
        Option1(parameter,str);
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<< endl;
    }
    getline(cpuFile,str);// yine sonda yorum olma ihtimaline karşın satırı okuyoruz.
}
void Sub (fstream& cpuFile,int R[],char* parameter)
{
    // Sürekli aynı işlemler uygulandığı için aynı açıklamaları tekrar yazmadım.
    string str;
    int regNo,regNo2,number;
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    regNo = static_cast <int> (str[1]) - 48 -1;
    if (str[0] != 'R' || !(static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    if (static_cast <int> (str[0]) <= 57 && static_cast <int> (str[0]) >= 48)
    {// sayı mı değil mi kontrolü yapılıyor.
        number = ConvertInteger(str);
        R[regNo] -= number;
    }
    else if (str[0] == 'R' && (static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {// register mi değil mi kontrolü yapılıyor.
        regNo2 = static_cast <int> (str[1]) -48 -1 ;
        R[regNo] -= R[regNo2];
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
    getline(cpuFile,str);
    if ((string)parameter =="1")
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<<endl;
}
void Add (fstream& cpuFile,int R[],char* parameter)
{
    string str;
    int regNo,regNo2,number;
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    regNo = static_cast <int> (str[1]) - 48 -1;
    if (str[0] != 'R' || !(static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    if (static_cast <int> (str[0]) <= 57 && static_cast <int> (str[0]) >= 48)
    {// sayı mı değil mi kontrolü yapılıyor.
        number = ConvertInteger(str);
        R[regNo] += number;
    }
    else if (str[0] == 'R' && (static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {// register mi mi değil mi kontrolü yapılıyor.
        regNo2 = static_cast <int> (str[1]) -48 -1 ;
        R[regNo] += R[regNo2];
    }
    else
    {
        cerr << "Invalid input" << endl;
        exit(1);
    }
    getline(cpuFile,str);
    if ((string)parameter =="1")
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<<endl;
}
void Hlt (fstream& cpuFile,int R[],char* parameter)
{
    int i;
    if ((string)parameter =="1")//argv[2] 1 ise bu optionun istediği şekilde registerleri basıyoruz.
        //fakat zaten burda bastığımız için HLT nin kendi bastırdığı registerleri 2 kere yazmasın diye yazmıyoruz.
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<<endl;
    if ((string)parameter =="0")
    {// argv[2] 0 sa da HLT nin kendi register yazdırma döngüsü çalışıyor.
        for (i=0 ; i<5 ; i++)
            cout <<"R"<<i+1<<" "<< R[i] <<" ";
        cout << endl;
    }
    exit(0);
}
void Jmp (fstream& cpuFile,int R[],char* fileParameter,char* parameter)
{
    int regNo,i,lineNum;
    string str;
    cpuFile >> str;
    str = ConvertCapitalLetter (str);
    Option1(parameter,str);
    if (static_cast <int> (str[0]) <= 57 && static_cast <int> (str[0]) >= 48)
    {// JMP den sonra sayı girildiyse bu if e giriyor.
        lineNum = ConvertInteger(str);
        //girilen sayının elimizde kalmasını istediğimiz için bunu integere çevirip
        // lineNum değişkenine atıyoruz.Ve dosyamızı kapatıp tekrar açıp istenen sayı
        // (lineNum) kadar satır atlayarak istediğimiz yere ulaşıyoruz.
        cpuFile.close();
        cpuFile.open(fileParameter);
        for (i=0 ; i<lineNum-1 ; i++)
        //lineNum kadar satır okunsaydı dosya lineNumdan bir sonraki satırın başında olacaktı.
            getline(cpuFile,str);
    }
    else if (str[0] == 'R' && (static_cast <int> (str[1]) <= 57 && static_cast <int> (str[1]) >= 48))
    {// JMP den sonra Registerin 0 olma şartı var ise onu kontrol ediyoruz.
        regNo=static_cast <int> (str[1]) -48 -1 ;
        if (R[regNo] == 0)
        {// girilen Register 0 ise aynı şekilde istenen sayıyı okuyup işlemleri yapıyoruz.
            cpuFile >> str;
            str = ConvertCapitalLetter (str);
            Option1(parameter,str);
            lineNum = ConvertInteger(str);
            cpuFile.close();
            cpuFile.open(fileParameter);
            for (i=0 ; i<lineNum-1 ; i++)
                getline(cpuFile,str);
        }
        else 
        {//girilen Register 0 değil ise istenilen satıra gidilmeyeceği için bu işlemleri yapıyoruz.
            cpuFile >> str;
            str = ConvertCapitalLetter (str);
            Option1(parameter,str);
            getline(cpuFile,str);
        }
    }
    if ((string)parameter =="1")
        cout<<"-R1="<<R[0]<<",R2="<<R[1]<<",R3="<<R[2]<<",R4="<<R[3]<<",R5="<<R[4]<<endl;
}
void Option1 (char* parameter,string str)
{// argv[2] nin 1 olup olmama durumunu kontrol edip ekrana gerekli yazıları basan fonksiyonumuz.
    string forIf = parameter;
    if (forIf == "1")
        cout << str << " ";
}
string ConvertCapitalLetter (string str)
{// örneğin MOV fonksiyonunun dosyada mOv şeklinde yazılması gibi durumlarda da
 //programımızın doğru çalışması için yazılan yazının tamamını büyük harfe çeviriyoruz.
    int i;
    for (i=0;i<str.size();i++)
        if (str[i] >= 'a' && str[i] <= 'z' )
            str[i] -= 'a' -'A' ;
    // her harfi tek tek küçük harf mi diye kontrol ederek küçükse büyüğe çeviriyoruz.
    return str;
}
int Power(int number,int exponent)
{// sıradan bir üst alma fonksiyonu.
    int i,result=1 ;
    for(i=0 ;i<exponent ;i++)
        result *= number ;
    return result ;
}
int ConvertInteger(string str)
{
    int size,total=0,convertedInt,newNum,i ;
    size=str.size() ;//stringin uzunluğunu buluyoruz.    
    for(i=0 ;i<size ;i++)
    {
        convertedInt=str[i]-48 ;//karakteri integera çevirdik.
        newNum=convertedInt*Power(10,size-(i+1));
        //math kütüphanesi kullanmamak için yazdığımız (power) üst alma fonksiyonu
        // ile her karakterin basamak sayısına göre üssünü alıp işlemleri yapıyoruz.               
        total += newNum ;//bulduğumuz sonuçları toplayarak sayıyı tam olarak çevirmiş oluyoruz.
    }
    return total ;
}
