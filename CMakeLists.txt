cmake_minimum_required(VERSION 3.31)
project(TinyRaster C)

set(CMAKE_C_STANDARD 23)

add_executable(TinyRaster main.c src/ppm.c src/memory/arena_allocator.c src/memory/heap_allocator.c src/vec3f.c src/mat4f.c src/helpers.h)
