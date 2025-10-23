/**
 * Write a description of Part3 here.
 * 
 * @author Ines Cabrera Betancor 
 * @version #1
 */

import edu.duke.*;

public class Part3 {
  public double cgRatio(String dna){
    int counter_cg = 0;
    for (char c : dna.toCharArray()){
      if (c == 'G' || c == 'C'){
        counter_cg++;
      }
    }
    return (double) counter_cg / dna.length();
  }
  public void processGenes(StorageResource sr) {
    // point 1 & 2
    System.out.println("LARGER THAN 9 CHARACTERS");
    int counter_9 = 0;
    for (String s : sr.data()) {
      if (s.length() > 9) {
        counter_9++;
        System.out.println(s);
      }
    }
    System.out.println("There are " + counter_9 + " strings with more than 9 characters");
    // Point 3 & 4
    System.out.println("CG RATIO HIGHER THAN 0.35");
    int counter_cg = 0;
    for (String s : sr.data()) {
      if (cgRatio(s) > 0.35) {
        counter_cg++;
        System.out.println(s);
      }
    }
    System.out.println("There are " + counter_cg + " strings with cgRatio > 0.35");
    // Point 5
    System.out.println("LONGEST GENE IN STORAGE RESOURCE");
    String max = "";
    for (String s : sr.data()) {
      if (s.length() > max.length()) {
        max = s;
      }
    }
    System.out.println(max);
  }
  public void testProcessGenes() {
    StorageResource sr = new StorageResource();
    sr.add("ATGCGTACGTAAT");
    sr.add("ATGTTTTAG");
    sr.add("ATGTTTAG");
    sr.add("GCGCGCGTAA");
    sr.add("ATATATATAT");
    sr.add("ATGCCCGGGTTTAA");
    processGenes(sr);
  }
  public static void main(String[] args){
    Part3 obj = new Part3();
    obj.testProcessGenes();
  }
}
