#ifndef INTEL_SIMD_IMPL_SIMPLE_H
#define INTEL_SIMD_IMPL_SIMPLE_H

#include <cassert>
#include "yuv_420.h"
#include "rgb.h"
#include "impl.h"

class ImplSimple : public Impl{
  void YUV2RGB(YUV420 *yuv, RGB *rgb) override;
  void AlphaBlend(RGB *rgb, uint8_t alpha) override;
  void RGB2YUV(RGB *rgb, YUV420 *yuv) override;
};

static inline uint8_t clamp(int x) {
  if (x < 0){
    return 0;
  }else if (x > 255){
    return 255;
  }else{
    return x;
  }
}

void ImplSimple::YUV2RGB(YUV420 *yuv, RGB *rgb) {
  assert(yuv->height_ == rgb->height_);
  assert(yuv->width_ == rgb->width_);

  auto y = yuv->y_;
  auto u = yuv->u_;
  auto v = yuv->v_;
  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;

  for(size_t i = 0; i < yuv->size_; ++i){
    int c = y[i] - 16;
    int d = u[i] - 128;
    int e = v[i] - 128;
    r[i] = clamp((298 * c + 409 * e + 128) >> 8);
    g[i] = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
    b[i] = clamp((298 * c + 516 * d + 128) >> 8);
  }

}

void ImplSimple::RGB2YUV(RGB *rgb, YUV420 *yuv) {
  assert(yuv->height_ == rgb->height_);
  assert(yuv->width_ == rgb->width_);

  auto y = yuv->y_;
  auto u = yuv->u_;
  auto v = yuv->v_;
  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;

  for(size_t i = 0; i < rgb->size_; i++){
    int rr = r[i];
    int gg = g[i];
    int bb = b[i];
    y[i] = clamp(((66 * rr + 129 * gg + 25 * bb + 128) >> 8) + 16);
    u[i] = clamp(((-38 * rr - 74 * gg + 112 * bb + 128) >> 8) + 128);
    v[i] = clamp(((112 * rr - 94 * gg - 18 * bb + 128) >> 8) + 128);
  }

}

void ImplSimple::AlphaBlend(RGB *rgb, uint8_t alpha) {
  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;
  for(size_t i = 0; i < rgb->size_; i++){
    r[i] = (int)alpha * r[i] / 256;
    g[i] = (int)alpha * g[i] / 256;
    b[i] = (int)alpha * b[i] / 256;
  }
}


#endif // INTEL_SIMD_IMPL_SIMPLE_H
