#include "elevation_dataset.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>


ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height){

    
    width_ = width;
    height_ = height;
    data_ = std::vector<std::vector<int>>(height, std::vector<int>(width));
    std::ifstream ifs(filename);
    unsigned long int counter = 0;
    if (!ifs.is_open())
    {
        throw std::invalid_argument("Cannot Open - ElevationDataset");
    }
    int data = 0;
   for (unsigned int row = 0; row < height; row++)
    {   
        
        for (unsigned int col = 0; col < width; col++)
        {
            ifs >> data;
            if (ifs.fail())
            {
                throw std::invalid_argument("WRONG");
            }else{
                data_.at(row).at(col) = data;
                counter++;
            }

        }
    }
    min_ele_ = data_.at(0).at(0);
    max_ele_ = data_.at(0).at(0);
    for (unsigned int row = 0; row < height; row++)
    {   
        
        for (unsigned int col = 0; col < width; col++)
        {

            if (data_.at(row).at(col) > max_ele_)
            {
                max_ele_ = data_.at(row).at(col);
            }
            if (data_.at(row).at(col) < min_ele_)
            {
                min_ele_ = data_.at(row).at(col);
            }

        }
    }
    ifs >> data;
    if (!ifs.fail())
    {
        throw std::runtime_error("Too much data");
    }

    if (counter < height * width)
    {
        throw std::runtime_error("Too little data");
    }


}
size_t ElevationDataset::Width() const{
    return width_;
}
size_t ElevationDataset::Height() const{
    return height_;
}

int ElevationDataset::MaxEle() const{
 return max_ele_;
}

int ElevationDataset::MinEle() const{
 return min_ele_;
}

int ElevationDataset::DatumAt(size_t row, size_t col) const{
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>> & ElevationDataset::GetData() const{
    return data_;
}



