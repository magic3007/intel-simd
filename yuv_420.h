#ifndef INTEL_SIMD_YUV420_H
#define INTEL_SIMD_YUV420_H

#include <cstddef>
#include <cstdint>
#include <string>

using std::string;

class YUV420 {
  public:
    YUV420(size_t width, size_t height);
    void Free();
    int ReadFromYUVFile(const string &filename);
    int WriteToYUVFile(const string &filename);

    size_t width_;
    size_t height_;
    size_t size_;
    uint8_t *y_, *u_, *v_;

};

#endif // INTEL_SIMD_YUV420_H
