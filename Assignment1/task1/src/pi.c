#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pi.h"

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
long double pi_iteration(long* k)
{
	long double dbl_k = (long double) *k;
	long double tmp =  8 / (     \
							  (4*dbl_k + 1) \
							* (4*dbl_k + 3) \
						);
						printf("term: %f\n", (double) tmp);
	return tmp;
}


/*
 * The actual pi calculation takes place according to:
 *  
 *  http://en.wikipedia.org/wiki/Leibniz_formula_for_pi
 * 
 *  
 */
void pi_leibniz(struct argumentpasser* mainArgs)
{
	long double tmp=0;
	char busy = 0;
	
	printf("\n\n");
	
	while( *(mainArgs->iteration) <= mainArgs->max_iterations) /* && time constraint */
	{
		/* store n-th iteration in array */
		tmp = tmp + pi_iteration(mainArgs->iteration);
		
		/* increment the current iteration*/
		*(mainArgs->iteration)++;
	}
	printf("%1.80f\n\n", (double) tmp);
	
	/* Indicate to main that the pi calculation is ready */
	mainArgs->busy = &busy;
}
