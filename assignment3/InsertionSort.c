#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* arr, int n);

int main() {
  int n, *arr, i;

  printf("Enter n: ");
  scanf("%d", &n);

  arr = (int*) malloc(sizeof(int) * n);
  printf("Enter %d numbers: ", n);
  for(i=0;i<n;i++)
    scanf("%d", arr+i);

  insertion_sort(arr, n);

  printf("Sorted array: ");
  for(i=0;i<n;++i) {
    printf("%d\t", arr[i]);
  }
  printf("\n");

  return 0;
}

void insertion_sort(int* arr, int n) {
  int i=0;
  int current_element;
  for(i=1;i<n;i++) {
    current_element = arr[i];
    int j=i;
    while (j > 0 && arr[j-1] > current_element) {
      arr[j] = arr[j-1];
      --j;
    }
    arr[j] = current_element;
  }
}