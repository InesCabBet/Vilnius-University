/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;

public class WordPlay {
  public boolean isVowel(char ch){
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
      return true;
    }
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
      return true;
    }
    return false;
  }
  public void testIsVowel() {
    System.out.println("---- TESTING isVowel ----");
    char[] array = {'F', 'a', 'g', 'U'};
    for (char c : array) {
      if (isVowel(c) == true){
        System.out.println("The letter " + c + " is a vowel.");
      } else {
        System.out.println("The letter " + c + " is not a vowel.");   
      }
    }
  }
  public String replaceVowels(String phrase, char ch) {
    String output = "";
    for (int i = 0; i < phrase.length(); i++) {
      if (isVowel(phrase.charAt(i)) == true) {
        output += ch;
      } else {
        output += phrase.charAt(i);
      }
    }
    return output;
  }
  public void testerReplaceVowels() {
    System.out.println("---- TESTING replaceVowels ----");
    String test1 = "Hello World. I'm Ines";
    System.out.println(test1 + " -> " + replaceVowels(test1,'9'));
  }
  public String emphasize(String phrase, char ch) {
    String output = "";
    for (int i = 0; i < phrase.length(); i++) {
      char current = Character.toLowerCase(phrase.charAt(i));
      if (current == Character.toLowerCase(ch)) {
        if ((i + 1) % 2 == 0) {
          output += '*';
        } else {
          output += '+';
        }
      } else {
        output += phrase.charAt(i);
      }
    }
    return output;
  }
  public void testEmphasize() {
    System.out.println("---- TESTING emphasize ----");
    System.out.println(emphasize("dna ctgaaactga", 'a'));
    System.out.println(emphasize("Mary Bella Abracadabra", 'a'));
  }
  public static void main(String args[]) {
    WordPlay wp = new WordPlay();
    wp.testIsVowel();
    wp.testerReplaceVowels();
    wp.testEmphasize();
  }
}
