/**
 * Write a description of Part4 here.
 * 
 * @author Ines Cabrera Betancor 
 * @version 25 SEP 2025
 */

import edu.duke.*;

public class Part4 {
  public void findLinks() {
    URLResource url = new URLResource("https://www.dukelearntoprogram.com/course2/data/manylinks.html");
    for (String line : url.lines()) {
      String lower = line.toLowerCase();
      int index = lower.indexOf("youtube.com");
      while (index != -1) {
        int start = lower.lastIndexOf("\"", index);
        int end = lower.indexOf("\"", index + 1);
        if (start != -1 && end != -1 && end > start) {
          String link = line.substring(start + 1, end);
          System.out.println(link);
        }
      index = lower.indexOf("youtube.com", index + 1);
      }
    }
  }
  public static void main(String[] args) {
    Part4 obj = new Part4();
    obj.findLinks();
  }
}