/**
 * Write a description of CaesarCipher here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 1
 */

import edu.duke.*;

public class TestCaesarCipher {
  public int[] countLetters(String message){
    String alpha = "abcdefghijklmnopqrstuvwxyz";
    int[] counts = new int[26];
    for (int i = 0; i < message.length(); i++) {
      char ch = Character.toLowerCase(message.charAt(i));
      int index = alpha.indexOf(ch);
      if (index != -1) {
        counts[index]++;
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
  public void simpleTests() {
    FileResource fr = new FileResource();
    String message = fr.asString();
    CaesarCipher cc = new CaesarCipher(18);
    String encrypted = cc.encrypt(message);
    System.out.println("------ TEST CAESAR CHIPER ------");
    System.out.println("Encrypted:\n" + encrypted);
    String decrypted = cc.decrypt(encrypted);
    System.out.println("Decrypted:\n" + decrypted);
    System.out.println("Auto-broken:\n" + breakCaesarCipher(encrypted));
  }
  public String breakCaesarCipher(String input) {
    int[] freqs = countLetters(input);
    int maxDex = maxIndex(freqs);
    int dkey = maxDex - 4; // assuming 'e' is most common letter
    if (maxDex < 4) {
      dkey = 26 - (4 - maxDex);
    }
    CaesarCipher cc = new CaesarCipher(dkey);
    return cc.decrypt(input);
  }
  public static void main(){
    TestCaesarCipher tc = new TestCaesarCipher();
    tc.simpleTests();
  }
}
