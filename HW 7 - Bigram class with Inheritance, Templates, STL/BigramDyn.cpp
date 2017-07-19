/* 
 * File:   BigramDyn.cpp
 * Author: Lütfullah TÜRKER
 * 
 * Created on 14 December 2016, 21:46
 */

#include "BigramDyn.h"

template <class T>
BigramDyn<T>::BigramDyn() {
    capacity = 10;
    bigram = new T[capacity];  // başlangıç olarak 10 yer alıyor sonra kontrol ederek artırıyoruz.
    size = 0;
}
template <class T>
BigramDyn<T>::BigramDyn(int dataType){
    capacity = 10;
    bigram = new T[capacity];
    size = 0;
}

template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn<T>& bigram2)
{// dinamik olduğu için big TREE yapıyoruz.
    bigram = new T[bigram2.capacity];
    capacity = bigram2.capacity;
    size = bigram2.size;
    for (int j = 0;j < size;++j)
        bigram[j] = bigram2.bigram[j];
}

template <class T>
BigramDyn<T>::~BigramDyn() {
    delete [] bigram;
}

template<class T>
void BigramDyn<T>::readFile(std::string fileName) throw (std::exception)
{// dosya açılamadıysa exception sınıfımızı fırlatıyoruz (içinde bir string ile birlikte).
    fstream file;
    int i;
    file.open(fileName);
    if (file.fail())
        throw FileError ("File Open Failed !!!");
    T tmp; // temp tutup dosyadan okuduklarımızı tempe yazıp tempten aktarıyoruz.
    for (i=0;file >> tmp;++i)
    {
        if (size >= capacity)
        {// kapasite dolarsa yeniden yer alma döngüsünden kapasiteyi artırıyoruz.
            T* temp =new T[capacity +10];
            for (int i =0;i<size;++i)
                temp[i] = bigram[i];
            delete [] bigram;
            bigram = temp ;
            capacity += 10 ;
        } 
        bigram[i] = tmp;
        size ++;
    } // okunan tip değişmesi (t4.txt deki gibi) gibi olası dosyanın sonuna kadar okuyamama durumlarında
    // aşağıdaki exceptionumuzu fırlatıyoruz.
    if (!file.eof())
        throw FileError ("The Program could not be reached at the end of file !!");
    file.close();
}
template<class T>
int BigramDyn<T>::numGrams() throw(exception)
{// hiç readfile fonksiyonu çağrılıp map doldurulmadıysa exception fırlatıyoruz.
    if (size == 0)
        throw FileError("Array size = 0  Please Read the Correct File!!!");
    return (size-1);
}
template<class T>
int BigramDyn<T>::numOfGrams(T first,T second)
{// for döngüleri ile girilen sayıdan kaç tane olduğunu hesaplayıp return ediyoruz.
    int count = 0;
    try
    {
    for (int i=0;i<numGrams();++i)
    {
        if (bigram[i] == first && bigram[i+1] == second)
            count ++;
    }
    }
    catch (exception& e)
    {
            cout << e.what()<<endl;
    }
    return count;
}
template<class T>
pair<T, T> BigramDyn<T>::maxGrams() 
{// en çok tekrar eden bigramı içiçe döngü ile bulup pair şeklinde return ediyoruz.
    int max = 0;
    int count =0;
    int tmp =0;
    for (int i=0;i<numGrams();++i)
    {
        for (int j=0;j<numGrams();++j)
        {
            if (bigram[i] == bigram[j] && bigram[i+1] == bigram[j+1])
                count ++;
            if (count > max)
            {
                max = count;
                tmp = i;  // maximumu bulduğumuz index bize lazım olduğu için tmp de indexi tutuyoruz.
            }
        }
        count = 0;
    } //  ve max ı bulduğumuz index tmp de olduğu için ona göre bulduğumuz indexi return ediyoruz.
    return pair<T,T>(bigram[tmp],bigram[tmp+1]);
}
template<class T>
std::ostream& BigramDyn<T>::printFunc(ostream& stream)throw (std::exception)
{// cout friend old. için virtual yardımcı fonksiyonumuzu çağrıp polymorfizmi sağlıyoruz.
    if (size == 0) // Eğer dosya okunmadan boş map ekrana basılmak istenirse exception fırlatıyoruz.
        throw FileError("File Reading is Failed!!");
    pair<T,T>* bigramArr =new pair<T,T>[size-1]; // sıralamak için bigramları tutacağımız pair arrayi oluşturuyoruz.
    for (int i=0;i<size-1;++i)
    {
        bigramArr[i].first=bigram[i];
        bigramArr[i].second=bigram[i+1];
    }// pair arrayimizi tek tek dolduruyoruz.
    int* countArr =new int [size-1]; // ve hangi bigramın kaaç kere tekrar ettiğini
    // tutmak için bigram indexleriyle aynı indexe sahip elemanlarda o bigramın kaç kere tekrarlandığını tutuyoruz.
    // bu yüzden başlangıçta tüm elemanları 0 yapıyoruz.
    for (int i=0;i<size-1;++i)
        countArr[i]=0;
    int count = 1;
    int tmp;
    pair<T,T> temp; // sıralama yapmak ve elemanları yer deiştirmek için temp.
    for (int i=0;i<size-1;++i)
    {
        tmp = i;
        countArr[i] ++;
        for (int j=i+1;j<size-1;++j)
        { // sıralama algoritması
            if (bigramArr[i].first == bigramArr[j].first && bigramArr[i].second == bigramArr[j].second)
            {
                temp = bigramArr[j];
                bigramArr[j] = bigramArr[++tmp];
                bigramArr[tmp] = temp;
                countArr[i] ++;
            }
        }
        i = tmp;
    }
    cout << "Sequence in decreasing frequency order.\n";
    int max = 0; // sıraladıktan sonra en çok tekrar eden indexe göre ekrana
    // büyükten küçüğe sıralı şekilde ve kaç kere tekrar edildiğini yazan
    // karmaşık algoritma.
    int temp1 = 0;
    for (int j=0;j<size-1;++j)
    {
        for (int i=0;i<size-1;++i)
        {
            if (countArr[i] > max)
            {
                max = countArr[i];
                temp1 = i;
            }
        }
        if (countArr[temp1] != 0)
        { // aynı elemanı kaç kere tekrar ediyorsa o kadar tekrar tekrar yazmaması için
        // bu if i koyuyor ve hepsini bir kere yazıyoruz.
        cout << "("<<bigramArr[temp1].first<<" , "<<bigramArr[temp1].second<<")";
        cout <<" has "<<max<<" in the sequence.\n";
        }
        max = 0;
        countArr[temp1] = 0;
    }
    delete [] countArr; // yazma bitince kullandığımız yardımcı arraylerimizi siliyoruz.
    delete [] bigramArr;
    return stream;
}

template <class T>
BigramDyn<T>& BigramDyn<T>::operator=(const BigramDyn<T>& bigram2)
{ // dinamik old. için big TREE yapılmalı
// kendimize atanıp atanmadığımızı kontrol etmek zorundayız.
    if (this == &bigram2)
        return *this;
    delete [] bigram;
    bigram = new T[bigram2.capacity];
    capacity = bigram2.capacity;
    size = bigram2.size;
    for (int j = 0;j < size;++j)
        bigram[j] = bigram2.bigram[j];
    return *this;
}
