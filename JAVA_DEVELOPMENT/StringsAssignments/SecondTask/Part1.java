/**
 * Write a description of Part1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Part1 {
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
  public void testFindStopCodon() {
    String dna1 = "AATGCTAACTAGCTGACTAAT";
    String dna2 = "ATGCCCTGACCC";
    String dna3 = "ATGCCCTAGCCC";
    String dna4 = "ATGCCCCCC";
    
    System.out.println("DNA1: " + dna1 + " -> stop TAA: " + findStopCodon(dna1, dna1.indexOf("ATG"), "TAA"));
    System.out.println("DNA2: " + dna2 + " -> stop TGA: " + findStopCodon(dna2, dna2.indexOf("ATG"), "TGA"));
    System.out.println("DNA3: " + dna3 + " -> stop TAG: " + findStopCodon(dna3, dna3.indexOf("ATG"), "TAG"));
    System.out.println("DNA4: " + dna4 + " -> stop TAA: " + findStopCodon(dna4, dna4.indexOf("ATG"), "TAA"));
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
  public void testFindGene() {
    String dna1 = "AATGCTAACTAGCTGACTAAT";
    String dna2 = "ATGCCCTGACCC";
    String dna3 = "ATGCCCTAGTAA";
    String dna4 = "CCCCCCCCCC";
    String dna5 = "ATGCCCCCCCC";
    String[] tests = {dna1, dna2, dna3, dna4, dna5};
    for (String dna : tests){
      System.out.println("DNA: " + dna);
      String gene = findGene(dna);
      System.out.println("Gene: " + gene + "\n");
    }
  }
  public void printAllGenes(String dna){
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
        System.out.println("Gene found: " + gene);
        start = atgIndex + gene.length();
      }
    }
  }
  public static void main(String[] args){
    Part1 part = new Part1();
    System.out.println("---- Testing findStopCodon ----");
    part.testFindStopCodon();
    System.out.println("\n---- Testing findGene ----");
    part.testFindGene();
    System.out.println("\n---- Testing printAllGenes ----");
    String dna = "AATGCTAACTAGCTGACTAATATGCCCTGACCCATGCCCTAGTAA";
    part.printAllGenes(dna);
  }
}
