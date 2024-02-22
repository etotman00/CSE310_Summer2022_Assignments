#include <iostream>
#include <cstdlib>
#pragma warning(disable: 4996) // Disable warnings

using namespace std;

// Airport structure
struct airport
{
	struct airport* left;
	int landing_time;
	int flight_number;
	struct airport* right;
};

// Pre-existing functions
struct airport* check(struct airport* at, int lnd_t, int fl_num, int K);
void insert(struct airport** at, int lnd_t, int fl_num);
void list(struct airport* at);
struct airport* withdraw(struct airport* at, int lnd_t);

// Check constraints, whether BST creation is satisfactory or not
struct airport* check(struct airport* at, int lnd_t, int fl_num, int K)
{
	int tmp;
	if (at != NULL)
	{
		// If maximum value is found
		if ((at)->landing_time > lnd_t)
			tmp = (at)->landing_time- lnd_t;
		else
			tmp = lnd_t - (at)->landing_time;

		// If the constraint is satisfactory
		if (tmp - K >= 1)
		{
			check(at->left, lnd_t, fl_num, K);
			check(at->right, lnd_t, fl_num, K);
		}
		else
			return at;
	}
	return NULL;
}

// Insert a node into the tree
void insert(struct airport** at, int lnd_t, int fl_num)
{
	if (*at == NULL)
	{
		*at = new struct airport;
		(*at)->left = NULL;
		(*at)->landing_time = lnd_t;
		(*at)->flight_number = fl_num;
		(*at)->right = NULL;
	}
	else
	{
		if ((*at)->landing_time > lnd_t)
			insert(&((*at)->left), lnd_t, fl_num);
		else
			insert(&((*at)->right), lnd_t, fl_num);
	}
	return;
}

// Display values in the tree
void list(struct airport* at)
{
	// If list is not empty
	if (at != NULL)
	{
		list((at)->left);
		cout << " Flight No.: " << at->flight_number << endl;
		cout << " Landing Time: " << at->landing_time;
		list((at)->right);
	}
	// Otherwise it is empty
	else 
		cout << " \n Empty!" << endl;
		return;
}

// Find the minimum value
struct airport* find_min_Val(struct airport* at)
{
	while (at->left != NULL)
		at = at->left;
	return at;
}

// Search and withdraw a value from tree.
struct airport* withdraw(struct airport* at, int lnd_t)
{
	struct airport* tmp;
	if (at == NULL) 
		return at;
	else if 
		(lnd_t < at->landing_time) at->left = withdraw(at->left, lnd_t);
	else if 
		(lnd_t > at->landing_time) at->right = withdraw(at->right, lnd_t);
	else 
	{
		// Lacking child nodes
		if (at->left == NULL && at->right == NULL) 
		{
			delete at;
			at = NULL;
		}

		// At least one child node
		else if (at->left == NULL) 
		{
			tmp = at;
			at = at->right;
			delete tmp;
		}
		else if (at->right == NULL) 
		{
			tmp = at;
			at = at->left;
			delete tmp;
		}

		// At least two child nodes
		else 
		{
			tmp = find_min_Val(at->right);
			at->landing_time = tmp->landing_time;
			at->right = withdraw(at->right, tmp->landing_time);
		}
	}
	return at;
}

// Main driver
int main()
{
	struct airport* at;
	int K, choice, lnd_t, fl_num;
	at = NULL;
	cout << " Enter time gap: ";
	cin >> K;
	cout << endl;
	while (1)
	{
		cout << endl;
		cout << " --------------------------------------" << endl;
		cout << " Welcome to the Landing Request System!" << endl;
		cout << " --------------------------------------" << endl;
		cout << " 1. Request Landing " << endl;
		cout << " 2. Withdraw Request" << endl;
		cout << " 3. List Landing Times & Flight Numbers" << endl;
		cout << " 4. Quit" << endl;
		cout << " --------------------------------------" << endl;
		cout << " Select one of the following options: ";
		cin >> choice;
		switch (choice)
		{

		// 1. Request Landing
		case 1:
			cout << " \n Enter flight no.: ";
			cin >> fl_num;
			cout << " Enter landing time: ";
			cin >> lnd_t;
			if (at == NULL)
			{
				insert(&at, lnd_t, fl_num);
				cout << " Successfully created landing request!" << endl;
			}
			else if (check(at, lnd_t, fl_num, K) == NULL)
			{
				insert(&at, lnd_t, fl_num);
				cout << " Successfully created landing request!" << endl;
			}
			else
				cout << " Failed to request landing!" << endl;
			break;

		// 2. Withdraw Request
		case 2:
			cout << " Enter landing time: ";
			cin >> lnd_t;
			at = withdraw(at, lnd_t);
			break;

		// 3. List Landing Times & Flight Numbers
		case 3:
			list(at);
			break;

		// 4. Quit
		case 4:
			cout << " Goodbye!" << endl;
			exit(1);
			break;

		default:
			cout << " Out of Range!" << endl;
		}
	}
	return 0;
}