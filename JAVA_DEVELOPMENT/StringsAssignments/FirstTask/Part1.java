
/**
 * Write a description of Part1 here.
 * 
 * @author Ines Cabrera Betancor 
 * @version (a version number or a date)
 */
public class Part1 {
  public String findSimpleGene(String dna){
    int start = dna.indexOf("ATG");
    if (start == -1){
      return "";
    }
    int stop = dna.indexOf("TAA", start + 3);
    if (stop == -1){
      return "";
    }
    if ((stop - start) % 3 == 0){
      return dna.substring(start, stop + 3);
    }
    return "";
  }
  public void testSimpleGene() {
    String test1 = "GTAAAT";
    String test2 = "AGTTAG";
    String test3 = "TGATAG";
    String test4 = "ATGATGAAT";
    String test5 = "ATGTAAAT";
    System.out.println("Test 1: " + test1 + " -> " + findSimpleGene(test1));
    System.out.println("Test 2: " + test2 + " -> " + findSimpleGene(test2));
    System.out.println("Test 3: " + test3 + " -> " + findSimpleGene(test3));
    System.out.println("Test 4: " + test4 + " -> " + findSimpleGene(test4));
    System.out.println("Test 5: " + test5 + " -> " + findSimpleGene(test5));
  }
  public static void main(String[] args){
    Part1 obj = new Part1();
    obj.testSimpleGene();
  }
}