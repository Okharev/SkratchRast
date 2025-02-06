#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro for defining a dynamic array type
#define DYN_ARR_TYPE(type, name)                                         \
  typedef struct {                                                       \
    type* data;                                                          \
    size_t size;                                                         \
    size_t capacity;                                                     \
  } name##DynArr;                                                        \
                                                                         \
  name##DynArr name##DynArr_init(size_t capacity);                       \
  void name##DynArr_reserve(name##DynArr* arr, size_t capacity);         \
  void name##DynArr_pushback(name##DynArr* arr, type item);              \
  void name##DynArr_emplace(name##DynArr* arr, size_t index, type item); \
  void name##DynArr_clear(name##DynArr* arr);                            \
  void name##DynArr_free(name##DynArr* arr);

#define DYN_ARR_IMPL(type, name)                                         \
  name##DynArr name##DynArr_init(size_t capacity) {                      \
    name##DynArr dyn_arr;                                                \
    dyn_arr.data = (type*)malloc(sizeof(type) * capacity);               \
    if (!dyn_arr.data) {                                                 \
      fprintf(stderr, "Memory allocation failed\n");                     \
      exit(EXIT_FAILURE);                                                \
    }                                                                    \
    dyn_arr.size = 0;                                                    \
    dyn_arr.capacity = capacity;                                         \
    return dyn_arr;                                                      \
  }                                                                      \
                                                                         \
  void name##DynArr_reserve(name##DynArr* arr, size_t capacity) {        \
    if (arr->capacity >= capacity)                                       \
      return;                                                            \
    type* new_data = (type*)realloc(arr->data, sizeof(type) * capacity); \
    if (!new_data) {                                                     \
      fprintf(stderr, "Memory reallocation failed\n");                   \
      exit(EXIT_FAILURE);                                                \
    }                                                                    \
    arr->data = new_data;                                                \
    arr->capacity = capacity;                                            \
  }                                                                      \
                                                                         \
  void name##DynArr_pushback(name##DynArr* arr, type item) {             \
    if (arr->size >= arr->capacity) {                                    \
      size_t new_capacity = arr->capacity ? arr->capacity * 2 : 1;       \
      name##DynArr_reserve(arr, new_capacity);                           \
    }                                                                    \
    arr->data[arr->size++] = item;                                       \
  }                                                                      \
                                                                         \
  void name##DynArr_free(name##DynArr* arr) {                            \
    free(arr->data);                                                     \
    arr->data = NULL;                                                    \
    arr->capacity = 0;                                                   \
    arr->size = 0;                                                       \
  }

#endif  // DYN_ARR_H
