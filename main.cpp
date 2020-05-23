#include <string>

#include "CLI11.hpp"
#include "config.h"
#include "utils/base.h"
#include "utils/stopwatch.hpp"
#include "impl_simple.h"
#include "impl_simd.h"
#include "impl_mmx.h"
#include "impl_sse2.h"
#include "impl_avx.h"

using std::string;
void do_work(Impl &impl, YUV420 *yuv_src, YUV420 *yuv_dst, RGB *rgb,
             uint8_t alpha){
  impl.YUV2RGB(yuv_src, rgb);
  impl.AlphaBlend(rgb, alpha);
  impl.RGB2YUV(rgb, yuv_dst);
}

int main(int argc, char *argv[]){
  CLI::App app("Convert YUV420 file to RGB");
  std::string fileName = "default";
  bool should_dump = false;
  app.add_option("-f", fileName, "Input YUV420 file")
      -> required();
  app.add_option("-s", should_dump, "Whether to dump the output");
  CLI11_PARSE(app, argc, argv);

  YUV420 yuv_src = YUV420(kWidth, kHeight);
  YUV420 yuv_dst = YUV420(kWidth, kHeight);
  RGB rgb = RGB(kHeight, kWidth);
  DEFER({ yuv_src.Free();});
  DEFER({yuv_dst.Free();});
  DEFER({rgb.Free();});

  yuv_src.ReadFromYUVFile(fileName);

  ImplSimple simple_isa;
  ImplSimd<SimdMMX> mmx;
  ImplSimd<SimdSSE2> sse2;
  ImplSimd<SimdAVX> avx;

  #define LIST_OF_IMPL \
    X(simple_isa) \
    X(mmx) \
    X(sse2) \
    X(avx)

  #define X(name) try{ \
    stopwatch::Stopwatch stopwatch; \
    stopwatch.start(); \
    for (size_t alpha = 0; alpha < 255; alpha += 1) { \
      do_work(name, &yuv_src, &yuv_dst, &rgb, alpha); \
      if (should_dump){ \
        string nameString = string(#name); \
        string outFile = nameString + "_output_" + std::to_string(alpha) + ".yuv"; \
        yuv_dst.WriteToYUVFile(outFile); \
      } \
    } \
    std::cout << std::left << std::setw(10) << #name << ": " << std::setw(8) \
      << std::right << stopwatch.elapsed<stopwatch::ms>() << "ms" << std::endl; \
  }catch (const std::exception& e) { \
    std::cerr << #name << ": " << e.what() << std::endl; \
  }
  LIST_OF_IMPL
  #undef X

  #undef LIST_OF_IMPL
  return 0;
}