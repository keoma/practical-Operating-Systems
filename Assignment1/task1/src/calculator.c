#include <pthread.h>
#include "control.h"
#include <time.h>

void calculatepi(struct argumentpasser *args)
{
 time_t start;
 start = time(NULL);
 for (*(args->iteration) = 0; (*(args->iteration) < args->max_iterations) && (long)(time(NULL) - start) < args->seconds; *(args->iteration) = *(args->iteration)+1)
 {
  args->pi[*(args->iteration)] = *(args->iteration) % 256;
  usleep(100000);
 }
 *(args->busy) = 0;
}
