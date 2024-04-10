#!/bin/bash
N=15

printf "\n\nInput:\n"
printf "./arr_gen --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot"
printf "\nOutput:\n"
./arr_gen --mode rand --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot

printf "\n\nInput:\n"
printf "./arr_gen --mode asc --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot"
printf "\nOutput:\n"
./arr_gen --mode asc --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot

printf "\n\nInput:\n"
printf "./arr_gen --mode desc --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot"
printf "\nOutput:\n"
./arr_gen --mode desc --count $N  --low 0 --high $((2 * N - 1)) | ./arr_sort --strategy dual_pivot
