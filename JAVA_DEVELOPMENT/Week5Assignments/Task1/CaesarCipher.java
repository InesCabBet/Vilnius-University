/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;
import java.io.*;
import java.util.*;

public class CaesarCipher {
  String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  public int getIndexAlphabet(char ch) {
    ch = Character.toUpperCase(ch);
    for (int i = 0; i < alphabet.length(); i++) {
      if (alphabet.charAt(i) == ch) {
        return i;
      }
    }
    return -1;
  }
  public boolean findInAlphabet(char c){
    c = Character.toUpperCase(c);
    for (int i = 0; i < alphabet.length(); i++) {
      if (alphabet.charAt(i) == c) {
        return true;
      }
    }
    return false;
  }
  public String encrypt (String input, int key) {
    String output = "";
    for (int i = 0; i < input.length(); i++) {
      char ch = input.charAt(i);
      if (findInAlphabet(ch) == false) {
        output += ch;
      } else {
        boolean isLower = Character.isLowerCase(ch);
        int index = getIndexAlphabet(ch);
        int new_index = (index + key) % alphabet.length();
        char new_char = alphabet.charAt(new_index);
        if (isLower) {
          new_char = Character.toLowerCase(new_char);
        }
        output += new_char;   
      }
    }
    return output;
  }
  public void testCeaser() {
    String test = "FIRST LEGION ATTACK EAST FLANK!";
    System.out.println(encrypt(test, 23));
    System.out.println("----- TESTING WITH UPPER OR LOWER CASE -----");
    System.out.println(encrypt("First Legion", 23));
    System.out.println(encrypt("First Legion", 17));       
  }
  public void testCeaserFiles() {
    System.out.println("----- TESTING FROM FILES -----");
    FileResource fr = new FileResource();
    String message = fr.asString();
    System.out.println("Select number key 1-25: ");
    Scanner sc = new Scanner(System.in);
    int key = sc.nextInt();
    sc.nextLine();
    String encrypted = encrypt(message, key);
    System.out.println("key is " + key + "\n" + encrypted);
  }
  public String encryptTwoKeys(String input, int key1, int key2) {
    String output = "";
    for (int i = 0; i < input.length(); i++) {
      char ch = input.charAt(i);
      if (findInAlphabet(ch) == false) {
        output += ch;
      } else {
        boolean isLower = Character.isLowerCase(ch);
        int index = getIndexAlphabet(ch);
        int new_index = 0;
        if (i % 2 == 0) {
          new_index = (index + key1) % alphabet.length();
        } else {
          new_index = (index + key2) % alphabet.length();
        }
        char new_char = alphabet.charAt(new_index);
        if (isLower) {
          new_char = Character.toLowerCase(new_char);
        }
        output += new_char;   
      }
    }
    return output;
  }
  public void testTwoKeys() {
    System.out.println("----- TESTING TWO KEYS -----");
    System.out.println(encryptTwoKeys("First Legion", 23, 17));      
  }
  public static void main(String args[]){
    CaesarCipher cc = new CaesarCipher();
    cc.testCeaser();
    cc.testCeaserFiles();
    cc.testTwoKeys();
  }
}
