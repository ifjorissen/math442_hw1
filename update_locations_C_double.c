
// #pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// thoughts on random # generation: 
// http://stackoverflow.com/questions/1340729/how-do-you-generate-a-random-double-uniformly-distributed-between-0-and-1-from-c
// http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c

// thoughts on timing:
// https://www.softwariness.com/articles/monotonic-clocks-windows-and-posix/
void generate_random_list(double *array, uint32_t size, double bound){
  double max = bound;
  double min = -bound;

  for (uint32_t i = 0; i<size; i++){
    array[i] = min + rand() / (RAND_MAX / (max - min));
  }
}

void update_coords(uint32_t size, double *x, double *y, double *z, double *vx, double *vy, double *vz){
  for(uint32_t i = 0; i < size; i ++){
    x[i] = x[i] + vx[i];
    y[i] = y[i] + vy[i];
    z[i] = z[i] + vz[i];
  }
}

int main(int argc, char *argv[]){
  const double bound = 1000.0;
  const double v_bound = 1.0;

  if (argc != 3){
    printf("Required arguments: vector_length(N) and iterations_num(M)");
    exit(EXIT_FAILURE);
  }

  // get command line args
  uint32_t size = (uint32_t)atoi(argv[1]);
  uint32_t iters = (uint32_t)atoi(argv[2]);

  // set seed
  srand(size);

  // initialize points
  double x[size];
  double y[size];
  double z[size];
  generate_random_list(x, size, bound);
  generate_random_list(y, size, bound);
  generate_random_list(z, size, bound);

  // initialize velocities
  double vx[size];
  double vy[size];
  double vz[size];
  generate_random_list(vx, size, v_bound);
  generate_random_list(vy, size, v_bound);
  generate_random_list(vz, size, v_bound);

  // time while we update coodinates iters number of times
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for(uint32_t i = 0; i < iters; i++){
    update_coords(size, x, y, z, vx, vy, vz);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  //compute the checksum
  double chksum = 0;

  for (uint32_t i = 0; i < size; i++){
    chksum += *(x + i) + *(y + i) + *(z + i);
    printf("x: %f y: %f z: %f, vx: %f vy: %f vz: %f checksum: %f iters: %u\n", *(x + i), *(y + i), *(z + i), *(vx + i), *(vy + i), *(vz + i), chksum, iters);
  }

  // output
  //convert nanoseconds to microseconds
  //convert seconds to microseconds
  long micro_sec =  1000000.0l * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000.0l;
  long mean_time = micro_sec/(size * iters);
  printf("Mean time per coordinate: %ld us\n", mean_time);
  printf("Final checksum is: %f", chksum);

  exit(EXIT_SUCCESS);
}
