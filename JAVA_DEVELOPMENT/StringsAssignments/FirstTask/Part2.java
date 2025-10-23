
/**
 * Write a description of Part2 here.
 * 
 * @author Inés Cabrera Betancor 
 * @version #1
 */
public class Part2 {
  public String findSimpleGene(String dna, String startCodon, String stopCodon){
    boolean isUpper = Character.isUpperCase(dna.charAt(0));
    String dnaLower = dna.toLowerCase();
    String startLower = startCodon.toLowerCase();
    String stopLower = stopCodon.toLowerCase();
    int start = dna.indexOf(startLower);
    if (start == -1){
        return "";
    }
    int stop = dna.indexOf(stopLower, start + 3);
    if (stop == -1){
        return "";
    }
    if ((stop - start) % 3 == 0){
        String gene = dna.substring(start, stop + 3);
        return isUpper ? gene.toUpperCase() : gene.toLowerCase();
    }
    return "";
  }
  public void testSimpleGene() {
    String startCodon = "ATG";
    String stopCodon = "TAA";
    // tests
    String test1 = "GTAAAT";
    String test2 = "AGTTAG";
    String test3 = "tagtag";
    String test4 = "ATGATGAAT";
    String test5 = "ATGTAAAT";
    System.out.println("Test 1: " + test1 + " -> " + findSimpleGene(test1, startCodon, stopCodon));
    System.out.println("Test 2: " + test2 + " -> " + findSimpleGene(test2, startCodon, stopCodon));
    System.out.println("Test 3: " + test3 + " -> " + findSimpleGene(test3, startCodon, stopCodon));
    System.out.println("Test 4: " + test4 + " -> " + findSimpleGene(test4, startCodon, stopCodon));
    System.out.println("Test 5: " + test5 + " -> " + findSimpleGene(test5, startCodon, stopCodon));
  }
  public static void main(String[] args){
    Part2 obj = new Part2();
    obj.testSimpleGene();
  }
}