/* This file is prepared for the course Operating Systems/Besturingssystemen, University of Twente, 2011. Students: you may modify this file during development of your solution (e.g. for debugging purposes), BUT you must eventually hand in a WORKING solution with this file UNMODIFIED. */

#include "as1_t2.h"
#include <stdlib.h>
#include <string.h>

unsigned long* makeRandomIds(int count){
	int i;
	unsigned long* result = malloc(sizeof(unsigned long) * count);
	if (NULL == result) return NULL;
	
	for (i=0; i<count; ++i){
		result[i] = random() % 128;
		//printf("%d :: %lu\n", i, result[i]);
	}
	
	return result;
}

/** Returns a pointer to an array of newly created tasks or NULL if it failed.
 * @param taskIds The ids for the to-be-created task_ts.
 * @param count The number of random tasks to be made.
 * @return task_t** Array of pointers to new task_ts.
 * @requires count != NULL
 */
task_t** makeTasks(unsigned long taskIds[], int count){
	task_t** tasks;
	int i;

	/* Allocate memory or return NULL. */
	tasks = (task_t**) malloc(sizeof(task_t*) * count);
	if (NULL == tasks) return NULL;
	
	/* Give tasks an id */
	for (i=0; i<count; ++i){
		tasks[i] = (task_t*) malloc(sizeof(task_t));
		//memset(tasks[i], 0x0, sizeof(task_t));
		tasks[i]->id = taskIds[i];
		//printf("%d :: %lu\n", i, tasks[i]->id);
	}
	
	return tasks;
}


#ifdef UNIT_TESTS
#include <stdio.h>
#include <assert.h>

/** The test program */
int main(int argc, char *argv[]){
	printf("= as1_t2 =\n");
	printf("This unit test program is provided for Assignment 1, Task 2 of the course Operating Systems, University of Twente, 2011.\n\n");
	printf("Your solution will be tested on a number of points. Afterwards, \"[End of Test]\" will be shown. IF this is not so, the program crashed and you're not done yet.\n");
	printf("Please note: this program may detect some flaws, but may not detect all of them. Do *not* assume correctness of your solution on passing this test alone.\n\n");

	runAllTests();
	return 0;
}

/** Run all tests, in a predefined order. */
void runAllTests(void){
	printf("[Begin of Test]\n");
	testSortEmpty();
	testSortOne();
	testSortEvenAmount();
	testSortOddAmount();
	testSortBinaryPow();
	testSortNonBinaryPow();
	testSortOrdered();
	testSortInversed();
	testSortDuplicates();
	testSortRandom();
	testSortRandomLarge();
	printf("[End of Test]\n");
}

/** Comparison function for reference qsort. */
int qcomp( const void * elem1, const void * elem2 ){
	int result;
	task_t** t1 = (task_t**) elem1;
	task_t** t2 = (task_t**) elem2;
	unsigned long id1 = t1[0]->id;
	unsigned long id2 = t2[0]->id;
	
	if (id1 < id2) result = -1;
	else if (id1 == id2) result = 0;
	else result = 1;

	return result;
}

/** Creates a task list for the specified task ids, sorts them and tests the result. */
void sortTasksWithIds(unsigned long refTaskIds[], int count){
	int i;
	
	/* Arrange */
	task_t** reference = makeTasks(refTaskIds, count);
	if (NULL == reference) return;
	
	/* Act & Assert */
	sortTasks(reference, count);
	
	/* Clean-up */
	for(i=0; i<count; ++i){
		free(reference[i]);
	}
	free(reference);
}

/** Sorts the specified task list and tests the result. */
void sortTasks(task_t** reference, int count){
	int i;
	int faults = 0;
	const size_t size = sizeof(task_t*) * count;
	
	if (NULL == reference) return;
	
	/* Arrange expected */
	task_t** expected = (task_t**) malloc(size);
	if (NULL == expected) return;
	memcpy(expected, reference, size);
	
	/* Arrange actual */
	task_t** actual = (task_t**) malloc(size);
	if (NULL == actual) return;
	memcpy(actual, reference, size);
	
	/* Act */
	qsort(expected, count, sizeof(task_t*), qcomp);
	msort(actual, count);
	
	/* Assert */
	assert(expected != NULL);
	assert(actual != NULL);
	//printf("%3s :: %5s | %5s | %5s\n","#","[exp]","[act]","[ref]");
	for(i=0; i<count; ++i){
		//printf("%3d :: %5lu | %5lu | %5lu\n", i, expected[i]->id, actual[i]->id, reference[i]->id);
		if (expected[i]->id != actual[i]->id) faults++;
	}
	assert(0 == faults);
	
	/* Clean-up */
	free(expected);
	free(actual);
}

void testSortNull(void){
	printf(" => testSortNull\n");
	
	sortTasks(NULL, 999);
}

void testSortEmpty(void){
	printf(" => testSortEmpty\n");

	int count = 0;
	unsigned long refTaskIds[] = { };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortOne(void){
	printf(" => testSortOne\n");
	
	int count = 1;
	unsigned long refTaskIds[] = { 42 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortEvenAmount(void){
	printf(" => testSortEvenAmount\n");

	int count = 2;
	unsigned long refTaskIds[] = { 48, 42 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortOddAmount(void){
	printf(" => testSortOddAmount\n");

	int count = 3;
	unsigned long refTaskIds[] = { 48, 42, 38 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortBinaryPow(void){
	printf(" => testSortBinaryPow\n");

	int count = 4;
	unsigned long refTaskIds[] = { 48, 42, 38, 100 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortNonBinaryPow(void){
	printf(" => testSortNonBinaryPow\n");

	int count = 5;
	unsigned long refTaskIds[] = { 48, 42, 38, 100, 1 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortOrdered(void){
	printf(" => testSortOrdered\n");

	int count = 6;
	unsigned long refTaskIds[] = { 1, 4, 9, 16, 25, 36 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortInversed(void){
	printf(" => testSortInversed\n");

	int count = 6;
	unsigned long refTaskIds[] = { 36, 25, 16, 9, 4, 1 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortDuplicates(void){
	printf(" => testSortDuplicates\n");

	int count = 8;
	unsigned long refTaskIds[] = { 99, 12, -12, 0, 0, 12, 1, -1 };
	
	sortTasksWithIds(refTaskIds, count);
}

void testSortRandom(void){
	printf(" => testSortRandom\n");

	int count = 8;
	unsigned long* refTaskIds = makeRandomIds(count);
	
	sortTasksWithIds(refTaskIds, count);
	
	free(refTaskIds);
}

void testSortRandomLarge(void){
	printf(" => testSortRandomLarge\n");

	int count = 1024*1024;
	unsigned long* refTaskIds = makeRandomIds(count);
	
	sortTasksWithIds(refTaskIds, count);
	
	free(refTaskIds);
}
#endif
