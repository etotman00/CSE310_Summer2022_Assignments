#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996) // Disable warnings

// Minimum and Maximum for the random generation
// And constant length for array
#define MAX 1000
#define MIN 100
#define LEN 99999999

// Length for modifiable array
int len;

// Insertion Sort Algorithm
void insertionSort(double arr[], int N) 
{
	int i;
	double key;
	for (int i = 1; i < N; i++) 
	{
		key = arr[i];
		int j = i - 1;

		while (j >= 0 && key < arr[j]) 
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

// Quicksort Algorithm
void swap(double arr[], int k, int small)
{
	double temp;
	temp = arr[k];
	
	arr[k] = arr[small];
	arr[small] = temp;
}

int partition(double arr[], int low, int high) 
{
	double pivot = arr[high];
	int small = low - 1;

	for (int k = low; k < high; k++) 
	{
		if (arr[k] <= pivot) 
		{
			small++;
			swap(arr, k, small);
		}
	}

	swap(arr, high, small + 1);
	return small + 1;
}

void quickSort(double arr[], int p, int r)
{
	if (p < r)
	{
		int pos = partition(arr, p, r);
		quickSort(arr, p, pos - 1);
		quickSort(arr, pos + 1, r);
	}
}

// Merge Sort Algorithm
void merge(double arr[], int p, int q, int r)
{
	double LM[LEN];
	int lt = p, rt = r, md = q + 1, k = lt;

	while (lt <= q && md <= rt) 
	{
		if (arr[lt] <= arr[md]) 
		{
			LM[k++] = arr[lt++];
		}
		else
		{
			LM[k++] = arr[md++];
		}
	}

	while (lt <= q)
		LM[k++] = arr[lt++];

	while (md <= rt) 
	{
		LM[k++] = arr[md++];
	}

	for (int i1 = p; i1 <= r; i1++) 
	{
		arr[i1] = LM[i1];
	}
}

void mergeSort(double arr[], int p, int r)
{
	if (p < r) 	
	{
		int q = p + (r - p) / 2;
		mergeSort(arr, p, q);
		mergeSort(arr, q + 1, r);
		mergeSort(arr, p, q, r);
	}
}

// Generate a random number array
double* getRandomNum(int size) 
{
	srand(time(NULL));
	double* arr = (double*)malloc(size * sizeof(double));

	for (int i = 0; i < size; i++) 
	{
		int random = (rand() % (MAX - MIN + 1) + MIN);
		arr[i] = random;
	}
	return arr;
}

// Main driver function
int main() 
{
	/* clock_t to count the amount of seconds it takes
	   for each algorithm */
	clock_t begin, end;
	double time_spent;
	double* arr;
	int size;

	// Array sizes
	int sizes[] = { 1000, 10000, 25000, 50000, 100000, 150000, 200000 };
	printf("ArraySize InsertionSort MergeSort QuickSort\n");

	for (int i = 0; i < 7; i++) 
	{
		size = sizes[i];
		printf("%-9d", size);
		
		// Insertion
		arr = getRandomNum(size);
		begin = clock();
		insertionSort(arr, size);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf(" %-13.2lf", time_spent);

		// Merge
		len = size;
		arr = getRandomNum(size);
		begin = clock();
		mergeSort(arr, 0, size - 1);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf(" %-9.2lf", time_spent);

		// Quick
		arr = getRandomNum(size);
		begin = clock();
		quickSort(arr, 0, size - 1);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf(" %-9.2lf", time_spent);
		printf("\n");
 	}
}