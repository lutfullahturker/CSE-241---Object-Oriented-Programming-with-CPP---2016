/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author osboxes
 */

import java.util.*;
import java.io.*;
import java.lang.reflect.Array;
@SuppressWarnings("unchecked")
public class BigramMap<T> implements Bigram<T>{
    
    private HashMap <Integer,Object> bigram;
    private int size;
    private final int dataType;
    

    BigramMap(int dataType) {
        bigram = new HashMap<>();
        this.dataType = dataType;
        size = 0;
    }

    @Override
    public void readFile(String fileName) throws Exception{
        File file1 = new File(fileName);
        Scanner file;
        // dosya açılamadıysa,yoksa,okunabilir değilse gibi durumlar için
        // exception sınıfımızı fırlatıyoruz (içinde bir string ile birlikte).
        if (!file1.canRead() && !file1.isFile() && !file1.exists())
            throw new FileError("File Open Failed !!!") ;
        try 
        {
            file = new Scanner(new FileReader(fileName));
        }
        catch (FileNotFoundException ex) {
            throw new FileError("File Not Found !!");
        }
        int i ;
        switch (dataType)
        {// DataType a göre okuma yapılcağı için switch ile yapıyoruz.
            case 1: 
                for (i=0;file.hasNextInt() ;++i)
                {// temp tutup dosyadan okuduklarımızı tempe yazıp tempten aktarıyoruz.
                    int temp = file.nextInt();
                    bigram. put(i, temp);
                }
                break;
            case 2:
                for (i=0;file.hasNext() ;++i)
                {
                    String temp = file.next();
                    bigram. put(i, temp);
                }
                break;
            case 3:
                for (i=0;file.hasNextDouble() ;++i)
                {
                    double temp = file.nextDouble();
                    bigram. put(i, temp);
                }
                break;
            default: throw new FileError("You Have Entered Wrong DataType!!");
        }
        size = i;
        // okunan tip değişmesi (testteki t4.txt deki gibi) gibi olası dosyanın sonuna kadar okuyamama durumlarında
    // aşağıdaki exceptionumuzu fırlatıyoruz.
        if ( file.hasNext())
            throw new FileError("The Program could not be reached at the end of file !!");
        if ( size == 0)
            throw new FileError("Array size = 0  Please Read the Correct File!!!");
        file.close();
    }

    @Override
    public int numGrams() throws Exception
    {// hiç readfile fonksiyonu çağrılıp map doldurulmadıysa exception fırlatıyoruz.
        if (size == 0)
            throw new FileError("Array size = 0  Please Read the Correct File!!!");
        return (size-1);
    }

    @Override
    public <T> int numOfGrams(T first, T second) throws Exception
    {// for döngüsü ile girilen sayıdan kaç tane olduğunu hesaplayıp return ediyoruz.
        int count = 0;
        if (size == 0)
            throw new FileError("Array size = 0  Please Read the Correct File!!!");
        for (int i=0;i<numGrams();++i)
        {
            if (bigram.get(i).equals(first) && bigram.get(i+1).equals(second))
                count ++;
        }
        return count;
    }
    @Override
    public String toString() 
    {
        String stream;
        if (size == 0)
        // Eğer dosya okunmadan boş map ekrana basılmak istenirse exception gibi string return ediyoruz.
            return "Array size = 0  Please Read the Correct File!!!";
        Pair<T,T>[] bigramArr = (Pair<T,T>[])Array.newInstance(Pair.class, size-1);
        for (int i=0;i<size-1;++i)
        {// sıralamak için bigramları tutacağımız pair arrayi oluşturuyoruz.
            bigramArr[i] = new Pair<>();
            bigramArr[i].setLeft((T)bigram.get(i));
            bigramArr[i].setRight((T)bigram.get(i+1));
        }// ve hangi bigramın kaaç kere tekrar ettiğini
    // tutmak için bigram indexleriyle aynı indexe sahip elemanlarda o bigramın kaç kere tekrarlandığını tutuyoruz.
    // bu yüzden başlangıçta tüm elemanları 0 yapıyoruz.
        int[] countArr =new int [size-1];
        for (int i=0;i<size-1;++i)
            countArr[i]=0;
        int count = 1;
        int tmp;
        // sıralama yapmak ve elemanları yer deiştirmek için temp.
        Pair<T,T> temp = new Pair<>();
        for (int i=0;i<size-1;++i)
        {
            tmp = i;
            countArr[i] ++;
            for (int j=i+1;j<size-1;++j)
            {
                if (bigramArr[i].getLeft().equals(bigramArr[j].getLeft()) && bigramArr[i].getRight().equals(bigramArr[j].getRight()))
                {
                    temp.setLeft(bigramArr[j].getLeft());
                    temp.setRight(bigramArr[j].getRight());
                    bigramArr[j].setLeft(bigramArr[++tmp].getLeft());
                    bigramArr[j].setRight(bigramArr[tmp].getRight());
                    bigramArr[tmp].setLeft(temp.getLeft());
                    bigramArr[tmp].setRight(temp.getRight());
                    countArr[i] ++;
                }
            }
            i = tmp;
        }// sıraladıktan sonra en çok tekrar eden indexe göre ekrana
    // büyükten küçüğe sıralı şekilde ve kaç kere tekrar edildiğini yazan
    // karmaşık algoritma.
        stream = "Sequence in decreasing frequency order.\n";
        int max = 0;
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
            {// aynı elemanı kaç kere tekrar ediyorsa o kadar tekrar tekrar yazmaması için
        // bu if i koyuyor ve hepsini bir kere yazıyoruz.
           stream = stream + "(" + bigramArr[temp1].getLeft() + " , " + bigramArr[temp1].getRight() + ")";
           stream = stream + " has " + max + " in the sequence.\n";
            }
            max = 0;
            countArr[temp1] = 0;
        }
        return stream;
    }

    
    
}
