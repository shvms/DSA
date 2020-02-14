#include <stdio.h>
#include <string.h>

#define RECORD_SIZE 100
#define STR_SIZE 1000

struct student {
  int rollNo;
  char name[STR_SIZE];
  float marks;
};

void newRecord(struct student[RECORD_SIZE], int);
void displayRecord(struct student[RECORD_SIZE], int);
int search(struct student[RECORD_SIZE], int);
void modify(struct student[RECORD_SIZE], int);


int main() {
  struct student records[RECORD_SIZE];
  int choice, currentRecordIndex = 0, searchIndex=-1;
  
  do {
    printf("-----------------STUDENT RECORDS------------------\n");
    printf("1. Write a new record.\n");
    printf("2. Display new records.\n");
    printf("3. Search\n");
    printf("4. Modify a record\n");
    printf("5. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch(choice) {
      case 1: newRecord(records, currentRecordIndex);
              currentRecordIndex++;     // TODO: update currentRecordIndex using pointer
              break;
      case 2: displayRecord(records,currentRecordIndex); break;
      case 3: searchIndex = search(records, currentRecordIndex);
              printf("Record found at: %d\n", searchIndex);
              break;
      case 4: printf("Enter index to modify: ");
              scanf("%d", &searchIndex);
              modify(records, searchIndex); break;
      case 5: printf("Thanks for standing by!\n"); break;
      default: printf("You had to choose between 1 a5. Sigh.... you missed your only chance.\n");
    }
  } while(choice != 5);
  return 0;
}

void newRecord(struct student records[RECORD_SIZE], int currentIndex) {
  printf("Enter name: ");
  scanf(" %s", records[currentIndex].name);

  printf("Enter roll number: ");
  scanf("%d", &records[currentIndex].rollNo);

  printf("Enter percentage of marks: ");
  scanf("%f", &records[currentIndex].marks);

  printf("Data added.\n");
}

void displayRecord(struct student records[RECORD_SIZE], int currentIndex) {
  int i=0;
  for(;i<currentIndex;i++) {
    printf("\n----------------------------------------------\n");
    printf("Name: %s\n", records[i].name);
    printf("Roll number: %d\n", records[i].rollNo);
    printf("Percentage: %f\n", records[i].marks);
  }
}

int search(struct student records[RECORD_SIZE], int currentIndex) {
  int choice, i, roll;
  char name[STR_SIZE];
  
  printf("1. By name\n");
  printf("2. By roll number\n");
  scanf("%d", &choice);
  switch(choice) {
    case 1:
          printf("Enter name: ");
          scanf(" %s", name);
          for(i=0;i<currentIndex;i++) {
            if (strcmp(name, records[i].name) == 0) {
              printf("\n------RECORD FOUND------\n");
              printf("Name: %s\n", name);
              printf("Roll Number: %d\n", records[i].rollNo);
              printf("Percentage of marks: %f\n", records[i].marks);
              return i;
            }
          }
          printf("Couldn't find the record.");
          break;
    
    case 2:
          printf("Enter roll number: ");
          scanf("%d", &roll);
          for(i=0;i<currentIndex;i++) {
            if (roll == records[i].rollNo) {
              printf("\n------RECORD FOUND------\n");
              printf("Name: %s\n", records[i].name);
              printf("Roll Number: %d\n", roll);
              printf("Percentage of marks: %f\n", records[i].marks);
              return i;
            }
          }
          printf("Couldn't find the record.");
          break;
    default: printf("Invalid key.");
  }

  return -1;
}

void modify(struct student records[RECORD_SIZE], int key) {
  char choice;
  if (key == -1) {
    printf("Invalid key.\n");
    return;
  }

  printf("Name: %s", records[key].name);
  printf("\nWant to change name?(y/n) ");
  scanf(" %c", &choice);
  if (choice =='y') {
    printf("\nEnter new name: ");
    scanf(" %s", records[key].name);
  }

  printf("Roll number: %d", records[key].rollNo);
  printf("\nWant to change roll number?(y/n) ");
  scanf(" %c", &choice);
  if (choice =='y') {
    printf("Enter new roll number: ");
    scanf("%d", &records[key].rollNo);
  }

  printf("Percentage: %f", records[key].marks);
  printf("\nWant to change marks?(y/n) ");
  scanf(" %c", &choice);
  if (choice =='y') {
    printf("Enter new marks: ");
    scanf("%f", &records[key].marks);
  }
}