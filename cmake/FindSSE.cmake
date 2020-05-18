if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  execute_process(COMMAND cat /proc/cpuinfo OUTPUT_VARIABLE CPUINFO)

  string(REGEX REPLACE "^.*(mmx).*$" "\\1" MMX_THERE ${CPUINFO})
  string(COMPARE EQUAL "mmx" "${MMX_THERE}" MMX_TRUE)
  if (MMX_TRUE)
    set(MMX_FOUND true CACHE BOOL "MMX available on host")
  else ()
    set(MMX_FOUND false CACHE BOOL "MMX available on host")
  endif ()

  string(REGEX REPLACE "^.*(sse2).*$" "\\1" SSE_THERE ${CPUINFO})
  string(COMPARE EQUAL "sse2" "${SSE_THERE}" SSE2_TRUE)
  if (SSE2_TRUE)
    set(SSE2_FOUND true CACHE BOOL "SSE2 available on host")
  else ()
    set(SSE2_FOUND false CACHE BOOL "SSE2 available on host")
  endif ()

  string(REGEX REPLACE "^.*(avx).*$" "\\1" SSE_THERE ${CPUINFO})
  string(COMPARE EQUAL "avx" "${SSE_THERE}" AVX_TRUE)
  if (AVX_TRUE)
    set(AVX_FOUND true CACHE BOOL "AVX available on host")
  else ()
    set(AVX_FOUND false CACHE BOOL "AVX available on host")
  endif ()

  string(REGEX REPLACE "^.*(avx2).*$" "\\1" SSE_THERE ${CPUINFO})
  string(COMPARE EQUAL "avx2" "${SSE_THERE}" AVX2_TRUE)
  if (AVX2_TRUE)
    set(AVX2_FOUND true CACHE BOOL "AVX2 available on host")
  else ()
    set(AVX2_FOUND false CACHE BOOL "AVX2 available on host")
  endif ()

else ()
  set(MMX_FOUND    true  CACHE BOOL "MMX available on host")
  set(SSE2_FOUND   true  CACHE BOOL "SSE2 available on host")
  set(AVX_FOUND    false CACHE BOOL "AVX available on host")
  set(AVX2_FOUND   false CACHE BOOL "AVX2 available on host")
endif ()

if (NOT MMX_FOUND)
  message(STATUS "Could not find hardware support for MMX on this machine.")
else()
    message(STATUS "MMX is available on host")
endif ()

if (NOT SSE2_FOUND)
  message(STATUS "Could not find hardware support for SSE2 on this machine.")
else()
    message(STATUS "SSE2 is available on host")
endif ()

if (NOT AVX_FOUND)
  message(STATUS "Could not find hardware support for AVX on this machine.")
else()
    message(STATUS "AVX is available on host")
endif ()

if (NOT AVX2_FOUND)
  message(STATUS "Could not find hardware support for AVX2 on this machine.")
else()
    message(STATUS "AVX2 is available on host")
endif ()

set(SSE_COMPILER_FLAGS )

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    if (MMX_FOUND)
        set(SSE_COMPILER_FLAGS "${SSE_COMPILER_FLAGS} -mmmx")
    endif ()

    if (SSE2_FOUND)
        set(SSE_COMPILER_FLAGS "${SSE_COMPILER_FLAGS} -mfpmath=sse -msse -msse2")
    endif ()

    if (AVX_FOUND)
        set(SSE_COMPILER_FLAGS "${SSE_COMPILER_FLAGS} -mavx")
    endif ()

    if (AVX2_FOUND)
        set(SSE_COMPILER_FLAGS "${SSE_COMPILER_FLAGS} -mavx2")
    endif ()
endif ()

mark_as_advanced(MMX_FOUND SSE2_FOUND AVX_FOUND SSE_COMPILER_FLAGS)