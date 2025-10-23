/**
 * Write a description of GrayScale1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import edu.duke.*;
import java.io.*;

public class GrayScale1 {
  public ImageResource makeGray(ImageResource inImage){
    ImageResource outImage = new ImageResource(inImage.getWidth(), inImage.getHeight());
    for (Pixel pixel : outImage.pixels()) {
      Pixel work = inImage.getPixel(pixel.getX(), pixel.getY());
      int average = (work.getRed() + work.getBlue() + work.getGreen())/3;
      pixel.setRed(average);
      pixel.setBlue(average);
      pixel.setGreen(average);
    }
    return outImage;
  }
  public void batchGrayAndSave() {
    DirectoryResource dr = new DirectoryResource();
    for (File fr : dr.selectedFiles()){
      ImageResource inImage = new ImageResource(fr);
      ImageResource gray = makeGray(inImage);
      String filename = inImage.getFileName();
      String newName = "gray-" + filename;
      gray.setFileName(newName);
      gray.save();
      gray.draw();
    }
  }
  public static void main(String args[]){
    GrayScale1 gs = new GrayScale1();
    gs.batchGrayAndSave();
  }
}
