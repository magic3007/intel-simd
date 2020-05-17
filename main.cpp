#include <string>

#include "CLI11.hpp"
#include "config.h"
#include "utils/base.h"
#include "impl_simple.h"

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
  app.add_option("-f", fileName, "Input YUV420 file")
      -> required();
  CLI11_PARSE(app, argc, argv);

  YUV420 yuv_src = YUV420(kWidth, kHeight);
  YUV420 yuv_dst = YUV420(kWidth, kHeight);
  RGB rgb = RGB(kHeight, kWidth);
  DEFER({ yuv_src.Free();});
  DEFER({yuv_dst.Free();});
  DEFER({rgb.Free();});

  yuv_src.ReadFromYUVFile(fileName);

  for(size_t alpha = 0; alpha < 255; alpha += 3){
    ImplSimple simple;

    #define LIST_OF_IMPL \
    X(simple)

    #define X(name) \
    { \
      string nameString = string(#name); \
      string outFile = nameString + "_output_" \
        + std::to_string(alpha) + ".yuv"; \
      do_work(name, &yuv_src, &yuv_dst, &rgb, alpha); \
      yuv_dst.WriteToYUVFile(outFile); \
    }
    LIST_OF_IMPL
    #undef X

    #undef LIST_OF_IMPL
  }
  return 0;
}