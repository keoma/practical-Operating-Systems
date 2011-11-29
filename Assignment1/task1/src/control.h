
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

int main(int argc, char* argv[]);                                         /*main function*/

