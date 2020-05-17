//
// Created by maiji on 05/17/2020.
//

#include "yuv_420.h"
#include "utils/base.h"
#include <cassert>
#include <fstream>

YUV420::YUV420(size_t width, size_t height)
    : width_(width), height_(height), size_(width * height),
      y_(new uint8_t[size_]), u_(new uint8_t[size_]), v_(new uint8_t[size_]){}

void YUV420::Free(){
  delete [] y_;
  delete [] u_;
  delete [] v_;
}

int YUV420::ReadFromYUVFile(const string &filename) {
  auto y = reinterpret_cast<uint8_t (*)[width_]>(y_);
  auto u = reinterpret_cast<uint8_t (*)[width_]>(u_);
  auto v = reinterpret_cast<uint8_t (*)[width_]>(v_);

  std::ifstream infile(filename, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
  if (!infile.is_open()){ return -1;}
  DEFER({infile.close();});

  std::streampos fsize = infile.tellg();
  infile.seekg(0, std::ifstream::beg);
  fsize = fsize - infile.tellg();
  assert(fsize == static_cast<size_t>(1.5 * size_));

  infile.read(reinterpret_cast<char *>(y), size_);
  for(size_t i = 0; i < height_; i+=2){
    for(size_t j = 0; j < width_; j+=2){
      uint8_t temp;
      infile.read(reinterpret_cast<char *>(&temp), 1);
      u[i][j] = u[i + 1][j] = u[i][j + 1] = u[i + 1][j + 1] = temp;
    }
  }

  for(size_t i = 0; i < height_; i += 2){
    for(size_t j = 0; j < width_; j += 2){
      uint8_t temp;
      infile.read(reinterpret_cast<char *>(&temp), 1);
      v[i][j] = v[i + 1][j] = v[i][j + 1] = v[i + 1][j + 1] = temp;
    }
  }
  return 0;
}

int YUV420::WriteToYUVFile(const string &filename) {
  auto y = reinterpret_cast<uint8_t (*)[width_]>(y_);
  auto u = reinterpret_cast<uint8_t (*)[width_]>(u_);
  auto v = reinterpret_cast<uint8_t (*)[width_]>(v_);

  std::ofstream outFile(filename, std::ofstream::out | std::ofstream::binary);
  if (!outFile.is_open()){return -1;}
  DEFER({outFile.close();});

  outFile.write(reinterpret_cast<const char *>(y), size_);

  for(size_t i = 0; i < height_; i += 2){
    for(size_t j = 0; j < width_; j += 2){
      outFile.write(reinterpret_cast<const char *>(&(u[i][j])), 1);
    }
  }

  for(size_t i = 0; i < height_; i += 2){
    for(size_t j = 0; j < width_; j += 2){
      outFile.write(reinterpret_cast<const char *>(&(v[i][j])), 1);
    }
  }
  return 0;
}
