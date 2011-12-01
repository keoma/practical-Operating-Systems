#ifndef _AS1_T2_H
#define _AS1_T2_H
#define UNIT_TESTS

/* This file is prepared for the course Operating Systems/Besturingssystemen, University of Twente, 2011. Students: you may modify this file during development of your solution (e.g. for debugging purposes), BUT you must eventually hand in a WORKING solution with this file UNMODIFIED. */

/** The (arbitrary) structure that represenst some task that must be handled (irrelevant for this assignment). */
typedef struct task_struct {
	/* Some task id */
	unsigned long id;

	/* Some state */
	long state;

	/* Function delegate address */
	void *function;
} task_t;


/** You must implement this function. This function sorts the specified amount (count) of tasks. */
extern void msort(task_t** tasks, int count);

/** This function is provided and generates the specified amount (count) of task ids. */
unsigned long* makeRandomIds(int count);
/** This function is provided and generates the specified amount (count) of tasks with the specified ids. */
task_t** makeTasks(unsigned long taskIds[], int count);


#ifdef UNIT_TESTS
int qcomp( const void * elem1, const void * elem2 );
void sortTasksWithIds(unsigned long refTaskIds[], int count);
void sortTasks(task_t** reference, int count);

void runAllTests(void);
void testSortNull(void);
void testSortEmpty(void);
void testSortOne(void);
void testSortEvenAmount(void);
void testSortOddAmount(void);
void testSortBinaryPow(void);
void testSortNonBinaryPow(void);
void testSortOrdered(void);
void testSortInversed(void);
void testSortDuplicates(void);
void testSortRandom(void);
void testSortRandomLarge(void);

#endif /* UNIT_TESTS */

#endif /* _AS1_T2_H */

