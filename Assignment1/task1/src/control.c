#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "calculator.h"

/*Struct that passes arguments through pthread_create*/
struct argumentpasser
{
 char* pi;
 long  seconds;
 char* busy;
 long* iteration;
 long  max_iterations;
};

char* pi;                                                                 /*Character array that contains the digits of π*/
char busy;                                                                /*Set to one by the control thread before it starts the calculation thread. The calculation thread should set this to zero to signal the control thread that it has finished its calculations.*/
long iteration;                                                           /*Set by the control thread to publish how far it has calculated π.*/
struct argumentpasser struct_argpasser;                                   /*Initialise the argument passing struct as a global variable.*/

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
 pi = malloc((/*sizeof char*/ 8) * *argv[0]/2 + 1);                       /*Allocate enough room to hold the maximum number of digits of π that we will calculate.*/
 if (pi == NULL)                                                          /*Malloc returned null implies that not enough room could be allocated. This will occur if someone requests to calculate π to a ridiculously huge precision.*/
 {
  puts("ERROR: Out of memory.");                                          /*Notifiy the user that not enough memory is available.*/
  exit(-1);                                                               /*Exit with error status.*/
 }
 int returncode;                                                          /*Return code for pthread_create. */
 pthread_t       pth_calculator;                                          /*The pthread that will run the calculation.*/
 pthread_attr_t  thread_attributes;                                       /*The attributes for the abovementioned pthread.*/
 busy = 1;                                                                /*Set busy to 1 MUST occur before pthread_create is called.*/
 struct_argpasser.pi = pi;                                                /*Pointer to pi in the struct.*/
 struct_argpasser.seconds = *argv[2];                                     /*Maximum amount of seconds the thread should run.*/
 struct_argpasser.busy = &busy;                                           /*Pointer to the busy variable.*/
 struct_argpasser.iteration = &iteration;                                 /*Pointer to the iteration variable.*/
 struct_argpasser.max_iterations = *argv[1];                              /*Maximum amount of iterations the thread should run.*/
 pthread_attr_init(&thread_attributes);                                   /*Initialise the thread attributes with default settings.*/
 pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_JOINABLE);/*Explicitly state in the thread attributes, that the thread should be joinable.*/
 returncode = pthread_create(&pth_calculator,&thread_attributes,&calculatepi,&struct_argpasser);/*Creat the thread that calculates π.*/
 pthread_attr_destroy(&thread_attributes);                                /*Clean up the thread attributes (They are no longer needed).*/
 if (returncode)                                                          /*Returncode is not zero, so something went wrong while trying to create the thread.*/
 {
  printf("ERROR: The return code from pthread_create() is %d.\n", returncode);/*Notify the user of the error.*/
  exit(-1);                                                               /*Return with error status.*/
 }
 while(busy)                                                              /*Check whether the calculation thread is still running.*/
 {
  int i;                                                                  /*Counter variable*/
  printf("Pi: %x.",pi[0]);                                                /*Print the first digit of π and the separator.*/
  for (i = 1; i < iteration; i++)                                         /*Loop through the digits stored in the array.*/
  {
   printf("%x",pi[i]);                                                    /*Print π per hexadecimal digit.*/
  }
  puts("");     
  sleep(1);                                                          /*Print the newline character.*/
 }
 long status;                                                             /*The variable that will hold the pthread_join status.*/
 returncode = pthread_join(pth_calculator,&status);                       /*Wait for the calculation thread to exit*/
 if (returncode)                                                          /*Returncode is not zero, so something went wrong while trying to create the thread.*/
 {
  printf("ERROR: The return code from pthread_join() is %d.\n", returncode);/*Notify the user of the error.*/
  exit(-1);                                                               /*Return with error status.*/
 }
 printf("Joined with calculation thread with status: %ld\n",status);        /*Alert the user to the status of the join with the calculation thread.*/
 int i;                                                                   /*Counter variable*/
 printf("Pi: %x.",pi[0]);                                                 /*Print the first digit of π and the separator.*/
 for (i = 1; i < iteration; i++)                                          /*Loop through the digits stored in the array.*/
  printf("%x",pi[i]);                                                     /*Print π per hexadecimal digit.*/
 puts("\n Exiting...");                                                   /*Print the newline character.*/
 free(pi);                                                                /*Free memory allocated to the calculated π.*/
 pthread_exit(NULL);                                                      /*Taken from an example at https://computing.llnl.gov/tutorials/pthreads/ Not sure what it does.*/
 exit(0);                                                                 /*Exit correctly (in case the previous line didn't do it).*/
}
