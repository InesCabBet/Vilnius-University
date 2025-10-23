/**
 * Write a description of Part3 here.
 * 
 * @author Inés Cabrera Betancor 
 * @version #1 
*/
public class Part3 {
  public int findStopCodon(String dna, int startIndex, String stopCodon){
    int index = dna.indexOf(stopCodon, startIndex + 3);
    while (index != -1){
      if ((index - startIndex) % 3 == 0){
        return index;
      } else {
        index = dna.indexOf(stopCodon, index + 1);
      }
    }
    return dna.length();
  }
  public String findGene(String dna) {
    int index = dna.indexOf("ATG");
    if (index == -1){
      return "";
    }
    int taaIndex = findStopCodon(dna, index, "TAA");
    int tagIndex = findStopCodon(dna, index, "TAG");
    int tgaIndex = findStopCodon(dna, index, "TGA");
    int minIndex = Math.min(taaIndex, Math.min(tagIndex, tgaIndex));
    if (minIndex == dna.length()){
      return "";
    }
    return dna.substring(index, minIndex + 3);
  }
  public int countGenes(String dna){
    int counter = 0;
    int start = 0;
    while(true){
      int atgIndex = dna.indexOf("ATG", start);
      if(atgIndex == -1){
        break;
      }
      String gene = findGene(dna.substring(atgIndex));
      if(gene.isEmpty()){
        start = atgIndex + 3;
      } else {
        counter++;
        start = atgIndex + gene.length();
      }
    }
    return counter;
  }
  public void testCountGenes() {
    String dna1 = "ATGTAAGATGCCCTAGT";
    String dna2 = "ATGAAATGAAAA";
    String dna3 = "CCCATGGGGTTTCCC";
    String dna4 = "ATGTAAATGTGAATGTAG";
    String dna5 = "ATGCCCTAAATGCCCTGA";
    String[] tests = {dna1, dna2, dna3, dna4, dna5};
    for (String dna : tests){
      System.out.println("DNA: " + dna);
      int genes = countGenes(dna);
      System.out.println("number of genes: " + genes + "\n");
    }
  }
  public static void main(String[] args){
    Part3 obj = new Part3();
    obj.testCountGenes();
  }
}
