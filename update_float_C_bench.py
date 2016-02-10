#!/usr/bin/env python3
#@ifjorissen
#2.9.16
#update_py_bench.py: a simple python script to run update_locations.py and capture output

import subprocess

#define start and max order for problem size
#also define a number of runs, which is how many times we execute
#a given problem size with a given number of iterations
START_ORDER = 8
MAX_ORDER = 25
RUNS = 10

#intialize datafile
data_file = open('data/benchmark_data_C_float.txt', 'w')
data_file.write("Run\t Order\t Problem Size\t Iterations\t Mean Time\t Checksum\n")

for i in range(START_ORDER, MAX_ORDER):
  #set the problem size and the number of iterations
  size = 2**i

  #set the number of iterations to run
  iters = int((MAX_ORDER - i)*(2**((MAX_ORDER - i)/2)))

  #call update_locations.py 
  command = './update_locations_C_float.o {} {}'.format(size, iters)
  print("running {} runs with {} points and updating {} times".format(RUNS, size, iters))

  for j in range(RUNS):

    #obtain & decode the output so we can write the relevant data to a file
    out = subprocess.check_output(command, shell=True)
    output = out.decode(encoding="utf-8")
    
    # output is of the form: "Mean time per coordinate: 8.194499969249591 us Final checksum is: 1233.3683773560347" 
    mean_time = output.split(" ")[4]
    chksum = output.split(" ")[-1]

    #write to file
    data_file.write("{!s}\t{!s}\t{!s}\t{!s}\t{!s}\t{!s}\n".format(j, i, size, iters, mean_time, chksum))


exit(0)