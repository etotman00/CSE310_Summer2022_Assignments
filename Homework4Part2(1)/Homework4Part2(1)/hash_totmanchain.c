#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996) // Disable warnings

struct hash* hashTable = NULL; // Hash table structure
const int accLimit = 800; // Number of accounts (buckets)

// The node structure for the account
struct node 
{
	char name[200];
	int accNum;
	double accBal;
	struct node* next;
};

// Head and count
struct hash 
{
	struct node* head;
	int count;
};

struct node* createAccountNode(char* name, int accNum, double accBal)
{
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));

	strcpy(newnode->name, name);
	newnode->accNum;
	newnode->accBal;
	newnode->next = NULL;
	return newnode;
}

// Insert account into hash with account number
void insertAccount(char* name, int accNum, double accBal)
{
	int hashIndexAccNum = accNum % accLimit;
	
	struct node* newnode = createAccountNode(name, accNum, accBal);

	if (!hashTable[hashIndexAccNum].head) // If table lacks head
	{
		hashTable[hashIndexAccNum].head = newnode;
		hashTable[hashIndexAccNum].count = 1;
		return;
	}
	newnode->next = (hashTable[hashIndexAccNum].head); 
	hashTable[hashIndexAccNum].head = newnode;
	hashTable[hashIndexAccNum].count++;
	return;
}

// Delete account by entering account number
void deleteAccount(int accNum) 
{
	int hashIndexAccNum = accNum % accLimit, flag = 0;
	
	struct node* temp, *myNode;
	myNode = hashTable[hashIndexAccNum].head;

	if (!myNode) // If account is not present 
	{
		printf("Account not found!\n");
		return;
	}
	
	temp = myNode;
	while (myNode != NULL) 
	{
		// If node/record is found
		if (myNode->accNum == accNum) 
		{
			flag = 1;
			if (myNode == hashTable[hashIndexAccNum].head)
				hashTable[hashIndexAccNum].head = myNode->next;
			else
				temp->next = myNode->next;

			hashTable[hashIndexAccNum].count--;
			free(myNode);
			break;
		}
		temp = myNode;
		myNode = myNode->next;
	}

	if (flag)
		printf("Account successfuly deleted!\n");
	else
		printf("Account not found!\n");
	return;
}

// Search account by entering account number
void searchAccount(int accNum) 
{
	int hashIndexAccNum = accNum % accLimit, flag = 0;
	
	struct node* myNode;
	myNode = hashTable[hashIndexAccNum].head;

	if (!myNode) // If account is not present
	{
		printf("Account not found!\n");
		return;
	}

	while (myNode != NULL) // If present, display account information
	{
		if (myNode->accNum == accNum) 
		{
			printf("Name: %s\n", myNode->name);
			printf("Account No.: %d\n", myNode->accNum);
			printf("Account Balance: %f\n", myNode->accBal);
			flag = 1;
			break;
		}
		myNode = myNode->next;
	}

	if (!flag)
		printf("Account not found!\n");
	return;
}


// Main driver
int main() 
{
	int n = 1000, choice, accNum, accBal;
	char name[200];
	
	hashTable = (struct hash*)calloc(n, sizeof(struct hash));
	
	while (1) 
	{
		printf("\n------------------------------");
		printf("\nWelcome to the Sun Devil Bank!");
		printf("\n------------------------------");
		printf("\n1. Insert account");
		printf("\n2. Delete account");
		printf("\n3. Search account");
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
	
			// Delete account
			case 2:
				printf("\nEnter account no. for deletion of account: ");
				scanf("%d", &accNum);
				deleteAccount(accNum);
				break;

			// Search account
			case 3:
				printf("\nEnter account no. to search: ");
				scanf("%d", &accNum);
				searchAccount(accNum);
				break;

			default:
				exit(0);

		} 
	}

	return 0;
}