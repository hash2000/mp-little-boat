
message(STATUS "Use vcpkg ${CMAKE_TOOLCHAIN_FILE}")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{CMAKE_TOOLCHAIN_FILE}")
message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
set(VCPKG_TRACE_FIND_PACKAGE off)
set(VCPKG_MANIFEST_MODE off)
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)
include(${CMAKE_TOOLCHAIN_FILE})

include("cmake/libs/poco.cmake")
include("cmake/libs/fltk.cmake")
include("cmake/libs/ffmpeg.cmake")
