/**
 * Write a description of Part2 here.
 * 
 * @author Ines Cabrera Betancor 
 * @version #1
 */

import edu.duke.*;

public class Part2 {
  public String cgRatio(String dna){
    int counter_cg = 0;
    for (char c : dna.toCharArray()){
      if (c == 'G' || c == 'C'){
        counter_cg++;
      }
    }
    String result = counter_cg + "/" + dna.length();
    return result;
  }
  public int countCTG(String dna){
    int counter = 0;
    int index = 0;
    String sub = "CTG";
    while((index = dna.indexOf(sub, index)) != - 1) {
      counter++;
      index += sub.length();
    }
    return counter;
  }
  public void testCGRatio(){
    String dna = "ATGCCATAG";
    System.out.println("Ratio of CG in " + dna + " is " + cgRatio(dna));
    String dna1 = "AGCTAAAATGCATG";
    System.out.println("Ratio of CG in " + dna1 + " is " + cgRatio(dna1));
  }
  public void testCTG(){
    String dna = "ACTGGTAGTCACTGAA";
    System.out.println("The substring CTG in " + dna + " appears: " + countCTG(dna) + " times");
  }
  public static void main(String[] args){
    Part2 obj = new Part2();
    obj.testCGRatio();
    obj.testCTG();
  }
}
