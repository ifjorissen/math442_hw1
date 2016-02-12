
// #pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define SEC_TO_MICRO 1000000.0l
#define NANO_TO_MICRO 1000.0l


// Snippet for osx timing:
// http://stackoverflow.com/questions/21665641/ns-precision-monotonic-clock-in-c-on-linux-and-os-x
// Use clock_gettime in linux, clock_get_time in OS X.

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
int clock_gettime(struct timespec *tp){
  clock_serv_t cclock;
  mach_timespec_t mts;

  host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
  int retval = clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);

  tp->tv_sec = mts.tv_sec;
  tp->tv_nsec = mts.tv_nsec;
  return retval;
}
#endif


// thoughts on random # generation: 
// http://stackoverflow.com/questions/1340729/how-do-you-generate-a-random-double-uniformly-distributed-between-0-and-1-from-c
// http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
float * generate_random_list(uint32_t size, float bound){
  float max = bound;
  float min = -bound;

  float *list = calloc(size, sizeof(float));

  for (uint32_t i = 0; i<size; i++){
    list[i] = min + rand() / (RAND_MAX / (max - min));
  }
  return list;
}

void update_coords(uint32_t size, float *x, float *y, float *z, float *vx, float *vy, float *vz){
  for(uint32_t i = 0; i < size; i ++){
    x[i] = x[i] + vx[i];
    y[i] = y[i] + vy[i];
    z[i] = z[i] + vz[i];
  }
}

int main(int argc, char *argv[]){
  const float bound = 1000.0;
  const float v_bound = 1.0;

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
  float *x = generate_random_list(size, bound);
  float *y = generate_random_list(size, bound);
  float *z = generate_random_list(size, bound);

  // initialize velocities
  float *vx = generate_random_list(size, v_bound);
  float *vy = generate_random_list(size, v_bound);
  float *vz = generate_random_list(size, v_bound);

  // time while we update locations iters number of times
  struct timespec start, end;
  clock_gettime(&start);
  for(uint32_t i = 0; i < iters; i++){
    update_coords(size, x, y, z, vx, vy, vz);
  }
  clock_gettime(&end);

  //compute the checksum
  float chksum = 0;

  for (uint32_t i = 0; i < size; i++){
    chksum += *(x + i) + *(y + i) + *(z + i);
    //printf("x: %f y: %f z: %f, vx: %f vy: %f vz: %f checksum: %f iters: %u\n", *(x + i), *(y + i), *(z + i), *(vx + i), *(vy + i), *(vz + i), chksum, iters);
  }

  free(x);
  free(y);
  free(z);
  free(vx);
  free(vy);
  free(vz);

  // output
  //convert nanoseconds to microseconds
  //convert seconds to microseconds
  float micro_sec =  SEC_TO_MICRO * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / NANO_TO_MICRO;
  float mean_time = micro_sec/(size * iters);
  printf("Mean time per coordinate: %f us\n", mean_time);
  printf("Final checksum is: %f", chksum);

  exit(EXIT_SUCCESS);
}
