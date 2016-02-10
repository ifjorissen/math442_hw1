### HW 1 Math 442
#### @ifjorissen

### Part 1: Benchmark Python
  * create benchmark data with `python3 update_py_bench.py`

### Part 2: Port to C with Double and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_double.c -o update_locations_C_double.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_double.o`
  * create benchmark data with `python3 update_c_bench.py`
  * Note that the data will be written to `c_bench.py`

### Part 3: Port to C with Float and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_float.c -o update_locations_C_float.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_float.o`
  * create benchmark data with `python3 update_c_bench.py`
  * Note that the data will be written to `c_bench.py`

### Part 4


### Part 5