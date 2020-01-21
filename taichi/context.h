#pragma once

#if defined(TI_RUNTIME_HOST)
#include "common.h"

namespace taichi::Tlang {
using namespace taichi;

template <typename T, typename G>
T union_cast_with_different_sizes(G g) {
  union {
    T t;
    G g;
  } u;
  u.g = g;
  return u.t;
}
#endif

struct Context {
  void *root;
  void *runtime;
  uint64 args[taichi_max_num_args];
  int32 extra_args[taichi_max_num_args][taichi_max_num_indices];

  Context() {
    root = nullptr;
  }

  Context(void *x) : Context() {
    root = x;
  }

#if defined(TI_RUNTIME_HOST)
  template <typename T>
  T get_arg(int i) {
    return union_cast_with_different_sizes<T>(args[i]);
  }

  template <typename T>
  void set_arg(int i, T v) {
    args[i] = union_cast_with_different_sizes<uint64>(v);
  }
#endif
};
#if defined(TI_RUNTIME_HOST)
}
#endif
