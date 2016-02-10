set terminal png
set logscale x 2
set title "Update Locations Benchmark"
set xlabel "Order of Problem Size"
set ylabel "Mean Time Per Coordinate (microseconds)"
plot 'benchmark_data_py.txt' using 2:5 with points