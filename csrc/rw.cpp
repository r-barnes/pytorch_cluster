#include <Python.h>
#include <torch/script.h>

#include "cpu/rw_cpu.h"

#ifdef _WIN32
PyMODINIT_FUNC PyInit__rw(void) { return NULL; }
#endif

torch::Tensor random_walk(torch::Tensor rowptr, torch::Tensor col,
                          torch::Tensor start, int64_t walk_length, double p,
                          double q) {
  if (rowptr.device().is_cuda()) {
#ifdef WITH_CUDA
    AT_ERROR("No CUDA version supported");
#else
    AT_ERROR("Not compiled with CUDA support");
#endif
  } else {
    return random_walk_cpu(rowptr, col, start, walk_length, p, q);
  }
}

static auto registry =
    torch::RegisterOperators().op("torch_cluster::random_walk", &random_walk);
