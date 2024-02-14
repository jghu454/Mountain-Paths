#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  const std::string kStudentOutput =
      "./student_out/ex_path_image_prompt_51w_55h.ppm";
  const std::string kTestFile = "./example-data/ex_input_data/map-input-w51-h55.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_paths/prompt_5w_2h.ppm";
  constexpr size_t kTestFileWidth = 51;
  constexpr size_t kTestFileHeight = 55;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);

  
}