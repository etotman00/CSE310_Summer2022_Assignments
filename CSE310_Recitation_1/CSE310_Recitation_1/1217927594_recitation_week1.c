#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996) // Disable warnings

// Length of student's name
#define MAX_NAME_LENGTH 30

// Record structure
struct studentRecord
{
	char studentName[MAX_NAME_LENGTH];
	float final_average;
	struct studentRecord* next;
};

// The 'head' and 'tail' pointers
struct studentRecord* head = NULL;
struct studentRecord* tail = NULL;

// Register new student record to the list
void addRecord(char studentName_input[MAX_NAME_LENGTH], float average_input)
{
	struct studentRecord* newRecord = (struct studentRecord*)malloc(sizeof(struct studentRecord));
	
	// Copy the inputted name and average and paste them to "studentName" and "final_average"
	strcpy(newRecord->studentName, studentName_input);
	newRecord->final_average = average_input;

	newRecord->next = NULL;

	// If list is empty
	if (head == NULL)
	{
		head = newRecord;
		tail = newRecord;
	}
	else 
	{
		tail->next = newRecord;
		tail = newRecord;
	}
}

// Display all existing student records
void displayRecords() 
{
	struct studentRecord* current = head;

	// If list is empty
	if (head == NULL) 
	{
		printf("\n\tRecords Unavailable!\n\n");
		return;
	}
	printf("\n");

	while (current != NULL) 
	{
		// Prints each records by incrementation
		printf("\t%s\t%.2f\n", current->studentName, current->final_average);
		current = current->next;
	}
	printf("\n");
}

// Flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// User selects one of the following options avaibl
void executeAction(char choice)
{
	char studentName_input[MAX_NAME_LENGTH];
	float average_input;
	int count;
	switch (choice)
	{
		case '1': 
			// Add new record
			printf("\nEnter student's name and average: ");
			scanf("%s%f", studentName_input, &average_input);
			addRecord(studentName_input, average_input);
			flushStdIn();
			printf("\nRecord successfully added!\n\n");
			break;

		case '2':
			// Display records
			displayRecords();
			break;

		case '3':
			// Count existing records
			count = countRecords(head);
			printf("\n\tRecords: %d\n\n", count);
			break;

		case '4':
			// Exit program
			printf("\nGoodbye!\n");
			break;
		default:
			printf("Invalid choice! \n");
	}
}

// Count existsing records that were added to the list
int countRecords(struct studentRecord* head) 
{
	int count = 0;

	while (head != NULL) 
	{
		head = head->next;
		++count;
	}
	return count;
}

// Main driver 
int main()
{
	char choice = 'i'; // Initialized to a dummy value
	do 
	{
		printf("Welcome sir or madam!\n");
		printf("\t Please select the following options:\n");
		printf("\t 1: Add student record\n");
		printf("\t 2: Display student records\n");
		printf("\t 3: Count number of records\n");
		printf("\t 4: Exit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != '4');

	return 0;
}