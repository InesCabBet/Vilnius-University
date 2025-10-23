/**
 * Write a description of WordFrequencies here.
 * 
 * @author Ines Cabrera Betancor
 * @version 23 OCT 2025
 */

import edu.duke.*;
import java.util.*;

public class WordFrequencies {
  private ArrayList<String> myWords;
  private ArrayList<Integer> myFreqs;
  public WordFrequencies() {
    myWords = new ArrayList<String>();
    myFreqs = new ArrayList<Integer>();
  }
  public int existsInWords(String word) {
    for (int i = 0; i < myWords.size(); i++) {
      if (myWords.get(i).equals(word)) {
        return i;
      }
    }
    return -1;
  }
  public void findUnique() {
    myWords.clear();
    myFreqs.clear();
    FileResource fr = new FileResource();
    for (String word : fr.words()) {
      word = word.toLowerCase();
      int check = existsInWords(word);
      if (check != -1) {
        int freq = myFreqs.get(check);
        myFreqs.set(check, freq + 1);
      } else {
        myWords.add(word);
        myFreqs.add(1);
      }
    }
  }
  public void tester() {
    findUnique();
    System.out.println("--- UNIQUE WORDS ---");
    int counter = 0;
    for(int i = 0; i < myFreqs.size(); i++) {
      System.out.println(myFreqs.get(i) + "   " + myWords.get(i));
      if (myFreqs.get(i) == 1) {
        counter++;
      }
    }
    System.out.println("Number of unique words: " + counter);
    int index = findIndexOfMax();
    System.out.println("The word that occurs most often and its count are: " + myWords.get(index) + " " + myFreqs.get(index));
  }
  public int findIndexOfMax() {
    int max = 0;
    for(int i = 0; i < myFreqs.size(); i++) {
      if (myFreqs.get(i) > myFreqs.get(max)) {
        max = i;
      }
    }
    return max;
  }
  public static void main() {
    WordFrequencies wf = new WordFrequencies();
    wf.tester();
  }
}