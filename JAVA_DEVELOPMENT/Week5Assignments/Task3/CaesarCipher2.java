/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;

public class CaesarCipher2 {
  private String alphabet;
  private String shiftedAlpha1;
  private String shiftedAlpha2;
  private int mainKey1;
  private int mainKey2;
  
  public CaesarCipher2(int key1, int key2) {
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shiftedAlpha1 = alphabet.substring(key1) + alphabet.substring(0, key1);
    shiftedAlpha2 = alphabet.substring(key2) + alphabet.substring(0, key2);
    mainKey1 = key1;
    mainKey2 = key2;
  }
  public String encrypt(String input) {
    StringBuilder encrypted = new StringBuilder(input);
    for (int i = 0; i < encrypted.length(); i++) {
      char currChar = encrypted.charAt(i);
      char upperChar = Character.toUpperCase(currChar);
      int idx = alphabet.indexOf(upperChar);
      if (idx != -1) {
        char newChar;
        if (i % 2 == 0) { // even index -> key1
          newChar = shiftedAlpha1.charAt(idx);
        } else {          // odd index -> key2
          newChar = shiftedAlpha2.charAt(idx);
        }
        if (Character.isLowerCase(currChar)) {
          newChar = Character.toLowerCase(newChar);
        }
        encrypted.setCharAt(i, newChar);
      }
    }
    return encrypted.toString();
  }
  public String decrypt(String input) {
    CaesarCipher2 cc = new CaesarCipher2(26 - mainKey1, 26 - mainKey2);
    return cc.encrypt(input);
  }
}
