/**
 * Write a description of Part1 here.
 * 
 * @author Ines Cabrera Betancor 
 * @version #1
 */

import edu.duke.*;

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
  public String findGene(String dna, int where) {
    int index = dna.indexOf("ATG", where);
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
  public StorageResource getAllGenes(String dna){
    int start = 0;
    StorageResource sr = new StorageResource();
    while(true){
      String gene = findGene(dna, start);
      if(gene.isEmpty()){
        break;
      }
      sr.add(gene);
      start = dna.indexOf(gene, start) + gene.length();
    }
    return sr;
  }
  public void testGetAllGenes(){
    String dna = "ATGAAATAAATGCCCCCCCTAGATGTAA";
    StorageResource genes = getAllGenes(dna);
    System.out.println("Genes found: ");
    for (String s : genes.data()){
      System.out.println(s);
    }
  }
  public static void main(String[] args){
    Part1 obj = new Part1();
    obj.testGetAllGenes();
  }
}
