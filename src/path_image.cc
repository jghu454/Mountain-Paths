#include "path_image.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

std::pair<unsigned int, unsigned int> findBestPath(unsigned int row, const ElevationDataset &dataset, int col, size_t height)
{
    //Checking which path to take
    bool possible_path[3];// index 0 = straight forward, index 1 = north east, index 2 = south east


    possible_path[0] = true;
    possible_path[1] = (row == 0)? false : true;
    possible_path[2] = (row + 1 < height)? true: false; 

    //determine amount of variables that are needed to compare;
    int best_path_row = row; //Currently the forward direction is best
    int lowest_resistance = std::abs(dataset.DatumAt(row,col + 1) - dataset.DatumAt(row,col)); // lowest resistance is by default the forward
    

    if (possible_path[2])// we look at southeast first because if southeast and northeast are tie, values would not change 
    {
          
        int south_east_dif = std::abs(dataset.DatumAt(row,col) - dataset.DatumAt(row + 1,col + 1)); //Getting southeast diff

        best_path_row = (lowest_resistance > south_east_dif)? row + 1 : best_path_row;
        lowest_resistance = (lowest_resistance > south_east_dif)? south_east_dif : lowest_resistance; 
    }

    if(possible_path[1])
    {
        
        int north_east_dif = std::abs(dataset.DatumAt(row -1, col + 1) - dataset.DatumAt(row,col));
        
        best_path_row = (lowest_resistance > north_east_dif)? row - 1 : best_path_row;
        lowest_resistance = (lowest_resistance > north_east_dif)? north_east_dif : lowest_resistance; 

        

    }

    return std::make_pair(best_path_row,lowest_resistance);

    
}


PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset)
{
    height_ = image.Height();
    width_ = image.Width();
    path_image_ = std::vector<std::vector<Color>>(height_,std::vector<Color>(width_));
    paths_ = std::vector<Path>(height_,Path(0,0));

    //Creating paths
    unsigned int best_path = 0;

    for (unsigned int r = 0; r < height_; r ++){
        unsigned int col = 0;
        unsigned int curr_row = r;
        paths_.at(r) = Path(width_,r); // Create new path of "width_" length starting at "r" start_row_
        paths_.at(r).SetLoc(0, r);
        while (col < width_ - 1)
        {
            //first value of the pair is the row
            //second value is the change in elevation
            std::pair<int,int> val = findBestPath(curr_row,dataset,col, height_);
            

            std::cout << "ROW: " << val.first << "| Diff: " << val.second;
            paths_.at(r).SetLoc(col + 1 ,val.first);
        
            paths_.at(r).IncEleChange(val.second);
            curr_row = val.first;
            col++;

        }
        std::cout << "\n ";
        if (paths_.at(r).EleChange() < paths_.at(best_path).EleChange())
        {
            best_path = r;
        }
    }


    for (unsigned int r = 0; r < height_; r++)
    {
        for (unsigned int c = 0; c < width_; c++)
        {
            std::cout << paths_.at(r).GetPath().at(c);
        }
        std::cout << "\n";
    }


    //Coloring in gray
    for (unsigned int r = 0; r < height_; r++)
    {
         for (unsigned int c = 0; c < width_; c++)
        {
            path_image_.at(r).at(c) = image.ColorAt(r,c);
        }
    }

    //Copying over image
    for (unsigned int r = 0; r < height_; r++)
    {   
        
        for (unsigned int c = 0; c < width_; c++)
        {
            if (r != best_path)
            {
                std::vector<size_t> x = paths_.at(r).GetPath();
                path_image_.at(x.at(c)).at(c) = Color(252,25,63);
            }
        }
    }

    //getting best path
    std::vector<size_t> x = paths_.at(best_path).GetPath();

    for (unsigned int c = 0; c < width_; c++)
    {
        path_image_.at(x.at(c)).at(c) = Color(31,253,13);
    }
    

}

size_t PathImage::Width() const
{
    return width_;
}
size_t PathImage::Height() const{ return height_;}
unsigned int PathImage::MaxColorValue() const{ return kMaxColorValue;}
const std::vector<Path>& PathImage::Paths() const{ return paths_;}
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const{ return path_image_;}
void PathImage::ToPpm(const std::string& name) const
{
     std::ofstream ofs;
  ofs.open(name);

  if (!ofs.is_open())
  {
    throw std::invalid_argument("NOT WORKING");
  }

  ofs << "P3" << "\n";
  ofs << width_ << " " << height_ << "\n";
  ofs << kMaxColorValue <<"\n";



  for (unsigned int r = 0; r < height_; r++)
  {
    for (unsigned int c = 0; c < width_; c++)
    {
      if (c < width_ - 1){
        ofs << path_image_.at(r).at(c).Red() << " " << path_image_.at(r).at(c).Green() << " " << path_image_.at(r).at(c).Blue() << " ";
      }else{
        ofs << path_image_.at(r).at(c).Red() << " " << path_image_.at(r).at(c).Green() << " " << path_image_.at(r).at(c).Blue() << "\n";
      }
      
    }
  }
    ofs.close();
}
     
     
     
     
     
     