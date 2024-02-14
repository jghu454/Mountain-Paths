#include "color.hpp"
#include <iostream>


Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...

  if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
  {
    std::cout << r << ":" << g << ":" << b << std::endl;
    throw std::invalid_argument("invalid arguments - Color" );
  }

  
}


// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}