cmake_minimum_required(VERSION 3.31)
project(TinyRaster C)

set(CMAKE_C_STANDARD 23)

add_executable(TinyRaster main.c src/ppm.c src/memory/arena_allocator.c src/memory/heap_allocator.c src/vec3f.c src/mat4f.c src/helpers.h
        src/obj_reader.c
        src/obj_reader.h
        src/camera.c
        src/camera.h)
target_link_libraries(TinyRaster m)

target_compile_options(TinyRaster PRIVATE
  $<$<CONFIG:Debug>:-g -O0 -ffast-math -march=native -Wall -Wextra>
  $<$<CONFIG:Release>:-Ofast -ffast-math -march=native -DNDEBUG>
  $<$<CONFIG:RelWithDebInfo>:-Ofast -ffast-math -march=native -g>
  $<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
)