

Fig 1 (benchmarks.png):
set terminal png
set logscale x 2
set title "Update Locations Benchmark"
set xlabel "Order of Problem Size"
set ylabel "Mean Time Per Coordinate (microseconds)"
set xtics auto
set ytics auto
set output 'benchmarks.png'
plot "data/benchmark_data_C_double.txt" using 2:5 title 'C(double)' with linespoints , \
     "data/benchmark_data_C_float.txt" using 2:5 title 'C(float)' with linespoints , \
     "data/benchmark_data_asm.txt" using 2:5 title 'ASM(float)' with linespoints , \
     "data/benchmark_data_py.txt" using 2:5 title 'python' with linespoints


Fig 2 (benchmarks_C.png):
set terminal png
set logscale x 2
set title "Update Locations Benchmark (C&ASM)"
set xlabel "Order of Problem Size"
set ylabel "Mean Time Per Coordinate (microseconds)"
set xtics auto
set ytics auto
set output 'benchmarks_C.png'
plot "data/benchmark_data_C_double.txt" using 2:5 title 'C(double)' with linespoints , \
     "data/benchmark_data_C_float.txt" using 2:5 title 'C(float)' with linespoints,\
     "data/benchmark_data_asm.txt" using 2:5 title 'ASM(float)' with linespoints