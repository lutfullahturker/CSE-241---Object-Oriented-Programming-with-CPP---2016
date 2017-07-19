/* 
 * File:   CPUProgram.cpp
 * Author: Lütfullah Türker
 * 
 * Created on 19 October 2016, 20:36
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram(std::string fileName){readFile(fileName);}

int CPUProgram::size()const{return fileSize;}
// constructor readFile ı çağırdığı gibi dosya satır sayısı readFile da 
// belirleniyor size() fonksiyonunda da bu değeri return ediyoruz.

void CPUProgram::readFile(std::string fileName)
{
    int i,lineNum = 0 ;
    std::fstream file;
    std::string temp;
    file.open(fileName);
    if (!file.is_open())
    {// dosya açılamadığı durumda hata verip çıkıyoruz.
        std::cerr << "File Open Failed!!" << std::endl;
        exit (1);
    }// toplam satır sayısını bulmak ve 200 ü geçmemesi için kontrol etmek için
    // dosyanın tamamını başta bir kere okuyoruz.
    for (lineNum = 0; !file.eof();lineNum++)
        getline(file,temp);
    if (lineNum > 200)
    {// dosyanın 200den fazla satır içermesini istemediğimiz için bunu kontrol ediyoruz.
        std::cerr << "Cpu File can't Have More Than 200 Lines.";
        exit (1);
    }
    file.close();
    file.open(fileName);
    for (i=0;!file.eof() ; i++)
    {// bir sorun yoksa okumaya başlıyoruz.
        getline(file,progLines[i]);
        // her satırı aldıktan sonra tüm harfleri büyük harfe çeviriyoruz.
        progLines[i] = convertCapitalLetter (progLines[i]);
        progLines[i] = fixInstruction(progLines[i]);
        // ve boşlukları silip okuduğumuz satırdaki yorumları da temizleyip
        // MOVR1,R2  şeklinde yapışık temiz bir string haline getiriyoruz.
    }
    fileSize = i-1 ;
    // tüm dosyaları okuduktan sonra satır sayısını buluyoruz ve fileSize atıyoruz.
}
std::string CPUProgram::convertCapitalLetter (std::string str)
{// örneğin MOV fonksiyonunun dosyada mOv şeklinde yazılması gibi durumlarda da
 //programımızın doğru çalışması için yazılan yazının tamamını büyük harfe çeviriyoruz.
    int i;
    for (i=0;i<str.size();i++)
        if (str[i] >= 'a' && str[i] <= 'z' )
            str[i] -= 'a' -'A' ;
    // her harfi tek tek küçük harf mi diye kontrol ederek küçükse büyüğe çeviriyoruz.
    return str;
}
std::string CPUProgram::fixInstruction(std::string fixIt)
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

std::string CPUProgram::getLine(int lineNum)const{return progLines[lineNum-1];}
// readFile ile tüm satırları arraye atadığımız için gelen satır sayısına göre
// o satırı return ediyoruz.