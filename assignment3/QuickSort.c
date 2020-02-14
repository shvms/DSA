#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int* arr, int low, int high);
int partition(int* arr, int low, int high, int index);

int main() {
  int n, *arr, i;

  printf("Enter n: ");
  scanf("%d", &n);

  arr = (int*) malloc(sizeof(int) * n);
  printf("Enter %d numbers: ", n);
  for(i=0;i<n;i++)
    scanf("%d", arr+i);

  srand(time(NULL));            // seeding random generator
  quicksort(arr, 0, n-1);

  printf("Sorted array: ");
  for(int i=0;i<n;++i) {
    printf("%d\t", arr[i]);
  }
  printf("\n");

  return 0;
}

void swap(int* a1, int* a2) {
  int temp = *a1;
  *a1 = *a2;
  *a2 = temp;
}

/*
 * random index inclusive of low & high
 */
int getRandomIndex(int low, int high) {
  int index = rand() % (high - low + 1);
  return index + low;
}

int partition(int* arr, int low, int high, int index) {
  // swapping the index with first element, i.e., low
  swap(arr+low, arr+index);

  /**
   * i traverses through the array. [low, high]
   * j tracks the first element greater the pivot
   */
  int i, j, pivot = arr[low];
  for(i=low+1,j=low+1;i<=high;++i) {
    if (arr[i] < pivot) {
      swap(arr+i, arr+j);
      ++j;
    }
  }

  // swapping the pivot (first) with (j-1)
  swap(arr+low, arr+(j-1));

  return j-1;
}

void quicksort(int* arr, int low, int high) {
  if (high - low + 1 > 1) {
    int pivot_index = getRandomIndex(low, high);
    pivot_index = partition(arr, low, high, pivot_index); // pivot index updated
    quicksort(arr, low, pivot_index-1);
    quicksort(arr, pivot_index+1, high);
  }
}