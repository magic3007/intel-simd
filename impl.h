#ifndef INTEL_SIMD_IMPL_H
#define INTEL_SIMD_IMPL_H

class Impl{
  public:
    virtual void YUV2RGB(YUV420 *yuv, RGB *rgb) = 0;
    virtual void AlphaBlend(RGB *rgb, uint8_t alpha) = 0;
    virtual void RGB2YUV(RGB *rgb, YUV420 *yuv) = 0;
};
#endif // INTEL_SIMD_IMPL_H
