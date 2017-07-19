
import java.util.Objects;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author osboxes
 * @param <T>
 * @param <N>
 */
public class Pair<T,N> {
// Java da Pair sınıfı olmadığı için kendim Pair class ı yazdım.Aynı görevi görüyor.
  private  T left;
  private  N right;

  public Pair() {super();}
  
  public Pair(T left, N right) {
      super();
    this.left = left;
    this.right = right;
  }

  public T getLeft() { return left; }
  public N getRight() { return right; }
  public void setLeft(T set) { left = set; }
  public void setRight(N set) { right = set; }


    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Pair<?, ?> other = (Pair<?, ?>) obj;
        if (!Objects.equals(this.left, other.left)) {
            return false;
        }
        if (!Objects.equals(this.right, other.right)) {
            return false;
        }
        return true;
    }
  
  public int hashCode() {
        int hashFirst = left != null ? left.hashCode() : 0;
        int hashSecond = right != null ? right.hashCode() : 0;

        return (hashFirst + hashSecond) * hashSecond + hashFirst;
    }

}
