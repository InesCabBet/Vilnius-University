/**
 * Write a description of Part1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import edu.duke.*;
import org.apache.commons.csv.*;
import java.io.*;
import java.util.*;

public class BabyNames {
  public void totalBirths(FileResource fr) {
    int totalBirths = 0;
    int totalBoys = 0;
    int totalGirls = 0;
    int uniqueBoys = 0;
    int uniqueGirls = 0;
    for (CSVRecord rec : fr.getCSVParser(false)) {
      int births = Integer.parseInt(rec.get(2));
      totalBirths += births;
      if (rec.get(1).equals("M")) {
        totalBoys += births;
        uniqueBoys++;
      } else {
        totalGirls += births;
        uniqueGirls++;
      }
    }
    System.out.println("Total births = " + totalBirths);
    System.out.println("Total boys births = " + totalBoys);
    System.out.println("Total girls births = " + totalGirls);
    System.out.println("Unique boys names = " + uniqueBoys);
    System.out.println("Unique girls names = " + uniqueGirls);
    System.out.println("Total unique names = " + (uniqueBoys + uniqueGirls));
  }

  public int getRank(int year, String name, String gender) {
    String fileName = "us_babynames/yob" + year + "short.csv";
    System.out.println(fileName);
    FileResource fr = new FileResource(fileName);
    int rank = 0;
    for (CSVRecord rec : fr.getCSVParser(false)) {
      if (rec.get(1).equals(gender)) {
          rank++;
          if (rec.get(0).equals(name)) {
            return rank;
          }
      }
    }
    return -1;
  }

  public String getName(int year, int rank, String gender) {
    String fileName = "us_babynames/yob" + year + "short.csv";
    FileResource fr = new FileResource(fileName);
    int currentRank = 0;
    for (CSVRecord rec : fr.getCSVParser(false)) {
      if (rec.get(1).equals(gender)) {
        currentRank++;
        if (currentRank == rank) {
          return rec.get(0);
        }
      }
    }
    return "NO NAME";
  }

  public void whatIsNameInYear(String name, int year, int newYear, String gender) {
    int rank = getRank(year, name, gender);
    if (rank == -1) {
      System.out.println("Name not found in year " + year);
      return;
    }
    String newName = getName(newYear, rank, gender);
    String pronoun = (gender.equals("F")) ? "she" : "he";
    System.out.println(name + " born in " + year + " would be " + newName + " if " + pronoun + " was born in " + newYear + ".");
  }

  public int yearOfHighestRank(String name, String gender) {
    DirectoryResource dr = new DirectoryResource();
    int bestYear = -1;
    int bestRank = Integer.MAX_VALUE;
    for (File f : dr.selectedFiles()) {
      String fileName = f.getName(); // e.g. yob2012short.csv
      int year = Integer.parseInt(fileName.replaceAll("\\D", ""));
      FileResource fr = new FileResource(f);
      int rank = 0;
      for (CSVRecord rec : fr.getCSVParser(false)) {
        if (rec.get(1).equals(gender)) {
          rank++;
          if (rec.get(0).equals(name)) {
            if (rank < bestRank) {
              bestRank = rank;
              bestYear = year;
            }
            break;
          }
        }
      }
    }
    if (bestYear == -1) return -1;
    return bestYear;
  }

  public double getAverageRank(String name, String gender) {
    DirectoryResource dr = new DirectoryResource();
    double totalRank = 0;
    int foundCount = 0;
    for (File f : dr.selectedFiles()) {
      FileResource fr = new FileResource(f);
      int rank = 0;
      boolean found = false;
      for (CSVRecord rec : fr.getCSVParser(false)) {
        if (rec.get(1).equals(gender)) {
          rank++;
          if (rec.get(0).equals(name)) {
            totalRank += rank;
            found = true;
            break;
          }
        }
      }
      if (found) foundCount++;
    }
    if (foundCount == 0) return -1.0;
    return totalRank / foundCount;
  }

  public int getTotalBirthsRankedHigher(int year, String name, String gender) {
    String fileName = "us_babynames/yob" + year + "short.csv";
    FileResource fr = new FileResource(fileName);
    int total = 0;
    for (CSVRecord rec : fr.getCSVParser(false)) {
      if (rec.get(1).equals(gender)) {
        if (rec.get(0).equals(name)) {
          break;
        }
        total += Integer.parseInt(rec.get(2));
      }
    }
    return total;
  }

  // ---------------- MAIN ----------------
  public static void main(String[] args) {
    BabyNames bn = new BabyNames();
    Scanner sc = new Scanner(System.in);
    boolean running = true;
    while (running) {
      System.out.println("\n=== MENU ===");
      System.out.println("1. Total births (choose file)");
      System.out.println("2. Get rank");
      System.out.println("3. Get name by rank");
      System.out.println("4. What is name in another year?");
      System.out.println("5. Year of highest rank (choose files)");
      System.out.println("6. Average rank (choose files)");
      System.out.println("7. Total births ranked higher");
      System.out.println("8. Exit");
      System.out.print("Choose option: ");
      int option = sc.nextInt();
      sc.nextLine();
      switch (option) {
        case 1:
          bn.totalBirths(new FileResource());
        break;
        case 2:
          System.out.print("Enter year: ");
          int year = sc.nextInt(); sc.nextLine();
          System.out.print("Enter name: ");
          String name = sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String gender = sc.nextLine().toUpperCase();
          int rank = bn.getRank(year, name, gender);
          System.out.println("Rank of " + name + " in " + year + " (" + gender + ") is: " + rank);
        break;
        case 3:
          System.out.print("Enter year: ");
          int year2 = sc.nextInt(); sc.nextLine();
          System.out.print("Enter rank: ");
          int r = sc.nextInt(); sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String g2 = sc.nextLine().toUpperCase();
          System.out.println("Name at rank " + r + " in " + year2 + " (" + g2 + ") is: " + bn.getName(year2, r, g2));
        break;
        case 4:
          System.out.print("Enter name: ");
          String n = sc.nextLine();
          System.out.print("Enter birth year: ");
          int y = sc.nextInt(); sc.nextLine();
          System.out.print("Enter new year: ");
          int ny = sc.nextInt(); sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String g3 = sc.nextLine().toUpperCase();
          bn.whatIsNameInYear(n, y, ny, g3);
        break;
        case 5:
          System.out.print("Enter name: ");
          String hn = sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String hg = sc.nextLine().toUpperCase();
          System.out.println("Select multiple files...");
          int bestYear = bn.yearOfHighestRank(hn, hg);
          System.out.println("Year of highest rank: " + bestYear);
        break;
        case 6:
          System.out.print("Enter name: ");
          String an = sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String ag = sc.nextLine().toUpperCase();
          System.out.println("Select multiple files...");
          double avg = bn.getAverageRank(an, ag);
          System.out.println("Average rank: " + avg);
        break;
        case 7:
          System.out.print("Enter year: ");
          int ty = sc.nextInt(); sc.nextLine();
          System.out.print("Enter name: ");
          String tn = sc.nextLine();
          System.out.print("Enter gender (M/F): ");
          String tg = sc.nextLine().toUpperCase();
          System.out.println("Total births ranked higher: " + bn.getTotalBirthsRankedHigher(ty, tn, tg));
        break;
        case 8:
          running = false;
        break;
        default:
          System.out.println("Invalid option!");
      }
    }
    sc.close();
    System.out.println("Program ended.");
  }
}

