/* Compile with gcc -Wall -O3 -o as1_t2 as1_t2.c dummysort.c
   Then, start ./as1_t2
*/
#include "as1_t2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/** Dummy implementation for msort -- remove!
void msort(task_t** tasks, int count){
	qsort(tasks, count, sizeof(task_t*), qcomp);
}
*
*/

void merge(task_t** left, task_t** right, int leftsize, int rightsize)
{	
	task_t ** tmp_left, ** tmp_right;
	
	/* Allocate memory for a temporary left and right part of the task_t* pointers */
	tmp_left = (task_t**) malloc( leftsize * sizeof(task_t*) );
	tmp_right = (task_t**) malloc( rightsize * sizeof(task_t*) );
	
	/* Copy the unsorted pointers to the newly allocated memory */
	memcpy( tmp_left, left, leftsize * sizeof(task_t*) );
	memcpy( tmp_right, right, rightsize * sizeof(task_t*) );
	
	/* index of left and right part within task pointers array */
	int left_index=0, right_index=0;
	
	while( left_index<leftsize || right_index<rightsize)
	{
		if(left_index<leftsize && right_index<rightsize) 
		{
			if( tmp_left[left_index]->id <= tmp_right[right_index]->id )
			{
				/* append first(left) to result */
				*left = tmp_left[left_index];
				
				left_index++;
			}
			else
			{
				/* append first(right) to result */
				*left = tmp_right[right_index];
				
				right_index++;
			}
		}
		else if (left_index < leftsize)
		{
			/* append first(left) to result */
			*left = tmp_left[left_index];
			
			left_index++;
		}
		else if (right_index < rightsize)
		{
			/* append first(right) to result */
			*left = tmp_right[right_index];
			
			right_index++;
		}
		/* increment left point, which indicates the complete result */
		left++;
	}
	
	/* free the temporary memory blocks */
	free(tmp_left);
	free(tmp_right);
}



void msort(task_t** tasks, int count)
{
	int middle;
	task_t** right;
	
    if (count <= 1)
    {
		/* Do nothing, the tasks are alreay sorted */
        return;
    }
    
    middle = count / 2;
    right = tasks + middle;

    /* Mergesort the left part */
    msort(tasks, middle);
    
    /* Mergesort the right part */
    msort(right, count-middle);
    
    /* Merge the left and the right parts, which are already sorted */
    merge(tasks, right, middle, count-middle);
}
