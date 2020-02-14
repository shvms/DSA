#include <stdio.h>

void oddEvenSort(int* arr, int length);

int main(void) {
  int arr[8] = {70, 80, 40, 20, 10, 30, 60, 50};
  oddEvenSort(arr, 5);

  for(int i=0;i<8;++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}

void oddEvenSort(int* arr, int length) {
  for(int i=0;i<length-2;i+=2) {
    for(int j=i+2;j<length;j+=2) {
      if (arr[i] < arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }

  for (int i=1;i<length-2;i+=2) {
    for (int j=i+2;j<length;j+=2) {
      if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}