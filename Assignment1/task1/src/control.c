#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

char* pi;
char busy;
long iteration;

struct argumentpasser
{
 char* pi;
 long  seconds;
 char* busy;
 long* iteration;
 long  max_iterations;
};

int main(int argc, char* argv[])
{
 if (argc < 2)
 {
  puts("ERROR: Please specify the desired amount of iterations and the desired maximum running time.");
  exit(-1);
 }
 if (argc > 2)
 {
  printf("WARNING: Disregarding %d trailing arguments",argc - 2);
 }
 pi = malloc((/*sizeof char*/ 8) * *argv[0]/2 + 1);
 if (pi == NULL)
 {
  puts("ERROR: Out of memory");
  exit(-1);
 }
 int returncode;
 struct argumentpasser struct_argpasser;
 pthread_t       pth_calculator;
 pthread_attr_t  thread_attributes;
 busy = 1;
 struct_argpasser.pi = pi;
 struct_argpasser.seconds = *argv[1];
 struct_argpasser.busy = &busy;
 struct_argpasser.iteration = &iteration;
 struct_argpasser.max_iterations = *argv[0];
 pthread_attr_init(&thread_attributes);
 pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_JOINABLE);
 returncode = pthread_create(&pth_calculator,&thread_attributes,maartensfunction,&struct_argpasser);
 pthread_attr_destroy(&thread_attributes);
 if (returncode)
 {
  printf("ERROR: The return code from pthread_create() is %d\n", returncode);
  exit(-1);
 }
 while(busy)
 {
  int i;
  printf("Pi: %x.",pi[0]); /*print the first digit of π and the separator.*/
  for (i = 1; i < iteration; i++)
  {
   printf("%x",pi[i]); /*Print π per hexadecimal digit.*/
  }
  printf("/n");
 }
 int status;
 pthread_join(pth_calculator,&status);
 printf("Joined with calculation thread with status: %d",status);
 free(pi);
 pthread_exit(NULL);
 exit(0);
}
