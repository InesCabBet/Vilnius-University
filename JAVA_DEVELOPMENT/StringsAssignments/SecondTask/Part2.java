/**
 * Write a description of Part2 here.
 * 
 * @author Inés Cabrera Betancor
 * @version #1
 */
public class Part2 {
  public int howMany(String stringa, String stringb){
    int counter = 0;
    int index = stringb.indexOf(stringa);
    while (index != -1){
      counter++;
      index = stringb.indexOf(stringa, index + stringa.length());
    }
    return counter;
  }
  public void testHowMany(){
    String s1 = "GAA";
    String s2 = "ATGAACGAATTGAATC";
    System.out.println("howMany(\"" + s1 + "\", \"" + s2 + "\") = " + howMany(s1, s2));
    
    String s3 = "AA";
    String s4 = "ATAAAA";
    System.out.println("howMany(\"" + s3 + "\", \"" + s4 + "\") = " + howMany(s3, s4));
    System.out.println("howMany(\"A\", \"AAAA\") = " + howMany("A", "AAAA")); 
    System.out.println("howMany(\"AT\", \"ATATAT\") = " + howMany("AT", "ATATAT"));
    System.out.println("howMany(\"G\", \"CCCCCC\") = " + howMany("G", "CCCCCC"));  
    System.out.println("howMany(\"CAT\", \"CATCATCAT\") = " + howMany("CAT", "CATCATCAT"));
  }
  public static void main(String[] args){
    Part2 obj = new Part2();
    obj.testHowMany();
  }
}