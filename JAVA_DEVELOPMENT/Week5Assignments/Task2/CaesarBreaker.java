/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;

public class CaesarBreaker {
  public int[] countLetters(String message) {
    String alphabet = "abcdefghijklmnopqrstuvwxyz";
    int[] counts = new int[26];
    for (int i = 0; i < message.length(); i++) {
      char ch = Character.toLowerCase(message.charAt(i));
      int index = alphabet.indexOf(ch);
      if (index != -1) {
        counts[index]++;
      }
    }
    return counts;
  }
  public int maxIndex(int[] values) {
    int max = 0;
    for (int i = 0; i < values.length; i++){
      if (values[i] > values[max]) {
        max = i;
      }
    }
    return max;
  }
  public String decrypt(String encrypted) {
    CaesarCipher cc = new CaesarCipher();
    int[] freqs = countLetters(encrypted);
    int maxDex = maxIndex(freqs);
    int dkey = maxDex - 4;
    if (maxDex < 4) {
      dkey = 26 - (4 - maxDex); 
    }
    System.out.println("Detected key: " + dkey);
    return cc.encrypt(encrypted, 26 - dkey);
  }
  public String halfOfString(String message, int start) {
    StringBuilder sb = new StringBuilder();
    for (int i = start; i < message.length(); i+= 2) {
      sb.append(message.charAt(i));
    }
    return sb.toString();
  }
  public int getKey(String s) {
    int[] freqs = countLetters(s);
    int maxDex = maxIndex(freqs);
    int dkey= maxDex - 4;
    if (maxDex < 4) {
      dkey = 26 - (4 - maxDex);
    }
    return dkey;
  }
  public String decryptTwoKeys(String encrypted) {
    CaesarCipher cc = new CaesarCipher();
    String half1 = halfOfString(encrypted, 0);
    String half2 = halfOfString(encrypted, 1);
    int key1 = getKey(half1);
    int key2 = getKey(half2);
    System.out.println("Detected keys -> Key1: " + key1 + "; Key2: " + key2);
    return cc.encryptTwoKeys(encrypted, 26 - key1, 26 - key2);
  }
  public void testDecrypt() {
    FileResource fr = new FileResource();
    String encrypted = fr.asString();
    String decrypted = decrypt(encrypted);
    System.out.println("Decrypted message:\n" + decrypted);
  }
  public void testDecryptTwoKeys() {
    FileResource fr = new FileResource();
    String encrypted = fr.asString();
    String decrypted = decryptTwoKeys(encrypted);
    System.out.println("Decrypted message:\n" + decrypted);
  }
  public static void main(String[] args) {
    CaesarBreaker cb = new CaesarBreaker();
    // Option 1: test one-key decryption
    //cb.testDecrypt();
    // Option 2: test two-key decryption
    cb.testDecryptTwoKeys();
  }
}
