#ifndef INTEL_SIMD_RGB_H
#define INTEL_SIMD_RGB_H

#include <cstddef>
#include <cstdint>

class RGB {
public:
  RGB(size_t height, size_t width);
  void Free();

  size_t height_, width_, size_;
  uint8_t *r_, *g_, *b_;
};

#endif // INTEL_SIMD_RGB_H
