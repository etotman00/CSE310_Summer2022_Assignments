#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996) // Disable warnings

// Account structure
struct account 
{
	char name[200];
	int accNum;
	int accBal;
};


const int accLimit = 800; // Number of accounts
int size = 0;

struct account** records;
struct account* dummy; // Dummy structure

// Insert account into hash 
void insertAccount(char* name, int accNum, int accBal) 
{
	struct account* temp = (struct account*)malloc(sizeof(struct account));
	
	strcpy(temp->name, name);
	temp->accNum = accNum;
	temp->accBal = accBal;

	int hashIndexAcc = accNum % accLimit;

	// Find the next free space in the hashtable
	while (records[hashIndexAcc] != NULL
		&& records[hashIndexAcc]->accNum != accNum
		&& records[hashIndexAcc]->accNum != -1) 
	{
		hashIndexAcc++;
		hashIndexAcc %= accLimit;
	}

	if (records[hashIndexAcc] == NULL
		|| records[hashIndexAcc]->accNum == -1)
		size++;

	records[hashIndexAcc] = temp;
}

// Search account by account no.
int searchAccount(int accNum) 
{
	int hashIndexAcc = accNum % accLimit;

	int count = 0;

	while (records[hashIndexAcc] != NULL) 
	{
		int count = 0;

		if (count++ > accLimit)
			break;

		// If account is found 
		if (records[hashIndexAcc]->accNum == accNum)
			printf("Name: %s\n", records[hashIndexAcc]->name);
			printf("Account No.: %d\n", records[hashIndexAcc]->accNum);
			printf("Account Balance: %f\n", records[hashIndexAcc]->accBal);
			return (records[hashIndexAcc]->accNum);

		hashIndexAcc++;
		hashIndexAcc %= accLimit;
	}
	// Otherwise, if not found
	printf("\nAccount not found!");
	return -1;
}

// Main driver
int main() 
{
	int n = 0, choice, accNum, accBal;
	char name[200];
	
	records = (struct account*)calloc(n, sizeof(struct account));

	while (1)
	{
		printf("\n------------------------------");
		printf("\nWelcome to the Sun Devil Bank!");
		printf("\n------------------------------");
		printf("\n1. Insert account");
		printf("\n2. Search account");
		printf("\n------------------------------");
		printf("\nEnter your option: ");

		scanf("%d", &choice);

		switch (choice) 
		{
		// Insert account
		case 1:
			getchar();
			printf("\nEnter your name: ");
			fgets(name, 200, stdin);
			name[strlen(name) - 1] = '\0';

			printf("\nEnter your Account No.: ");
			scanf("%d", &accNum);

			printf("\nEnter your Account Balance: ");
			scanf("%f", &accBal);

			insertAccount(name, accNum, accBal);
			break;

		// Search account
		case 2:
			printf("\nEnter account no. to search: ");
			scanf("%d", &accNum);
			searchAccount(accNum);
			break;
		
		default:
			printf("\nOut of range!");
		}
	}

	return 0;
}
