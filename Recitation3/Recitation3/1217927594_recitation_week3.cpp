#include <iostream>
#include <stdio.h>
#pragma warning(disable: 4996) // Disable warnings

using namespace std;

// Class node for priority queue
class Node 
{
	public:
		string plane_name;
		int wait_time;
		Node* next;
		// 'n' is name and 'w' is wait time 
		Node(string n, int w)
		{
			plane_name = n;
			wait_time = w;
			next = NULL;
		}
};

// Insert a node into the queue (add request)
Node* Insert(Node* head, string plane_name, int wait_time)
{
	Node* temp = new Node(plane_name, wait_time);

	if (head == NULL || head->wait_time>wait_time) 
	{
		temp->next = head;
		head = temp;
	}
	else 
	{
		Node* p = head;
		while (p->next != NULL) 
		{
			if (p->next->wait_time>wait_time) 
			{
				temp->next = p->next;
				p->next = temp;
				break;
			}
			p = p->next;
		}
		if (p->next == NULL)
		{
			p->next = temp;
		}
	}
	return head;
}

// Remove the node from the queue
Node* remove(Node* head) 
{
	if (head == NULL)
		return NULL;

	string plane_name = head->plane_name;
	int wait_time = head->wait_time;

	// Display plane name and wait time
	cout << plane_name << " with wait time " << wait_time << " landed" << endl;

	head = head->next;
	return head;
}

// Print the queue (display all landing requests)
void print(Node* head)
{
	if (head == NULL)
		return;
	Node* temp = head;

	cout << "All the landing requests: " << endl;

	while (temp != NULL) 
	{
		cout << temp->plane_name << " with waiting time " << temp->wait_time << endl;
		temp = temp->next;
	}
}

// Main driver 
int main()
{
	Node* head = NULL;
	
	cout << "\tWelcome to the Plane Landing System" << endl;

	int exit = 0;
	while(1) 
	{
		// Following options available
		cout << "\n1. Make a landing request" << endl;
		cout << "2. Land a Plane" << endl;
		cout << "3. List all the landing requests" << endl;
		cout << "4. Exit\n" << endl;
		cout << "Select your option: ";
		
		int i;
		cin >> i;
		string plane_name;
		int wait_time;

		switch (i)
		{
			// Make a landing request
			case 1:
				cout << "\nEnter plane name: ";
				cin >> plane_name;

				cout << "Enter wait time before landing: ";
				cin >> wait_time;

				head = Insert(head, plane_name, wait_time);
				cout << "Successfully created landing request!" << endl;
				break;
			
			// Land a Plane
			case 2:
				head = remove(head);
				break;

			// List all landing requests
			case 3:
				print(head);
				break;

			// Exit
			case 4:
				exit = 1;
				cout << "Goodbye!" << endl;
				break;

			// Invalid choice
			default:
				cout << "Out of range!" << endl;
				break;
		}
		if (exit == 1)
			break;
	}
	return 0;
}