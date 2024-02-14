#include "grayscale_image.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

#include "elevation_dataset.hpp"


GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {

  
  width_ = dataset.Width();
  height_ = dataset.Height();
  
  image_ = std::vector<std::vector<Color>>(dataset.Height(),
                                           std::vector<Color>(dataset.Width()));
  for (unsigned int r = 0; r < height_; r++) {
    for (unsigned int c = 0; c < width_; c++) {
      
      double shade_of_gray =
          std::round((double)(dataset.GetData().at(r).at(c) - dataset.MinEle()) /(dataset.MaxEle() - dataset.MinEle()) * 255);
      if (dataset.MaxEle() - dataset.MinEle() == 0)
      {
        shade_of_gray = 0;
      }
      image_.at(r).at(c) = Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }
  
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    GrayscaleImage(ElevationDataset(filename, width, height)) {}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm( const std::string& name ) const
{
  std::ofstream ofs;
  ofs.open(name);

  if (!ofs.is_open())
  {
    //throw exception
  }

  ofs << "P3" << "\n";
  ofs << width_ << " " << height_ << "\n";
  ofs << kMaxColorValue <<"\n";



  for (unsigned int r = 0; r < height_; r++)
  {
    for (unsigned int c = 0; c < width_; c++)
    {
      if (c < width_ - 1){
        ofs << image_.at(r).at(c).Red() << " " << image_.at(r).at(c).Green() << " " << image_.at(r).at(c).Blue() << " ";
      }else{
        ofs << image_.at(r).at(c).Red() << " " << image_.at(r).at(c).Green() << " " << image_.at(r).at(c).Blue() << "\n";
      }

    }
    
  }

}
