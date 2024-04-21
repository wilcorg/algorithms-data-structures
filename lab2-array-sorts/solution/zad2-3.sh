#!/bin/bash

BENCHMARK=../src/benchmark/cmake-build-debug/benchmark
cmake --build ../src/benchmark/cmake-build-debug --target benchmark

printf "n;c;s;c_n;s_n\n" > dataset/insertion_k=1
printf "n;c;s;c_n;s_n\n" > dataset/insertion_k=10
printf "n;c;s;c_n;s_n\n" > dataset/insertion_k=100
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=1
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=10
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=100
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=1
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=10
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=100
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=1
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=10
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=100
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=1_long
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=10_long
printf "n;c;s;c_n;s_n\n" > dataset/kmerge_k=100_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=1_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=10_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_k=100_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=1_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=10_long
printf "n;c;s;c_n;s_n\n" > dataset/quick_hybrid_k=100_long
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=1
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=10
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=100
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=1_long
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=10_long
printf "n;c;s;c_n;s_n\n" > dataset/dual_pivot_k=100_long
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=1
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=10
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=100
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=1_long
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=10_long
printf "n;c;s;c_n;s_n\n" > dataset/merge_k=100_long

for i in {10..50..10}
do
  for k in 1 10 100
  do
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy insertion --k $k >> dataset/insertion_k=$k
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy quick --k $k >> dataset/quick_k=$k
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy quick_hybrid --k $k >> dataset/quick_hybrid_k=$k
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy kmerge --k $k >> dataset/kmerge_k="$k"
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy merge --k $k >> dataset/merge_k="$k"
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy dual_pivot --k $k >> dataset/dual_pivot_k="$k"
  done
done

for i in {1000..50000..1000}
do
  for k in 1 10 100
  do
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy quick --k $k >> dataset/quick_k="$k"_long
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy quick_hybrid --k $k >> dataset/quick_hybrid_k="$k"_long
     BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy kmerge --k $k >> dataset/kmerge_k="$k"_long
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy merge --k $k >> dataset/merge_k="$k"_long
    BENCHMARK --mode rand --count $i --high $((2 * i - 1)) --strategy dual_pivot --k $k >> dataset/dual_pivot_k="$k"_long
  done
done

