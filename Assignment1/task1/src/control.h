#include <pthread.h>                                                                                                                  /*Used for threading and mutex locking.                                                            */

struct argumentpasser                                                                                                                 /*Struct that passes arguments through pthread_create.                                             */
{                                                                                                                                     /*                                                                                                 */
 long double* pi;                                                                                                                     /*Holds the calculated π.                                                                          */
 unsigned long seconds;                                                                                                               /*Holds the maximum amount of seconds the calculation is allowed to run.                           */
 char* busy;                                                                                                                          /*Used to signal the main thread when the calculation has finished.                                */
 unsigned long  max_iterations;                                                                                                       /*Holds the maximum amount of iterations the calculation is allowed to run.                        */
 pthread_mutex_t* mutex_pi;                                                                                                           /*Mutex to lock "pi" when reading or writing.                                                      */
 pthread_mutex_t* mutex_busy;                                                                                                         /*Mutex to lock "busy" when reading or writing.                                                    */
};                                                                                                                                    /*                                                                                                 */

int main(int argc, char* argv[]);                                                                                                     /*Main function.                                                                                   */
