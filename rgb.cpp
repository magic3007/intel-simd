#include "rgb.h"

RGB::RGB(size_t height, size_t width) :
  height_(height), width_(width), size_(height * width),
  r_(new uint8_t[size_]), g_(new uint8_t[size_]), b_(new uint8_t[size_]){}

void RGB::Free(){
  delete [] r_;
  delete [] g_;
  delete [] b_;
}