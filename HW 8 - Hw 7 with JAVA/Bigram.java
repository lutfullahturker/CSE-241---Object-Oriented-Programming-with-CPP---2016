/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author osboxes
 * @param <T>
 */
import java.lang.Throwable;
// tüm fonksiyonları subclass larda implement etmek için interface yazıyorum ve class objesi oluşturulamıyor.
public interface Bigram<T> {
    public   void readFile(String fileName) throws Exception;
    public  int numGrams() throws Exception;
    public  <T> int numOfGrams(T first,T second) throws Exception;
    public  String toString();
}
