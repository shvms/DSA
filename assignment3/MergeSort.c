#include <stdio.h>
#include <stdlib.h>

void mergesort(int* arr, int low, int high);
void combine(int* arr, int low1, int high, int low2, int high2);

int main() {
  int n, *arr, i;

  printf("Enter n: ");
  scanf("%d", &n);

  arr = (int*) malloc(sizeof(int) * n);
  printf("Enter %d numbers: ", n);
  for(i=0;i<n;i++)
    scanf("%d", arr+i);

  mergesort(arr, 0, n-1);

  printf("Sorted array: ");
  for(int i=0;i<n;++i) {
    printf("%d\t", arr[i]);
  }
  printf("\n");

  return 0;
}

void combine(int* arr, int low1, int high1, int low2, int high2) {
  int len1 = high1 - low1 + 1;
  int len2 = high2 - low2 + 1;
  int len = len1 + len2;
  int* temp = (int*) malloc(sizeof(int) * len);
  int i = low1, j = low2, k = 0;
  

  while (i <= high1 && j <= high2) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }
  
  if (i > high1) {
    for(;j<=high2;++j) { temp[k++] = arr[j]; }
  } else if (j > high2) {
    for(;i<=high1;++i) { temp[k++] = arr[i]; }
  }

  // copying back
  for(i=low1,j=0;j<len;++i,++j) {
    arr[i] = temp[j];
  }

  free(temp);
}

void mergesort(int* arr, int low, int high) {
  if (high - low + 1 > 1) {
    int mid = (low + high) / 2;
    mergesort(arr, low, mid);
    mergesort(arr, mid+1, high);
    combine(arr, low, mid, mid+1, high);
  }
}