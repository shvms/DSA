#include <stdio.h>

#define MAX_SIZE 10

int main() {
  int arr[MAX_SIZE];
  int i=0;

  printf("Enter %d elements: ", MAX_SIZE);
  for(;i<MAX_SIZE;i++) {
                scanf("%d", arr + i);
        }

        printf("Elements with addresses:\n");
        for(i=0;i<MAX_SIZE;i++) {
                printf("Value: %d\tAddress: %p\n", *(arr+i), arr+i);
        }

        return 0;
}