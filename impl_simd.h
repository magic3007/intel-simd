#ifndef INTEL_SIMD_IMPL_SIMD_H
#define INTEL_SIMD_IMPL_SIMD_H

// Reference: https://software.intel.com/sites/landingpage/IntrinsicsGuide/#expand=2231,1880

#include <cassert>
#include "impl.h"


template<class SIMD>
class ImplSimd : public Impl{
  public:
  void YUV2RGB(YUV420 *yuv, RGB *rgb) override;
  void AlphaBlend(RGB *rgb, uint8_t alpha) override;
  void RGB2YUV(RGB *rgb, YUV420 *yuv) override;
private:
  static constexpr size_t kStride = SIMD::kStride;
  using Vector = typename SIMD::VectorType;
};

#define add(a,b)   SIMD::Add(a,b)
#define sub(a,b)   SIMD::Sub(a,b)
#define mul(a,b)   SIMD::Mul(a,b)
#define rli(a,b)   SIMD::Rli(a,b)
#define load(a)    SIMD::Load(a)
#define store(a,b) SIMD::Store(a,b)
#define cn(a)      SIMD::Constant(a)

template <class SIMD>
void ImplSimd<SIMD>::YUV2RGB(YUV420 *yuv, RGB *rgb) {
  assert(yuv->height_ == rgb->height_);
  assert(yuv->width_ == rgb->width_);
  assert(yuv->size_ % kStride == 0);

  auto y = yuv->y_;
  auto u = yuv->u_;
  auto v = yuv->v_;
  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;

  for(size_t i = 0; i < yuv->size_; i += kStride){
    Vector c = sub(load(y+i), cn(16));
    Vector d = sub(load(u+i), cn(128));
    Vector e = sub(load(v+i), cn(128));

    /*
    r[i] = clamp((298 * c + 409 * e + 128) >> 8);
    g[i] = clamp((298 * c - 100 * d - 208 * e + 128) >> 8);
    b[i] = clamp((298 * c + 516 * d + 128) >> 8);
     */
    store(rli(add(add(mul(cn(298),c),mul(cn(409),e)),cn(128)), 8), r + i);
    store(rli(add(sub(sub(mul(cn(298),c),mul(cn(100),d)),mul(cn(208),e)), cn(128)), 8), g + i);
    store(rli(add(add(mul(cn(298),c),mul(cn(516),d)),cn(128)), 8), b + i);
    SIMD::Empty();
  }
}

template <class SIMD>
void ImplSimd<SIMD>::RGB2YUV(RGB *rgb, YUV420 *yuv) {
  assert(yuv->height_ == rgb->height_);
  assert(yuv->width_ == rgb->width_);
  assert(yuv->size_ % kStride == 0);

  auto y = yuv->y_;
  auto u = yuv->u_;
  auto v = yuv->v_;
  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;

  for(size_t i = 0; i < yuv->size_; i += kStride){
    Vector c = load(r+i);
    Vector d = load(g+i);
    Vector e = load(b+i);

    /*
    y[i] = clamp(((66 * c + 129 * d + 25 * e + 128) >> 8) + 16);
    u[i] = clamp(((-38 * c - 74 * d + 112 * e + 128) >> 8) + 128);
    v[i] = clamp(((112 * c - 94 * d - 18 * e + 128) >> 8) + 128);
     */
    store(add(rli(add(add(add(mul(cn(66),c), mul(cn(129), d)), mul(cn(25), e)), cn(128)),8), cn(16)), y+i);
    store(add(rli(add(sub(sub(mul(cn(112),e), mul(cn(38), c)), mul(cn(74), d)), cn(128)),8), cn(128)), u+i);
    store(add(rli(add(sub(sub(mul(cn(112),c), mul(cn(94), d)), mul(cn(18), e)), cn(128)),8), cn(128)), v+i);
    SIMD::Empty();
  }

}
template <class SIMD>
void ImplSimd<SIMD>::AlphaBlend(RGB *rgb, uint8_t alpha) {
  assert(rgb->size_ % kStride == 0);

  auto r = rgb->r_;
  auto g = rgb->g_;
  auto b = rgb->b_;

  Vector const_alpha = cn(alpha);

  for(size_t i = 0; i < rgb->size_; i += kStride){
    Vector c = load(r+i);
    Vector d = load(g+i);
    Vector e = load(b+i);
    /*
    r[i] = (uint32_t)alpha * r[i] >> 8;
    g[i] = (uint32_t)alpha * g[i] >> 8;
    b[i] = (uint32_t)alpha * b[i] >> 8;
     */
    store(rli(mul(const_alpha, c),8),r+i);
    store(rli(mul(const_alpha, d),8),g+i);
    store(rli(mul(const_alpha, e),8),b+i);
    SIMD::Empty();
  }
}

#undef add
#undef sub
#undef mul
#undef rli
#undef load
#undef store
#undef cn

#endif // INTEL_SIMD_IMPL_SIMD_H
