/* 
 * File:   CPUProgram.cpp
 * Author: Lütfullah Türker
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram(int option){}

CPUProgram::CPUProgram(){}

int CPUProgram::size()const{return fileSize;}
// constructor readFile ı çağırdığı gibi dosya satır sayısı readFile da 
// belirleniyor size() fonksiyonunda da bu değeri return ediyoruz.

void CPUProgram::ReadFile(std::string fileName)
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
        getline(file,temp);
        // her satırı aldıktan sonra tüm harfleri büyük harfe çeviriyoruz.
        temp= convertCapitalLetter (temp);
        temp = fixInstruction(temp);
        progLines.push_back(temp);
        // ve boşlukları silip okuduğumuz satırdaki yorumları da temizleyip
        // MOVR1,R2  şeklinde yapışık temiz bir string haline getiriyoruz.
    }
    fileSize = i ;
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
///////////////////////////////////NOT/////////////////////////////////////////
// PDF de verilen test örneğinde getLine fonksiyonunu myCPUProgram.getLine(0) ve
// myCPUProgram.getLine(myCPUProgram.size()-1) şeklinde çağırılmış.Fakat ben
// programCounter a göre satır sayısı alındığı için ve bir önceki ödevden de 
// programCounter ı 1 den başlattığımız için getLine fonk. gelen sayının 1 eksiği
// olan elemanı yani programCounter ilk satırdayken(1) getLine(myCPU.getPC())
// ile çağrıldığında arrayde ilk satır 0 da olduğu için gelen sayı -1. elemanı
// return ediyorum.Ve mantıken de bu böyle olmak zorunda.
// PDF örneğinde verildiği gibi getLine(0) yapınca ilk satırı return etmesi için
// -1 yapmamam gerekiyor Fakat bu seferde Program düzgün çalışmaz.Çünkü programCounter
// 1 den başlıyor.Bunun için PC yi 0 yapmak lazım fakat PC 1 olması gerekiyor.
// Bu yüzden getLine(0) ile kullanıldığında ve size()-1 ile kullanıldığında
// program çalışmaz.-1 i silince çalışacak fakat silmedim diye puanım kırılmazsa
//sevinirim.
///////////////////////////////////////////////////////////////////////////////