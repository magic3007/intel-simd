#ifndef INTEL_SIMD_IMPL_SSE2_H
#define INTEL_SIMD_IMPL_SSE2_H

#include <emmintrin.h>

class SimdSSE2{
public:
  using VectorType = __m128i;
  static constexpr size_t kStride = 128 / 16;

  static inline VectorType Zero(){
    return _mm_setzero_si128();
  }

  static inline VectorType Constant(short c){
    return _mm_set1_epi16(c);
  }

  static inline VectorType Add(const VectorType &a, const VectorType &b){
    return _mm_add_epi16(a, b);
  }

  static inline VectorType Sub(const VectorType &a, const VectorType &b){
    return _mm_sub_epi16(a,b);
  }

  static inline VectorType Mul(const VectorType &a, const VectorType &b){
    return _mm_mullo_epi16(a,b);
  }

  static inline VectorType Rli(const VectorType &a, int imm8){
    return _mm_srai_epi16(a, imm8);
  }

  static inline VectorType Load(const uint8_t *src){
    const auto rv = _mm_loadl_epi64(reinterpret_cast<const __m128i_u *>(src));
    return _mm_unpacklo_epi8(rv, Zero());
  }

  static inline void Store(const VectorType &a, uint8_t *dst){
    const auto rv = _mm_packs_epi16(a, Zero());
    _mm_storel_epi64(reinterpret_cast<__m128i_u *>(dst), rv);
  }

  static inline void Empty(){
  }

};

#endif // INTEL_SIMD_IMPL_SSE2_H
