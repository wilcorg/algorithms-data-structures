#!/bin/bash

cmake --build ../src/arr_gen/cmake-build-debug --target arr_gen
cmake --build ../src/arr_sort/cmake-build-debug --target arr_sort
ARR_GEN=../src/arr_gen/cmake-build-debug/arr_gen
ARR_SORT=../src/arr_sort/cmake-build-debug/arr_sort
N=15

printf "Input:\n"
printf "ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy insertion"
printf "\nOutput:\n"
ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy insertion

printf "\n\nInput:\n"
printf "ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy quick"
printf "\nOutput:\n"
ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy quick

printf "\n\nInput:\n"
printf "ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy quick_hybrid --hybrid_threshold 5"
printf "\nOutput:\n"
ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy quick_hybrid --hybrid_threshold 5

printf "\n\nInput:\n"
printf "ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy dual_pivot --hybrid_threshold 5"
printf "\nOutput:\n"
ARR_GEN --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ARR_SORT --strategy dual_pivot --hybrid_threshold 5
