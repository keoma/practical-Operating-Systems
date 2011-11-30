#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  /* Necessary for the sleep function */
#include "pi.h"

/*
 * source: http://3.141592653589793238462643383279502884197169399375105820974944592.com/
 */
const long double real_pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

int main(int argc, char* argv[])                                          /*main function*/
{
 if (argc < 3)                                                            /*Too few arguments specified.*/
 {
  puts("ERROR: Please specify the desired amount of iterations and the desired maximum running time.");/*Ask the user to specify the required arguments.*/
  exit(-1);                                                               /*Exit with error status*/
 }
 if (argc > 3)                                                            /*Too many arguments specified.*/
 {
  printf("WARNING: Disregarding %d trailing arguments.\n",argc - 2);      /*Warn the user that excess arguments have will be disregarded.*/
 }
 
 int returncode;                                                          /*Return code for pthread_create. */
 pthread_t       pth_calculator;                                          /*The pthread that will run the calculation.*/
 pthread_attr_t  thread_attributes;                                       /*The attributes for the abovementioned pthread.*/
 busy = 1;                                                                /*Set busy to 1 MUST occur before pthread_create is called.*/
 struct_argpasser.pi = &pi;                                                /*Pointer to pi in the struct.*/
 struct_argpasser.seconds =  (unsigned long) atof(argv[2]);                                     /*Maximum amount of seconds the thread should run.*/
 struct_argpasser.busy = &busy;                                           /*Pointer to the busy variable.*/
 struct_argpasser.iteration = &iteration;                                 /*Pointer to the iteration variable.*/
 struct_argpasser.max_iterations = (unsigned long) atof(argv[1]);          /*Maximum amount of iterations the thread should run.*/
 pthread_attr_init(&thread_attributes);                                   /*Initialise the thread attributes with default settings.*/
 pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_JOINABLE);/*Explicitly state in the thread attributes, that the thread should be joinable.*/
 returncode = pthread_create(&pth_calculator,&thread_attributes,(void *) &calculatepi,&struct_argpasser);/*Creat the thread that calculates π.*/
 pthread_attr_destroy(&thread_attributes);                                /*Clean up the thread attributes (They are no longer needed).*/
 if (returncode)                                                          /*Returncode is not zero, so something went wrong while trying to create the thread.*/
 {
  printf("ERROR: The return code from pthread_create() is %d.\n", returncode);/*Notify the user of the error.*/
  exit(-1);                                                               /*Return with error status.*/
 }

printf("Max iteration: %e\n", (double) struct_argpasser.max_iterations);

 while(busy)                                                              /*Check whether the calculation thread is still running.*/
 {
  /* Significand precision of float is 52 bits 
   * Assume rounding of errors for the 65-52=13 remaining long double bits
   */
  printf("Pi: %1.51f\n", (double) pi);                                /*Print π*/
  sleep(1);                                                          /*Print the newline character.*/
 }
 
 long status;                                                             /*The variable that will hold the pthread_join status.*/
 returncode = pthread_join(pth_calculator,(void *) &status );                       /*Wait for the calculation thread to exit*/
 if (returncode)                                                          /*Returncode is not zero, so something went wrong while trying to create the thread.*/
 {
  printf("ERROR: The return code from pthread_join() is %d.\n", returncode);/*Notify the user of the error.*/
  exit(-1);                                                               /*Return with error status.*/
 }
 printf("Joined with calculation thread with status: %ld\n",status);        /*Alert the user to the status of the join with the calculation thread.*/
 
 printf("Pi: %1.51f\n", (double) pi);                                                 /*Print π */
 printf("Error calculating pi:\n %1.51f.", (double) (real_pi-pi) );                                                 /*Print error */
 puts("\n Exiting...");                                                   /*Print the newline character.*/
 pthread_exit(NULL);                                                      /*Taken from an example at https://computing.llnl.gov/tutorials/pthreads/ Not sure what it does.*/
 exit(0);                                                                 /*Exit correctly (in case the previous line didn't do it).*/
}
