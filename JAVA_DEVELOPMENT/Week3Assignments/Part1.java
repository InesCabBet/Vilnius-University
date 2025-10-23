/**
 * Write a description of Part1 here.
 * 
 * @author Inés Cabrera Betancor
 * @version 01 OCT 2025
 */

import edu.duke.*;
import org.apache.commons.csv.*;

public class Part1 {
  public String countryInfo(CSVParser parser, String country) {
    for (CSVRecord record : parser) {
      String countryName = record.get("Country");
      if (countryName.equalsIgnoreCase(country)) {
        String exports = record.get("Exports");
        String value = record.get("Value (dollars)");
        return countryName + ":" + exports + ":" + value;
      }
    }
    return "NOT FOUND";
  }
  public void listExporterTwoProducts(CSVParser parser, String exportItem1, String exportItem2) {
    for (CSVRecord record : parser) {
      String exports = record.get("Exports");
      if (exports.contains(exportItem1) && exports.contains(exportItem2)) {
        System.out.println(record.get("Country"));
      }
    }
  }
  public int numberOfExporters(CSVParser parser, String exportItem) {
    int count = 0;
    for (CSVRecord record : parser) {
      String exports = record.get("Exports");
      if (exports.contains(exportItem)) {
        count++;
      }
    }
    return count;
  }
  public void bigExporters(CSVParser parser, String amount){
    for (CSVRecord record : parser) {
      String value = record.get("Value (dollars)");
      if (value.length() > amount.length()) {
        System.out.println(record.get("Country") + " " + value);
      }
    }
  }
  public void tester() {
    FileResource fr = new FileResource("exportdata.csv");
    CSVParser parser = fr.getCSVParser();
    System.out.println(countryInfo(parser, "Germany"));
    parser = fr.getCSVParser();
    listExporterTwoProducts(parser, "gold", "diamonds");
    parser = fr.getCSVParser();
    System.out.println("Number of exporters of gold: " + numberOfExporters(parser, "gold"));
    parser = fr.getCSVParser();
    bigExporters(parser, "$999,999,999");
  }
  public static void main(String[] args){
    Part1 obj = new Part1();
    obj.tester();
  }
}
