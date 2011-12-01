/* Compile with gcc -Wall -O3 -o as1_t2 as1_t2.c dummysort.c
   Then, start ./as1_t2
*/
#include "as1_t2.h"
#include <stdlib.h>

/** Dummy implementation for msort -- remove! */
void msort(task_t** tasks, int count){
	qsort(tasks, count, sizeof(task_t*), qcomp);
}

