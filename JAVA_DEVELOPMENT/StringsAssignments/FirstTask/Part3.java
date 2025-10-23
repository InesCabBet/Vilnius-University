
/**
 * Write a description of Part3 here.
 * 
 * @author Inés Cabrera Betancor
 * @version #1
 */
public class Part3 {
  public boolean twoOccurrences(String stringa, String stringb) {
    int firstIndex = stringb.indexOf(stringa);
    if (firstIndex == -1) {
      return false;
    }
    int secondIndex = stringb.indexOf(stringa, firstIndex + stringa.length());
    return secondIndex != -1;
  }
  public void testing(){
    // TwoOccurrences
    String test1 = "banana";
    System.out.println("Test 1 " + test1 + " -> a: " + twoOccurrences("a", test1));
    String test2 = "i love spaguetti";
    System.out.println("Test 2 " + test2 + " -> ove: " + twoOccurrences("ove", test2));
    String test3 = "ctgatgta";
    System.out.println("Test 3 " + test3 + " -> atg: " + twoOccurrences("atg", test3));
    // LastPart
    String p1 = "banana";
    String p2 = "forest";
    System.out.println("The part of the string after an in " + p1 + " is " + lastPart("an", p1));
    System.out.println("The part of the sting after zoo in " + p2 + " is " + lastPart("zoo", p2));
  }
  public String lastPart(String stringa, String stringb) {
    int index = stringb.indexOf(stringa);
    if (index == -1){
      return stringb;
    } 
    return stringb.substring(index + stringa.length());
  }
  public static void main(String[] args){
    Part3 obj = new Part3();
    obj.testing();
  }
}
