/* 
 * File:   CPUProgram.cpp
 * Author: Lütfullah Türker
 * No: 141044050         CPP HW4
 * Created on 27 October 2016, 16:52
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram(int runOption){option =runOption;}

CPUProgram::CPUProgram(){option =0;}

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
    for (i=0;!file.eof() ; i++)
    {// bir sorun yoksa okumaya başlıyoruz.
        getline(file,temp);
        progLines.push_back(temp);
    }
    fileSize = i ;
    // tüm dosyaları okuduktan sonra satır sayısını buluyoruz ve fileSize atıyoruz.
}
std::string CPUProgram::getLine(int lineNum)const{return progLines[lineNum];}
// readFile ile tüm satırları arraye atadığımız için gelen satır sayısına göre
// o satırı return ediyoruz.

//////////////////////////OPERATOR OVERLOADINGS////////////////////////////////

std::string& CPUProgram::operator [](const int lineNum)
{ // return edilen satır değiştirilebilmesi için referans kullandık.
    if (lineNum > progLines.size()-1)
    {
        std::cerr << "Invalid Input ! (Out Of Index!)" << std::endl;
        exit(1);
    }
    return progLines[lineNum];
}
const std::string& CPUProgram::operator [](const int lineNum)const
{
    if (lineNum > progLines.size()-1)
    {
        std::cerr << "Invalid Input ! (Out Of Index!)" << std::endl;
        exit(1);
    }
    return progLines[lineNum];
}
const CPUProgram CPUProgram::operator +(const std::string& addStr)const
{ // gelen string ve class içindeki değişkenler değişmediği için const kullandık.
    CPUProgram resultProg(option);
    // toplamı return etmek için temp CPUProgram oluşturuyoruz.Ve kendimize eşitliyoruz.
    resultProg = *this;
    // eklemeyi kendi üzerimizde uygulamayacağımız için temp üzerinde uyguluyoruz.
    resultProg.progLines.push_back(addStr);
    resultProg.fileSize ++;
    // bir satır daha eklediğimiz için size ı 1 artırıyoruz.
    return resultProg;  // toplamı tuttuğumuz temp i return ediyoruz.
}
const CPUProgram& CPUProgram::operator +=(const std::string& addStr)
{// + işlemini  kendi üzerimizde uygulayarak yaptığımız operatör.
 // *this deki kendi data memberlarımızı değiştirdiğimiz için sonda const yok.
    progLines.push_back(addStr);
    fileSize ++ ;
    return *this ;
}
const CPUProgram CPUProgram::operator +(const CPUProgram& prog2)const
{// aynı şekilde temp oluşturup ikinci CPUProgram objesindeki satırları döngü ile
    // temp e ekliyoruz. ve tempi return ediyoruz.
    CPUProgram newProg(option);
    newProg = (*this);
    for (int i =0;i<prog2.fileSize ; ++i)
        newProg.progLines.push_back(prog2.progLines[i]);
    newProg.fileSize = prog2.fileSize + fileSize ;
    return newProg ;
}
const bool CPUProgram::operator ==(const CPUProgram& compare)const
{
    return (fileSize == compare.fileSize);
}
const bool CPUProgram::operator !=(const CPUProgram& compare)const
{
    return !(*this == compare) ;
}
const bool CPUProgram::operator <(const CPUProgram& compare)const
{
    if (fileSize < compare.fileSize)
        return true;
    else 
        return false ;
}
const bool CPUProgram::operator >=(const CPUProgram& compare)const
{// birbirinin tersi olduğu için kolay yoldan bu şekilde return yapıyoruz.
    return !(*this < compare);
}
const bool CPUProgram::operator >(const CPUProgram& compare)const
{
    if (fileSize > compare.fileSize)
        return true;
    else 
        return false ;
}
const bool CPUProgram::operator <=(const CPUProgram& compare)const
{
    return !((*this) > compare);
}
std::ostream& operator <<(std::ostream& output,const CPUProgram& print)
{// son satırı yazınca alt satıra geçmemesi için onu ayrı yazıyoruz.
    for (int i =0;i < print.fileSize-1 ; ++i)
        output << print.progLines[i] << std::endl;
    output << print.progLines[print.fileSize -1];
    return output;
}
CPUProgram& CPUProgram::operator --()
{// son satırı vector den siliyoruz.
    // bir satır azaldığı için de size ı 1 azaltıyoruz.
    progLines.erase(progLines.end());
    fileSize -- ;
    return *this ;
}
const CPUProgram CPUProgram::operator --(int)
{// post decrement de temp oluşturmak zorunda kalıyoruz.Çünkü azaltılmamış eski
    // halini return etmeliyiz.Bunu da başta temp oluşturarak tempde tutuyoruz.
    CPUProgram temp(option);
    temp = *this;
    progLines.erase(progLines.end());
    fileSize -- ;
    return temp ;
}
const CPUProgram CPUProgram::operator () (const int& num1,const int& num2)const
{// sonucu return edeceğimiz temp  result objesi oluşturuyoruz.
// ilk sayı ikinciden küçükse  ayrı ,büyükse ayrı  döngülerde işlemler yapılıyor.
// Bunun yerine abs fonksiyonu kullanarak daha kısa şekilde de yapabilirdik.
// sayılar satır sayımızdan büyükse hatalı olacağından bunu kontrol ediyoruz.    
    CPUProgram result(option);
    if (num1 > fileSize || num2 > fileSize)
    {
        std::cerr << "Invalid Input !" << std::endl;
        exit(1);
    }
    if (num1 <= num2)
        for (int i =num1;i<=num2;++i)
            result.progLines.push_back(progLines[i-1]);
    else 
        for (int i =num2;i<=num1;++i)
            result.progLines.push_back(progLines[i-1]);
    result.fileSize = std::abs(num1-num2) + 1;
    return result ;
}
//////////////////////////OPERATOR OVERLOADINGS////////////////////////////////