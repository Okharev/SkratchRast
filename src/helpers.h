#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <math.h>

#define PI_F acosf(-1.0f)

#ifdef NDEBUG
#define ASSERT_MSG(expr, fmt, ...) ((void)0)
#else
#define ASSERT_MSG(expr, fmt, ...)                                                                                                              \
  do {                                                                                                                                          \
    if (!(expr)) {                                                                                                                              \
      fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %d.\n" fmt "\n", #expr, __func__, __FILE__, __LINE__, ##__VA_ARGS__); \
      abort();                                                                                                                                  \
    }                                                                                                                                           \
  } while (0)
#endif

#endif