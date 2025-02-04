cmake_minimum_required(VERSION 3.29)
project(TinyRaster C)

set(CMAKE_C_STANDARD 23)

file(GLOB TinyRaster
     "*.h"
     "*.c"
)

add_executable(TinyRaster ${TinyRaster})
