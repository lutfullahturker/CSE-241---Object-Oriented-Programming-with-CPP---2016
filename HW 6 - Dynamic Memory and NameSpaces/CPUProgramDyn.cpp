/* 
 * File:   CPUProgramDyn.cpp
 * Author: Lütfullah TÜRKER
 * 
 * Created on 25 November 2016, 14:09
 */

#include "CPUProgramDyn.h"

using namespace std;

namespace DynamicCPUProg
{
CPUProgramDyn::CPUProgramDyn() {
    capacity = 2;
    used = 0;
    progLines = new string[capacity];
    option = 0;
    fileSize = 0;
}
CPUProgramDyn::CPUProgramDyn(int runOption){
    capacity = 2;
    used = 0;
    progLines = new string[capacity];
    option =runOption;
    fileSize = 0;
}

CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& prog2) {
    // copyConstructor da herşeyi birbirine eşitliyoruz.
    progLines = new string[prog2.capacity];
    capacity = prog2.capacity;
    fileSize = prog2.fileSize;
    option = prog2.option;
    used = prog2.used;
    for (int j = 0;j < used;++j)
        progLines[j] = prog2.progLines[j];
}

CPUProgramDyn::~CPUProgramDyn() {
    delete [] progLines;
}

int CPUProgramDyn::size()const{return fileSize;}
// readFile ı çağırdığı gibi dosya satır sayısı readFile da 
// belirleniyor size() fonksiyonunda da bu değeri return ediyoruz.

void CPUProgramDyn::ReadFile(std::string fileName)
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
        used ++;
        progLines[used-1] = temp;
        if (used == capacity)
        {// kullanılan ve kapasite olarak iki ayrı integer tuttuk.
         // ve kapasite kadar kullanılan eleman varsa kapasiteyi iki katına çıkardık.
            string *temp1 = new string[capacity*2];
            for (int j = 0;j < used;++j)
                temp1[j] = progLines[j];
            delete [] progLines;
            progLines = temp1 ;
            capacity *= 2 ;
        }
    }
    fileSize = i ;
    // tüm dosyaları okuduktan sonra satır sayısını buluyoruz ve fileSize atıyoruz.
}
std::string CPUProgramDyn::getLine(int lineNum)const{return progLines[lineNum];}
// readFile ile tüm satırları arraye atadığımız için gelen satır sayısına göre
// o satırı return ediyoruz.

//////////////////////////OPERATOR OVERLOADINGS////////////////////////////////

std::string CPUProgramDyn::operator [](const int lineNum)
{ // return edilen satır değiştirilebilmesi için referans kullandık.
    if (lineNum >= used || lineNum < 0)
    {
        std::cerr << "Invalid Input ! (Out Of Index!)" ;
        string temp ="";
        return temp;
    }// hata durumunda boş string return edilmesi söylendiği için böyle yaptık.
    return progLines[lineNum];
}
const std::string CPUProgramDyn::operator [](const int lineNum)const
{
    if (lineNum >= used || lineNum < 0)
    {
        std::cerr << "Invalid Input ! (Out Of Index!)";
        string temp ="";
        return temp;
    }
    return progLines[lineNum];
}
const CPUProgramDyn CPUProgramDyn::operator +(const std::string& addStr)const
{ // gelen string ve class içindeki değişkenler değişmediği için const kullandık.
    CPUProgramDyn resultProg(option);
    // toplamı return etmek için temp CPUProgramDyn oluşturuyoruz.Ve kendimize eşitliyoruz.
    resultProg = *this;
    // eklemeyi kendi üzerimizde uygulamayacağımız için temp üzerinde uyguluyoruz.
    if (used == capacity)
    {// used==capacity ise eklenecek yer olmadığı için kapasiteyi artırıyoruz.
        string *temp1 = new string[capacity+1];
        for (int j = 0;j < used;++j)
            temp1[j] = progLines[j];
        delete [] resultProg.progLines;
        resultProg.progLines = temp1 ;
        resultProg.capacity ++ ;
    }
    resultProg.progLines[used] = addStr;
    resultProg.used++;
    resultProg.fileSize ++;
    // bir satır daha eklediğimiz için size ı 1 artırıyoruz.
    return resultProg;  // toplamı tuttuğumuz temp i return ediyoruz.
}
const CPUProgramDyn& CPUProgramDyn::operator +=(const std::string& addStr)
{// + işlemini  kendi üzerimizde uygulayarak yaptığımız operatör.
 // *this deki kendi data memberlarımızı değiştirdiğimiz için sonda const yok.
    if (used == capacity)
    {
        string *temp1 = new string[capacity+1];
        for (int j = 0;j < used;++j)
            temp1[j] = progLines[j];
        delete [] progLines;
        progLines = temp1 ;
        capacity ++ ;
    }
    progLines[used] = addStr;
    ++used ;
    ++fileSize  ;
    return *this ;
}
const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& prog2)const
{
    // aynı şekilde temp oluşturup ikinci CPUProgramDyn objesindeki satırları döngü ile
    // temp e ekliyoruz. ve tempi return ediyoruz.
    CPUProgramDyn newProg(option);
    newProg = (*this);
    if (used+prog2.used >= capacity)
    {
        delete [] newProg.progLines;
        newProg.progLines = new string[used+prog2.used+1];
        for (int j = 0;j < used;++j)
            newProg.progLines[j] = progLines[j];
        newProg.capacity = used+prog2.used+1 ;
    }
    for (int i = 0;i < prog2.used;++i)
        newProg.progLines[used+i] = prog2.progLines[i];
    newProg.used = used+prog2.used;
    newProg.fileSize = prog2.fileSize + fileSize ;
    return newProg ;
}
const bool CPUProgramDyn::operator ==(const CPUProgramDyn& compare)const
{
    return (fileSize == compare.fileSize);
}
const bool CPUProgramDyn::operator !=(const CPUProgramDyn& compare)const
{
    return !(*this == compare) ;
}
const bool CPUProgramDyn::operator <(const CPUProgramDyn& compare)const
{
    if (fileSize < compare.fileSize)
        return true;
    else 
        return false ;
}
const bool CPUProgramDyn::operator >=(const CPUProgramDyn& compare)const
{// birbirinin tersi olduğu için kolay yoldan bu şekilde return yapıyoruz.
    return !(*this < compare);
}
const bool CPUProgramDyn::operator >(const CPUProgramDyn& compare)const
{
    if (fileSize > compare.fileSize)
        return true;
    else 
        return false ;
}
const bool CPUProgramDyn::operator <=(const CPUProgramDyn& compare)const
{
    return !((*this) > compare);
}
std::ostream& operator <<(std::ostream& output,const CPUProgramDyn& print)
{// son satırı yazınca alt satıra geçmemesi için onu ayrı yazıyoruz.
    if (print.fileSize >0)
    {
        for (int i =0;i < print.fileSize-1 ; ++i)
        output << print.progLines[i] << std::endl;
        output << print.progLines[print.fileSize -1];
    }
    return output;
}
CPUProgramDyn& CPUProgramDyn::operator --()
{// son satırı array den siliyoruz.
    // bir satır azaldığı için de size ı 1 azaltıyoruz.
    if (used <= 0)
        return *this;
    progLines[used-1] = "";
    used -- ;
    fileSize -- ;
    return *this ;
}
const CPUProgramDyn CPUProgramDyn::operator --(int)
{// post decrement de temp oluşturmak zorunda kalıyoruz.Çünkü azaltılmamış eski
    // halini return etmeliyiz.Bunu da başta temp oluşturarak tempde tutuyoruz.
    if (used <= 0)
        return *this;
    CPUProgramDyn temp(option);
    temp = *this;
    progLines[used-1] = "";
    used -- ;
    fileSize -- ;
    return temp ;
}
const CPUProgramDyn CPUProgramDyn::operator () (const int& num1,const int& num2)const
{// sonucu return edeceğimiz temp  result objesi oluşturuyoruz.
// ilk sayı ikinciden küçükse  ayrı ,büyükse ayrı  döngülerde işlemler yapılıyor.
// Bunun yerine abs fonksiyonu kullanarak daha kısa şekilde de yapabilirdik.
// sayılar satır sayımızdan büyükse hatalı olacağından bunu kontrol ediyoruz.    
    CPUProgramDyn result(option);
    if (num1 > fileSize || num2 > fileSize || num1 < 0 || num2 < 0)
    {
        std::cerr << "Invalid Input ! (Out Of Index!)";
        return result;
    }
    result.capacity = abs(num1-num2)+1;
    delete [] result.progLines;
    result.progLines = new string[result.capacity];
    if (num1 <= num2)
        for (int i =num1,count=0;i<=num2;++i,++count)
            result.progLines[count] = progLines[i-1];
    else 
        for (int i =num2,count=0;i<=num1;++i,++count)
            result.progLines[count] = progLines[i-1];
    result.fileSize = result.capacity;
    result.used = result.capacity;
    return result ;
}
CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn& prog2)
{// kendimize atanıp atanmadığımızı kontrol etmek zorundayız.
    if (this == &prog2)
        return *this;
    delete [] progLines;
    progLines = new string[prog2.capacity];
    capacity = prog2.capacity;
    fileSize = prog2.fileSize;
    option = prog2.option;
    used = prog2.used;
    for (int j = 0;j < used;++j)
        progLines[j] = prog2.progLines[j];
    return *this;
}
//////////////////////////OPERATOR OVERLOADINGS////////////////////////////////

}