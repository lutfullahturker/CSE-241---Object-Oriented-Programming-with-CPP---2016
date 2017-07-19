/* 
 * File:   BigramMap.h
 * Author: Lütfullah TÜRKER
 *
 * Created on 14 December 2016, 21:45
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <fstream>
#include "Bigram.h"

using namespace std;

template <class T>
class BigramMap : public Bigram<T>{
public:
    BigramMap();
    BigramMap(int dataType);
    
    virtual void readFile(std::string fileName) throw (std::exception)override;
    virtual int numGrams() throw(exception) override;  
    virtual int numOfGrams(T first,T second) override;
    virtual std::ostream& printFunc(ostream& stream  )throw (std::exception)override;
    virtual std::pair<T, T> maxGrams() override;
private:
    map <int,T> bigram;
    int size;
};
#endif /* BIGRAMMAP_H */

