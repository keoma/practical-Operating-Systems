#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pi.h"
#include <time.h>


/*
 * Long double precision:
 * http://en.wikipedia.org/wiki/Extended_precision
 * 
 * 15 bit exponent
 * 65 bit fraction 
 * 
 */
 

/*
 * Calculate the nth-iteration of Leibniz
 *  
 */

const long double pi_iteration_dividend = 8;
const long double pi_iteration_four = 4;
const long double pi_iteration_three = 3;
const long double pi_iteration_one = 1;

long double pi_iteration(unsigned long* iteration)
{
	long double four_times_k = pi_iteration_four * (long double) *iteration;
	long double divisor =  (four_times_k + pi_iteration_one) \
							* (four_times_k + pi_iteration_three);
		
	return pi_iteration_dividend/divisor;
}


/*
 * The actual pi calculation takes place according to:
 *  
 *  http://en.wikipedia.org/wiki/Leibniz_formula_for_pi
 * 
 *  
 */
void calculatepi(void* mainArgs)
{
	/* Point to struct stored in control.c */
	struct argumentpasser* struct_args = mainArgs;
	
	/* Initialize pi: */
	*(struct_args->pi) = 0;
	
	
	while( *(struct_args->iteration) <= struct_args->max_iterations)		
	{
		
		/* store n-th iteration in array */
		*(struct_args->pi) = *(struct_args->pi) + pi_iteration(struct_args->iteration);
		
		/* increment the current iteration*/
		++*struct_args->iteration;
	}
	
	/* Indicate to main that the pi calculation is ready */
	*(struct_args->busy) = 0;
}
