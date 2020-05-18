#ifndef INTEL_SIMD_IMPL_AVX_H
#define INTEL_SIMD_IMPL_AVX_H

#include <immintrin.h>

class SimdAVX{

public:
  using VectorType = __m256i;
  static constexpr size_t kStride = 256 / 16;

  static inline VectorType Zero(){
    return _mm256_setzero_si256();
  }

  static inline VectorType Constant(short c){
    return _mm256_set1_epi16(c);
  }

  static inline VectorType Add(const VectorType &a, const VectorType &b) {
    return _mm256_add_epi16(a, b);
  }

  static inline VectorType Sub(const VectorType &a, const VectorType &b){
    return _mm256_sub_epi16(a,b);
  }

  static inline VectorType Mul(const VectorType &a, const VectorType &b){
    return _mm256_mullo_epi16(a,b);
  }

  static inline VectorType Rli(const VectorType &a, int imm8){
    return _mm256_srai_epi16(a, imm8);
  }

  static inline VectorType Load(const uint8_t *src){
    auto t = _mm_setzero_si128();
    auto lo = _mm_unpacklo_epi8(_mm_loadl_epi64(reinterpret_cast<const __m128i_u *>(src)), t);
    auto hi = _mm_unpacklo_epi8(_mm_loadl_epi64(reinterpret_cast<const __m128i_u *>(src + 8)), t);
    return _mm256_inserti128_si256(_mm256_castsi128_si256(lo),hi,1);
  }


  static inline void Store(const VectorType &a, uint8_t *dst){
    auto v = _mm256_packs_epi16(a, Zero());
    // _mm256_storeu2_m128i(&hi, &lo, v);
    auto lo = _mm256_castsi256_si128(v);
    auto hi = _mm256_extractf128_si256(v, 1);
    _mm_storel_epi64(reinterpret_cast<__m128i_u *>(dst), lo);
    _mm_storel_epi64(reinterpret_cast<__m128i_u *>(dst + 8), hi);
  }

  static inline void Empty(){
  }

};

#endif // INTEL_SIMD_IMPL_AVX_H
