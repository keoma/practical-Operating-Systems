#include <stdlib.h>
#include <stdio.h>

/* This file is prepared for the course Operating Systems/Besturingssystemen, University of Twente, 2010. Students: do not change this file for your assignment. */

int main(int argc, char *argv[]){
        printf("We will now invoke the dummy command in libc. If your implementation would print anything to the standard output, it should be printed here as well.\nThe test ends with the line \"[End of Test]\". If there is no such output, the program crashed and you're not done yet :).\n-- Your friendly BeSys instructors.\n\n[Begin of Test]\n");
        dummy();
        printf("\n[End of Test]\n");
}
