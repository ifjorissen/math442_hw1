
###HW1 (Galaxy Explorers) Results
##### @ifjorissen

#### Note: 
I used various code snippets, perhaps most notably an implementation of clock_gettime() which is compatible with Mac OSX. While all of this code *should* run on a Linux box, I ran it on my laptop (mac). 

#### Part 1: Benchmark Python
  * a) Explain the number of iterations you chose and why
    * I decided to used a scaling number of iterations so the that the largest problem sizes would take less time to run and the deviations in the smaller problem sizes would be leveled out. More precisely, though this was, perhaps "overkill," a problem size of type 2^i would be run (MAX_ORDER - i)(2^((MAX_ORDER - i)/4))), where MAX_ORDER is the order of the largest problem size we might encounter. I will note that the other problem sizes don't directly influence the runtime, or number of iterations necessary to combat variance. However, using a function like this was convienient, as it ran the smallest problem sizes thousands of times while running the largest problem sizes only a handful of times.

  * b) For each problem size, the update_locations.py script is run 10 times (as indicated by the RUNS constant in the update_py_bench.py script, and similarly in the others). This allows me to understand the amount of variation there is across a major run. 

  * c) see the "figs" folder for images. For each port, there is a corresponding scatter plot which shows the mean time spent per coordinate (as a funciton of the number of objects in the system) for each of the RUNS (default, 10). 
    * In the python scatter plot (benchmark_py_scatter.png) the difference in mean coodinate time is ~.03 microseconds. This seems to hold true for each of the problem sizes.  
    * In the C(float) and C(double) scatter plots (benchmark_C_float_scatter.png and benchmark_C_double_scatter.png) the difference in mean coodinate time is much less consistent.
    * The benchmarks are all compared in the plot benchmarks.png. It is clear that the original python version is much, much slower than either of the C ports (~30x slower). 
    * benchmarks_C.png is a plot of the C ports using floats and doubles. It makes sense that the float version generally outperformed the version implemented with doubles. 

#### Parts 2 and 3 (Port to C using doubles and floats):
  * See figs/benchmarks.png for an image of all three (Cw/Float Cw/double and Python) plotted together
  * See figs/benchmarks_C_and_asm.png for a plot of the C ports using floats and doubles. It makes sense that the float version generally outperformed the version implemented with doubles (since they are of a smaller size).
  * See benchmark_C_float_scatter.png and benchmark_C_double_scatter.png for scatter plots of the two implementations as the mean time per coodinate (on a given problem size) varied throughout the 10 runs. Note that the difference in mean coodinate time is much less consistent than we saw in the python implementation.


#### Part 4: Port to ASM & Benchmark
  * I relied pretty heavily on the output of `gcc update_locations_C_float.c -o update_locations_C_float_asm03 -Wall -Werror -Wextra -pedantic -O3 -g -S` to write this inline asm. 
  * See benchmark_asm_scatter.png for a scatter plot of how the asm implementation's mean time per coordinate varied throught the 10 runs and the problem sizes. 
  * See benchmark_C_and_asm.png for a graph of the mean time to update location vs problem size. Note that the asm is anywhere from 1.5-5x faster depending on the problem size. Each of the ports has a "bump" in mean time per coordinate update for problem sizes ~2^14 to 2^19 and then again around ~2^22. I'm not quite sure why this exists, or why it's most pronounced in the asm port. 


#### Part 5: Memory Profiling
  * I used two of valgrind's tools, memcheck and massif, to understand more about how much memory was being used in each of the three programs. As I understand it, memcheck outputs a summary of total bytes allocates & freed throughout the lifetime of the program, while massif outputs (as its default) much more verbose output detailing when and how memory was being used, allocated, freed, etc during the programs execution. Since we only allocated memory once (when we generated the random x,y,z and vx,vy,vz arrays) I found these two tools to be relatively consistent in their results. 

  * C(Float) memcheck results:
    * ```
      ==14345== Command: ./update_locations_C_float.o 1048576 11
      ==14345== Parent PID: 53159
      ==14345== 
      ==14345== 
      ==14345== HEAP SUMMARY:
      ==14345==     in use at exit: 26,621 bytes in 191 blocks
      ==14345==   total heap usage: 281 allocs, 90 frees, 25,198,685 bytes allocated
      ```
  * C(double) memcheck results:
   * ```
      ==14266== Command: ./update_locations_C_double.o 1048576 11
      ==14266== Parent PID: 53159
      ==14266== 
      ==14266== 
      ==14266== HEAP SUMMARY:
      ==14266==     in use at exit: 26,621 bytes in 191 blocks
      ==14266==   total heap usage: 281 allocs, 90 frees, 50,364,509 bytes allocated
      ==14266==
      ```
  * ASM(float) memcheck results:
    * ```
      ==33639== Command: ./update_locations_asm.o 1048576 11
      ==33639== Parent PID: 33067
      ==33639== 
      ==33639== 
      ==33639== HEAP SUMMARY:
      ==33639==     in use at exit: 26,621 bytes in 191 blocks
      ==33639==   total heap usage: 281 allocs, 90 frees, 25,198,685 bytes allocated
      ==33639==  
      ```

  * It makes sense that the ASM and float ports used the same amount of memory, since they both used floating types and were basically the same program except the update_coordinates function called a loop written with inline assembly instead of a standard C loop. It also makes sense that the amount of memory used in update_locations_C_double.c was 2x the amount used in either the asm or float implementations, since the size of a double is 2x the size of a floating point number. Finally, the number of memory allocations, frees, and blocks remained consistent across all three implementations because they all used the same calling scheme (insofar as they all followed the same set of instructions with respect to memory allocation, useage, and deallocation.)
  * For the raw, detailed, complete results, see the `memory` folder.


---

### Running this yourself
#### Part 1: Benchmark Python
  * create benchmark data with `python3 update_py_bench.py`

#### Part 2: Port to C with Double and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_double.c -o update_locations_C_double.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_double.o`
  * create benchmark data with `python3 update_double_C_bench.py`
  * Note that the data will be written to `benchmark_data_C_double.txt`

#### Part 3: Port to C with Float and Benchmark
  * Compile the C port of update_coordinates.py with: `gcc update_locations_C_float.c -o update_locations_C_float.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_C_float.o`
  * create benchmark data with `python3 update_float_C_bench.py`
  * Note that the data will be written to `benchmark_data_C_float.txt`

#### Part 4: Port update_coordinates to ASM
  * Compile the asm/C port of update_coordinates.py with: `gcc update_locations_asm.c -o update_locations_asm.o -Wall -Werror -Wextra -pedantic -O0 -g`
  * run with `./update_locations_asm.o`
  * create benchmark data with `python3 update_asm_C_bench.py`
  * Note that the data will be written to `benchmark_data_asm.txt`


#### Part 5: Profile the memory usage for the problem size 2^20. (11 iterations)
  * Massif
    * For each of the three ports (double, float, asm), run valgrind's massif:
      * `valgrind --tool=massif ./update_locations_C_double.o 1048576 11`
      * `valgrind --tool=massif ./update_locations_C_float.o 1048576 11`
      * `valgrind --tool=massif ./update_locations_asm.o 1048576 11`
    * For each output file (massif.out.<pid>) 
      * `ms_print massif.out.14177 > memory/c_double_mem_massif.txt`
      * `ms_print massif.out.14433 > memory/c_float_mem_massif.txt`
      * `ms_print massif.out.33523 > memory/asm_mem_massif.txt`
  * Memcheck
    * For each of the three ports (double, float, asm), run valgrind's memcheck:
      * `valgrind --tool=memcheck --log-file='memory/c_double_mem_memcheck.txt' ./update_locations_C_double.o 1048576 11`
      * `valgrind --tool=memcheck --log-file='memory/c_float_mem_memcheck.txt' ./update_locations_C_float.o 1048576 11`
      * `valgrind --tool=memcheck --log-file='memory/asm_mem_memcheck.txt' ./update_locations_asm.o 1048576 11`

