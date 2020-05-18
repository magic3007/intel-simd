#ifndef INTEL_SIMD_IMPL_MMX_H
#define INTEL_SIMD_IMPL_MMX_H

#include <emmintrin.h>

class SimdMMX{
public:
  using VectorType = __m64;
  static constexpr size_t kStride = 64 / 16;

  static inline VectorType Zero(){
    return _mm_setzero_si64();
  }

  static inline VectorType Constant(short c){
    return _mm_set1_pi16(c);
  }

  static inline VectorType Add(const VectorType &a, const VectorType &b){
    return _mm_add_pi16(a, b);
  }

  static inline VectorType Sub(const VectorType &a, const VectorType &b){
    return _mm_sub_pi16(a,b);
  }

  static inline VectorType Mul(const VectorType &a, const VectorType &b){
    return _mm_mullo_pi16(a,b);
  }

  static inline VectorType Rli(const VectorType &a, int imm8){
    return _mm_srai_pi16(a, imm8);
  }

  static inline VectorType Load(const uint8_t *src){
    return _mm_unpacklo_pi8(_m_from_int(*(uint32_t *)src), Zero());
  }

  static inline void Store(const VectorType &a, uint8_t *dst){
    *(uint32_t *)dst = _m_to_int(_mm_packs_pi16(a, Zero()));
  }

  static inline void Empty(){
    _mm_empty();
  }

};

#endif // INTEL_SIMD_IMPL_MMX_H
