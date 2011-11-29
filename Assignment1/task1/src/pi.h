
/*Struct that passes arguments through pthread_create*/
struct argumentpasser
{
 char* pi;
 long  seconds;
 char* busy;
 long* iteration;
 long  max_iterations;
};

long double pi_iteration(long*);

void pi_leibniz(struct argumentpasser*);
