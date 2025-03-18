cmake_minimum_required(VERSION 3.31)
project(TinyRaster C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(TinyRaster main.c src/ppm.c src/memory/arena_allocator.c src/memory/heap_allocator.c src/vec3f.c src/mat4f.c src/helpers.h
        src/obj_reader.c
        src/obj_reader.h
        src/transform.c
        src/transform.h
        src/camera.c
        src/camera.h
        src/mat4f.c
        src/mat4f.h
        src/mesh.c
        src/mesh.h
        src/camera.c
        src/quaternion.h
        src/quaternion.c)

target_link_libraries(TinyRaster m SDL3::SDL3)



target_compile_options(TinyRaster PRIVATE
  $<$<CONFIG:Debug>:-g -O0 -ffast-math -march=native -Wall -Wextra>
  $<$<CONFIG:Release>:-Ofast -ffast-math -march=native -DNDEBUG>
  $<$<CONFIG:RelWithDebInfo>:-Ofast -ffast-math -march=native -g>
  $<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
)