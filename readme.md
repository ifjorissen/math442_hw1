### HW 1 Math 442
#### @ifjorissen

###HW1 Results

#### Note: 
I used various code snippets, perhaps most notably an implementation of clock_gettime() which is compatible with Mac OSX. While all of this code *should* run on a Linux box, I ran it on my laptop (mac). 

#### Part 1: Benchmark Python
  * a) Explain the number of iterations you chose and why
    * I decided to used a scaling number of iterations so the that the largest problem sizes would take less time to run and the deviations in the smaller problem sizes would be leveled out. More precisely, though this was, perhaps "overkill," a problem size of type 2^i would be run (MAX_ORDER - i)(2^((MAX_ORDER - i)/4))), where MAX_ORDER is the order of the largest problem size we might encounter. I will note that the other problem sizes don't directly influence the runtime, or number of iterations necessary to combat variance. However, using a function like this was convienient, as it ran the smallest problem sizes thousands of times while running the largest problem sizes only a handful of times.

  * b) For each problem size, the update_locations.py script is run 10 times (as indicated by the RUNS constant in the update_py_bench.py script, and similarly in the others). This allows me to understand the amount of variation there is across a major run. 


#### Part 4: Port to ASM & Benchmark
  * To do ...

#### Part 5: Estimate the amount of memory used by the program
  * To do ...


### Running this yourself
#### Part 1: Benchmark Python
  * create benchmark data with `python3 update_py_bench.py`

#### Part 2: Port to C with Double and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_double.c -o update_locations_C_double.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_double.o`
  * create benchmark data with `python3 update_c_bench.py`
  * Note that the data will be written to `c_bench.py`

#### Part 3: Port to C with Float and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_float.c -o update_locations_C_float.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_float.o`
  * create benchmark data with `python3 update_c_bench.py`
  * Note that the data will be written to `c_bench.py`

#### Part 4


#### Part 5