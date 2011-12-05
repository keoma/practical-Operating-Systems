#include "control.h"                                                                                                       /*The struct used to pass arguments is defined here.                       */
#include <time.h>                                                                                                          /*Necessary for stopping after a certain amount of seconds.                */
#include <pthread.h>                                                                                                       /*Mutex locking for thread safety.                                         */
                                                                                                                           /*Long double precision:                                                   */
                                                                                                                           /*http://en.wikipedia.org/wiki/Extended_precision                          */
                                                                                                                           /*15 bit exponent                                                          */
                                                                                                                           /*65 bit fraction                                                          */
                                                                                                                           /*The actual pi calculation takes place according to:                      */
                                                                                                                           /*http://en.wikipedia.org/wiki/Leibniz_formula_for_pi                      */

const long double pi_iteration_dividend = 8;                                                                               /*                                                                         */
const long double pi_iteration_four = 4;                                                                                   /*                                                                         */
const long double pi_iteration_three = 3;                                                                                  /*                                                                         */
const long double pi_iteration_one = 1;                                                                                    /*                                                                         */

long double pi_iteration(unsigned long iteration)                                                                          /*                                                                         */
{                                                                                                                          /*                                                                         */
 long double four_times_k = pi_iteration_four * (long double) iteration;                                                   /*                                                                         */
 long double divisor = (four_times_k + pi_iteration_one) * (four_times_k + pi_iteration_three);                            /*                                                                         */
 return pi_iteration_dividend/divisor;                                                                                     /*                                                                         */
}                                                                                                                          /*                                                                         */
                                                                                          
void calculatepi(void* mainArgs)                                                                                           /*Main calculation function                                                */
{                                                                                                                          /*                                                                         */
 struct argumentpasser* struct_args = mainArgs;                                                                            /*So we don't have to cast mainArgs on every call                          */
 *(struct_args->pi) = 0;                                                                                                   /*Initialise "pi".                                                         */
 time_t start;                                                                                                             /*Define a time_t to hold the starting time of the computation.            */
 start = time(NULL);                                                                                                       /*Get starting time.                                                       */
 unsigned long iteration;                                                                                                  /*Internal counter to keep track of the iterations.                        */
 for(iteration = 0; iteration <= struct_args->max_iterations && time(NULL) - start < struct_args->seconds; iteration++)    /*Loop trough the iterations of pi. Until we hit either the maximum amount */
 {                                                                                                                         /*of iterations or the maximum amount of seconds.                          */
  long double correction = pi_iteration(iteration);                                                                        /*Calculate difference with current pi.                                    */
  pthread_mutex_lock(struct_args->mutex_pi);                                                                               /*Lock mutex so "pi" can safely be written.                                */
  *(struct_args->pi) = *(struct_args->pi) + correction;                                                                    /*Modify "pi" according to the calculated correction.                      */
  pthread_mutex_unlock(struct_args->mutex_pi);                                                                             /*Unlock mutex, we are done with "pi" for now.                             */
 }                                                                                                                         /*                                                                         */
 pthread_mutex_lock(struct_args->mutex_busy);                                                                              /*Lock mutex so "busy" can be written safely.                              */
 *(struct_args->busy) = 0;                                                                                                 /*Set "busy" to zero to signal the end of the π calculations.              */
 pthread_mutex_unlock(struct_args->mutex_busy);                                                                            /*Unlock mutex, we are done with "busy" entirely.                          */
}
