/* 
 * File:   BigramDyn.h
 * Author: Lütfullah TÜRKER
 *
 * Created on 14 December 2016, 21:46
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include "Bigram.h"

using namespace std;


template <class T>
class BigramDyn : public Bigram<T>{
public:
    BigramDyn();
    BigramDyn(int dataType);
    BigramDyn(const BigramDyn& orig);
    virtual ~BigramDyn();

    BigramDyn& operator=(const BigramDyn& bigram2);
    virtual void readFile(std::string fileName) throw (std::exception)override;
    virtual int numGrams() throw(exception) override ;
    virtual int numOfGrams(T first,T second  )override;
    virtual std::ostream& printFunc(ostream& stream  )throw (std::exception)override;
    virtual std::pair<T, T> maxGrams() override ;
private:
    T* bigram;
    int size;
    int capacity;
};

#endif /* BIGRAMDYN_H */

