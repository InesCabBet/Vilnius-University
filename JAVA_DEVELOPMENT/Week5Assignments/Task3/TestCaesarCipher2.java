/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;

public class TestCaesarCipher2 {
  public String halfOfString(String message, int start) {
    StringBuilder half = new StringBuilder();
    for (int i = start; i < message.length(); i += 2) {
      half.append(message.charAt(i));
    }
    return half.toString();
  }
  public int[] countLetters(String message) {
    String alph = "abcdefghijklmnopqrstuvwxyz";
    int[] counts = new int[26];
    for (int i = 0; i < message.length(); i++) {
      char ch = Character.toLowerCase(message.charAt(i));
      int idx = alph.indexOf(ch);
      if (idx != -1) {
        counts[idx]++;
      }
    }
    return counts;
  }
  public int maxIndex(int[] values) {
    int maxIdx = 0;
    for (int i = 0; i < values.length; i++) {
      if (values[i] > values[maxIdx]) {
        maxIdx = i;
      }
    }
    return maxIdx;
  }
  public String breakCaesarCipher(String input) {
    // Split message into two halves
    String half1 = halfOfString(input, 0);
    String half2 = halfOfString(input, 1);
    // Get key for first half
    int[] freqs1 = countLetters(half1);
    int key1 = maxIndex(freqs1) - 4;
    if (key1 < 0) key1 += 26;
    // Get key for second half
    int[] freqs2 = countLetters(half2);
    int key2 = maxIndex(freqs2) - 4;
    if (key2 < 0) key2 += 26;
    System.out.println("Detected keys: " + key1 + ", " + key2);
    CaesarCipher2 cc = new CaesarCipher2(key1, key2);
    return cc.decrypt(input);
  }
  public void simpleTests() {
    FileResource fr = new FileResource();
    String message = fr.asString();
    CaesarCipher2 cc = new CaesarCipher2(17, 3);
    String encrypted = cc.encrypt(message);
    System.out.println("------ TEST CAESAR CIPHER TWO KEYS ------");
    System.out.println("Encrypted:\n" + encrypted);
    String decrypted = cc.decrypt(encrypted);
    System.out.println("Decrypted:\n" + decrypted);
    String autoBroken = breakCaesarCipher(encrypted);
    System.out.println("Auto-broken:\n" + autoBroken);
  }
  public static void main() {
    TestCaesarCipher2 tc = new TestCaesarCipher2();
    tc.simpleTests();
  }
}
