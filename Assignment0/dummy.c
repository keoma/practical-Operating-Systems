/*
This file is an extention to libc.
It shows that it is possible to both
compile libc and extend it with an
arbitray function.
*/

#include <stdio.h>

void dummy()
{
	printf("Hello world!!!");
}
