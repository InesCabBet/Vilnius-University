/**
 * Write a description of ImageInversion here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

import edu.duke.*;
import java.io.*;

public class ImageInversion {
  public ImageResource invert(ImageResource inImage){
    ImageResource outImage = new ImageResource(inImage.getWidth(), inImage.getHeight());
    for (Pixel pixel : outImage.pixels()){
      Pixel work = inImage.getPixel(pixel.getX(), pixel.getY());
      int newRed = 255 - work.getRed();
      pixel.setRed(newRed);
      int newBlue = 255 - work.getBlue();
      pixel.setBlue(newBlue);
      int newGreen = 255 - work.getGreen();
      pixel.setGreen(newGreen);
    }
    return outImage;
  }
  public void negativeAndSave() {
    DirectoryResource dr = new DirectoryResource();
    for (File f : dr.selectedFiles()) {
      ImageResource image = new ImageResource(f);
      ImageResource inverted = invert(image);
      String fileName = image.getFileName();
      String newName = "inverted-" + fileName;
      inverted.setFileName(newName);
      inverted.save();
      inverted.draw();
    }
  }
  public static void main(String args[]) {
    ImageInversion img = new ImageInversion();
    img.negativeAndSave();
  }
}
