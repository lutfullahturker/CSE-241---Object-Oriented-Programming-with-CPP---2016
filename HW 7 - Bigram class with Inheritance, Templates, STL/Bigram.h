/* 
 * File:   Bigram.h
 * Author: osboxes
 *
 * Created on 14 December 2016, 21:50
 */

#ifndef BIGRAM_H
#define BIGRAM_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

template <class T>
class Bigram {
public:// tüm fonksiyonları pure virtual olcak şekilde =0 yazıyorum ve class objesi oluşturulamıyor.
    Bigram();
    Bigram(int dataType);
    Bigram(const Bigram<T>& orig);
    virtual ~Bigram();
    virtual void readFile(std::string fileName) throw (std::exception) = 0;
    virtual int numGrams() = 0;  
    virtual int numOfGrams(T first,T second) =0;
    virtual std::ostream& printFunc(std::ostream& stream)throw (std::exception)=0;
    friend std::ostream& operator<<(std::ostream& stream,Bigram<T> &printIt)
    {return printIt.printFunc(stream);}
    virtual std::pair<T, T> maxGrams() = 0; 
private:

};
// exception class ımı burada yazdım diğer derived classlar a da ulaşması için.
class FileError : public exception{
public:// gelen stringi döngü ile C deki gibi alıp what() da print yapıyoruz.
    FileError(const char* print){
        for (int i=0;print[i]!='\0';++i){
        printEx[i]=print[i];}
        }
    virtual ~FileError(){delete [] printEx;}
    virtual const char* what() const throw() override{return printEx;}
private:
    char * printEx=new char[100];
};

#endif /* BIGRAM_H */

