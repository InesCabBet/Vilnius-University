/**
 * Write a description of Part2 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import edu.duke.*;
import org.apache.commons.csv.*;
import java.io.*;

public class Part2 {
  public CSVRecord coldestHourInFile(CSVParser parser) {
    CSVRecord coldest = null;
    for (CSVRecord record : parser) {
      String tempStr = record.get("TemperatureF");
      if (tempStr.equals("-9999")) continue; // ignorar datos inválidos
      double currentTemp = Double.parseDouble(tempStr);
      if (coldest == null || currentTemp < Double.parseDouble(coldest.get("TemperatureF"))) {
        coldest = record;
      }
    }
    return coldest;
  }
  public void testColdestHourInFile() {
    FileResource fr = new FileResource();
    CSVRecord coldest = coldestHourInFile(fr.getCSVParser());
    if (coldest != null) {
      System.out.println("Coldest temperature was " + coldest.get("TemperatureF") + " at " + coldest.get("DateUTC"));
    } else {
      System.out.println("No valid temperature found in file.");
    }
  }
  public String fileWithColdestTemperature() {
    CSVRecord coldestSoFar = null;
    String coldestFileName = "";
    DirectoryResource dr = new DirectoryResource();
    for (File f : dr.selectedFiles()) {
      FileResource fr = new FileResource(f);
      CSVRecord current = coldestHourInFile(fr.getCSVParser());
      if (current == null) continue;
      if (coldestSoFar == null ||
        Double.parseDouble(current.get("TemperatureF")) < Double.parseDouble(coldestSoFar.get("TemperatureF"))) {
        coldestSoFar = current;
        coldestFileName = f.getName();
      }
    }
    return coldestFileName;
  }
  public void testFileWithColdestTemperature() {
    String fileName = fileWithColdestTemperature();
    if (fileName == null || fileName.isEmpty()) {
      System.out.println("No file selected or no valid temperatures found.");
      return;
    }
    System.out.println("Coldest day was in file " + fileName);
    try {
      FileResource fr = new FileResource("nc_weather/2014/" + fileName);
      CSVRecord coldest = coldestHourInFile(fr.getCSVParser());
      System.out.println("Coldest temperature on that day was " + coldest.get("TemperatureF"));
      System.out.println("All the Temperatures on the coldest day were:");
      for (CSVRecord record : fr.getCSVParser()) {
        System.out.println(record.get("DateUTC") + ": " + record.get("TemperatureF"));
      }
    } catch (Exception e) {
      // Si no se puede abrir por ruta, pedimos al usuario que seleccione el archivo manualmente
      System.out.println("No se pudo abrir por ruta 'nc_weather/2014/" + fileName + "'. Por favor selecciona el archivo manualmente:");
      FileResource fr = new FileResource();
      CSVRecord coldest = coldestHourInFile(fr.getCSVParser());
      System.out.println("Coldest temperature on that day was " + coldest.get("TemperatureF"));
      System.out.println("All the Temperatures on the coldest day were:");
      for (CSVRecord record : fr.getCSVParser()) {
        System.out.println(record.get("DateUTC") + ": " + record.get("TemperatureF"));
      }
    }
  }
  public CSVRecord lowestHumidityInFile(CSVParser parser) {
    CSVRecord lowest = null;
    for (CSVRecord record : parser) {
      String humStr = record.get("Humidity");
      if (humStr.equals("N/A")) continue;
      double currentHum = Double.parseDouble(humStr);
      if (lowest == null || currentHum < Double.parseDouble(lowest.get("Humidity"))) {
        lowest = record;
      }
    }
    return lowest;
  }
  public void testLowestHumidityInFile() {
    FileResource fr = new FileResource();
    CSVRecord lowest = lowestHumidityInFile(fr.getCSVParser());
    if (lowest != null) {
      System.out.println("Lowest Humidity was " + lowest.get("Humidity") + " at " + lowest.get("DateUTC"));
    } else {
      System.out.println("No valid humidity found in file.");
    }
  }
  public CSVRecord lowestHumidityInManyFiles() {
    CSVRecord lowestSoFar = null;
    DirectoryResource dr = new DirectoryResource();
    for (File f : dr.selectedFiles()) {
      FileResource fr = new FileResource(f);
      CSVRecord current = lowestHumidityInFile(fr.getCSVParser());
      if (current == null) continue;
      if (lowestSoFar == null ||
        Double.parseDouble(current.get("Humidity")) < Double.parseDouble(lowestSoFar.get("Humidity"))) {
        lowestSoFar = current;
      }
    }
    return lowestSoFar;
  }
  public void testLowestHumidityInManyFiles() {
    CSVRecord lowest = lowestHumidityInManyFiles();
    if (lowest != null) {
      System.out.println("Lowest Humidity was " + lowest.get("Humidity") + " at " + lowest.get("DateUTC"));
    } else {
      System.out.println("No valid humidity found in selected files.");
    }
  }
  public double averageTemperatureInFile(CSVParser parser) {
    double total = 0.0;
    int count = 0;
    for (CSVRecord record : parser) {
      String tempStr = record.get("TemperatureF");
      if (tempStr.equals("-9999")) continue; // ignorar lecturas inválidas
      double temp = Double.parseDouble(tempStr);
      total += temp;
      count++;
    }
    if (count == 0) return Double.NaN;
    return total / count;
  }
  public void testAverageTemperatureInFile() {
    FileResource fr = new FileResource();
    double avg = averageTemperatureInFile(fr.getCSVParser());
    if (Double.isNaN(avg)) {
      System.out.println("No valid temperature values found.");
    } else {
      System.out.println("Average temperature in file is " + avg);
    }
  }
  public double averageTemperatureWithHighHumidityInFile(CSVParser parser, int value) {
    double total = 0.0;
    int count = 0;
    for (CSVRecord record : parser) {
      String humStr = record.get("Humidity");
      if (humStr.equals("N/A")) continue;
      double hum = Double.parseDouble(humStr);
      if (hum >= value) {
        String tempStr = record.get("TemperatureF");
        if (tempStr.equals("-9999")) continue;
        total += Double.parseDouble(tempStr);
        count++;
      }
    }
    if (count == 0) return Double.NaN;
    return total / count;
  }
  public void testAverageTemperatureWithHighHumidityInFile() {
    FileResource fr = new FileResource();
    double avg = averageTemperatureWithHighHumidityInFile(fr.getCSVParser(), 80);
    if (Double.isNaN(avg)) {
      System.out.println("No temperatures with that humidity");
    } else {
      System.out.println("Average Temp when high Humidity is " + avg);
    }
  }
  public static void main(String[] args) {
    Part2 p = new Part2();
    System.out.println("=== Executing testColdestHourInFile ===");
    try { p.testColdestHourInFile(); } catch (Exception e) { System.out.println("testColdestHourInFile terminó con error: " + e.getMessage()); }

    System.out.println("\n=== Executing testFileWithColdestTemperature ===");
    try { p.testFileWithColdestTemperature(); } catch (Exception e) { System.out.println("testFileWithColdestTemperature terminó con error: " + e.getMessage()); }

    System.out.println("\n=== Executing testLowestHumidityInFile ===");
    try { p.testLowestHumidityInFile(); } catch (Exception e) { System.out.println("testLowestHumidityInFile terminó con error: " + e.getMessage()); }

    System.out.println("\n=== Executing testLowestHumidityInManyFiles ===");
    try { p.testLowestHumidityInManyFiles(); } catch (Exception e) { System.out.println("testLowestHumidityInManyFiles terminó con error: " + e.getMessage()); }

    System.out.println("\n=== Executing testAverageTemperatureInFile ===");
    try { p.testAverageTemperatureInFile(); } catch (Exception e) { System.out.println("testAverageTemperatureInFile terminó con error: " + e.getMessage()); }

    System.out.println("\n=== Executing testAverageTemperatureWithHighHumidityInFile ===");
    try { p.testAverageTemperatureWithHighHumidityInFile(); } catch (Exception e) { System.out.println("testAverageTemperatureWithHighHumidityInFile terminó con error: " + e.getMessage()); }
  }
}

