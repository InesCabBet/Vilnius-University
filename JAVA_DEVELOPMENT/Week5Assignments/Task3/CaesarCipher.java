/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

public class CaesarCipher {
  private String alphabet;
  private String shiftedAlphabet;
  private int mainKey;
  
  public CaesarCipher(int key) {
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shiftedAlphabet = alphabet.substring(key) + alphabet.substring(0,key);
    mainKey = key;
  }
  public String encrypt(String input){
    StringBuilder encrypted = new StringBuilder(input);
    for (int i = 0; i < encrypted.length(); i++) {
      char current = encrypted.charAt(i);
      int index = alphabet.indexOf(Character. toUpperCase(current));
      if (index != -1) {
        char newChar = shiftedAlphabet.charAt(index);
        if (Character.isLowerCase(current)) {
          newChar = Character.toLowerCase(newChar);
        }
        encrypted.setCharAt(i, newChar);
      }
    }
    return encrypted.toString();
  }
  public String decrypt(String input) {
    CaesarCipher cc = new CaesarCipher(26 - mainKey);
    return cc.encrypt(input);
  }
}
