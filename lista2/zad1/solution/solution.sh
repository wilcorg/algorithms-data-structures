#!/bin/bash
cp ../arr_gen/cmake-build-debug/arr_gen ../arr_sort/cmake-build-debug/arr_sort .

printf "Input:\n"
printf "./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy insertion"
printf "\nOutput:\n"
./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy insertion

printf "\n\nInput:\n"
printf "./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy quick"
printf "\nOutput:\n"
./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy quick

printf "\n\nInput:\n"
printf "./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy quick_hybrid --hybrid_threshold 5"
printf "\nOutput:\n"
./arr_gen --mode rand --count 15  --low 0 --high 100 | ./arr_sort --strategy quick_hybrid --hybrid_threshold 5
