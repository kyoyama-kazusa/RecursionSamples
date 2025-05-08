#pragma once

#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *, int, int);
int partition(int *, int, int);
void swap(int *__restrict, int *__restrict);

void entry(void) {
	int array[9] = { 3, 8, 1, 6, 5, 4, 7, 2, 9 };
	print_array(array, 9);

	quick_sort(array, 0, 8);

	print_array(array, 9);
}

void quick_sort(int *array, int left, int right) {
	if (left < right) {
		int pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

int partition(int *array, int left, int right) {
	int pivot = array[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (array[j] < pivot) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[right]);
	return i + 1;
}

void swap(int *__restrict a, int *__restrict b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
