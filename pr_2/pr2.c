#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int global = 0;

int global1;

#define SIZE 500000000

int main() {
	int local = 0;
	volatile int* mal = (int*)malloc(sizeof(int));
	clock_t begin;
	clock_t end;
	double time_spent;


	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		global += 1;
	}
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("data segment :%f s\n",time_spent);


	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		global1 += 1;
	}
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("BSS :%f s\n", time_spent);


	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		local += 1;
	}
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("stack :%f s\n", time_spent);


	begin = clock();
	for (int i = 0; i < SIZE; i++) {
		*mal += 1;
	}
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("heap :%f s\n", time_spent);

	free(mal);

	return 0;
}