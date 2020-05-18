# Intel-SIMD
⚡ Leverage Intel vectorization technique **MMX**, **SSE2** and **AVX** to accelerate the processing of converting YUV420 image into RGB image.
## Example
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
./demo -f ../testcases/dem1.yuv
```