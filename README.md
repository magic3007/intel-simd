# Intel-SIMD
⚡ Leverage Intel vectorization technique **MMX**, **SSE2** and **AVX** to accelerate the process of converting YUV420 image into RGB image.
## Example
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
./demo --help
./demo -f ../testcases/dem1.yuv
```

## Resource

- [YUView](https://github.com/IENT/YUView): The Free and Open Source Cross Platform YUV Viewer with an advanced analytics toolset