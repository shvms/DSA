#include <stdio.h>
#include <stdlib.h>

int binary_search(int* arr, int low, int high, int key);

int main() {
  int n, *arr, key;
  
  printf("Enter n: ");
  scanf("%d", &n);

  arr = (int*) malloc(sizeof(int) * n);
  printf("Enter %d numbers in sorted order: ", n);
  for(int i=0;i<n;i++)
    scanf("%d", arr+i);
  
  printf("Enter key to search for: ");
  scanf("%d", &key);

  int res = binary_search(arr, 0, n-1, key);
  if (res == -1)
    printf("Couldn't find the item.\n");
  else
    printf("Found %d at %d.\n", key, res);
  return 0;
}

int binary_search(int* arr, int low, int high, int key) {
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] == key)
      return mid;
    else if (arr[mid] > key)
      high = mid-1;
    else
      low = mid+1;
  }
  return -1;
}