/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;
import java.io.*;

public class WordLength {
  public void countWordLengths(FileResource resource, int[] counts){
    for (String word : resource.words()) {
      int length = word.length();
      // check non-letter at beginning
      if (length > 0 && !Character.isLetter(word.charAt(0))) {
        length--;
      }
      // check non-letter at the end
      if (length > 0 && !Character.isLetter(word.charAt(word.length() - 1))) {
        length--;
      }
      // length is not negative
      if (length < 0) {
        length = 0;
      }
      if (length >= counts.length) {
        counts [counts.length - 1]++;
      } else {
        counts[length]++;
      }
    }
  }
  public int indexOfMax(int[] values){
    int maxIndex = 0;
    for (int i = 1; i < values.length; i++) {
      if (values[i] > values[maxIndex]) {
        maxIndex = i;
      }
    }
    return maxIndex;
  }
  public void testCountWordLength() {
    FileResource fr = new FileResource(); 
    int[] counts = new int[31];
    countWordLengths(fr, counts);
    for (int i = 0; i < counts.length; i++) {
      if (counts[i] > 0) {
        if (i == counts.length - 1) {
          System.out.println("Number of words of length 30 or more: " + counts[i]);
        } else {
          System.out.println("Number of words of length " + i + ": " + counts[i]);
        }
      }
    }
    int mostCommonLength = indexOfMax(counts);
    System.out.println("Most common word length is: " + mostCommonLength);
  }
  public static void main(String[] args){
    WordLength wl = new WordLength();
    wl.testCountWordLength();
  }
}
