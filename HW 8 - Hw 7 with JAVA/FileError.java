/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author osboxes
 */
// Kendi exception sınıfımı yazdım Gelen string ile birlikte super class ın constructorunu çağırıyoruz.
import java.lang.Throwable;
@SuppressWarnings("serial")
public class FileError extends Exception {

    public FileError(String print){
        super(print);
        }
}
