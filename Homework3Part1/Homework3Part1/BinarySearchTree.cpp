#include <iostream>
#include <cstdlib>
#pragma warning(disable: 4996) // Disable warnings

using namespace std;

class BinarySearchTree
{
private:
	class node
	{
	public:
		node* left;
		node* right;
		node* parent;
		int key;
		string data;
	};


public:
	node* root;
	BinarySearchTree()
	{
		root = NULL;
	}
	bool isEmpty() const { return root == NULL; }
	void INORDER_TREE_WALK(node*);
	void TREE_INSERT(int);

	// Create a copy of the tree and get prefix expression of an expression tree
	void pre_order_Traversal(node* i)
	{
		if (i != NULL)
		{
			cout << " " << i->key << " ";

			if (i->left)
				pre_order_Traversal(i->left);
			if (i->right)
				pre_order_Traversal(i->right);
		}
	}

	// Delete a tree and get the postfix expression of an expression tree
	void post_order_Traversal(node* i)
	{
		if (i != NULL) 
		{
			if (i->left)
				post_order_Traversal(i->left);
			if (i->right)
				post_order_Traversal(i->right);

			cout << " " << i->key << " ";
		}
	}

	// Find the maximum value in the tree
	int find_max_Val(node* i) 
	{
		// If there is no tree present
		if (i == NULL)
		{
			cout << "Tree: empty." << endl;
			return 0;
		}

		// A tree exists with a maximum value
		while (i->right != NULL) 
		{
			i = i->right;
		}

		cout << "Maximum value existing in the tree is: " << i->key;

		return i->key;
	}

	// Remove maximum value in the tree
	void rem_max_Val(node* i) 
	{
		int sel = find_max_Val(i);

		remove(sel);
	}

	// Find the successor to a node in the tree
	void the_successor(int x) 
	{
		node* i = root;

		while (i != NULL) 
		{
			if (x < i->key)
			{
				i = i->left;
			}
			else if (x > i->key)
			{
				i = i->right;
			}
			else 
			{
				break;
			}
		}
		
		// If key is not found
		if (i == NULL) 
		{
			cout << "Not found!" << endl;
		}

		// If key is found
		if (i->right != NULL) 
		{
			node* sel = i->right;

			while (sel->left != NULL) 
			{
				sel = sel->left;
			}

			cout << "The node successor is: " << sel->key << endl;
		}
		else // Otherwise a parent-node's successor is found
		{
			node* prog = i->parent;
			node* sel = i;
			
			while (prog != NULL && sel == prog->right) 
			{
				sel = prog;
				prog = prog->parent;
			}

			if (prog != NULL) 
			{
				cout << "The node successor is: " << prog->key << endl;
			}
			else
			{
				cout << "The node lacks a successor!" << endl;
			}
		}
	}

	// Remove node from the tree
	void remove(int x) 
	{
		node* i = root;

		while (i != NULL) 
		{
			if (x < i->key) 
			{
				i = i->left;
			}
			else if (x > i->key) 
			{
				i = i->right;
			}
			else 
			{
				break;
			}
		}

		// If key is not found
		if (i == NULL)
		{
			cout << "Not found!" << endl;
			return;
		}
		
		// If key is found in either the left or right leaves of the tree
		if (i->right != NULL) 
		{
			node* tmp = i->right;
			
			while (tmp->left != NULL) 
			{
				tmp = tmp->left;
			}

			i->key = tmp->key;

			if (tmp->parent == i) 
			{
				i->right = tmp->right;
				
				if (tmp->right != NULL) 
				{
					tmp->right->parent = tmp->parent;
				}
			}
			else 
			{
				tmp->parent->left = tmp->right;
				
				if (tmp->right != NULL) 
				{
					tmp->right->parent = tmp->parent;
				}
			}
			free(tmp);
		}
		else if (i->left != NULL) 
		{
			node* tmp = i->left;

			while (tmp->right != NULL) 
			{
				tmp = tmp->right;
			}

			i->key = tmp->key;

			if (tmp->parent == i) 
			{
				i->left = tmp->left;

				if (tmp->left != NULL) 
				{
					tmp->left->parent = tmp->parent;
				}
			}
			else 
			{
				tmp->parent->right = tmp->left;

				if (tmp->left != NULL) 
				{
					tmp->left->parent = tmp->parent;
				}
			}
			free(tmp);
		}
		else 
		{
			if (i == root) 
			{
				root = NULL;
				return;
			}

			if (i->key > i->parent->key) 
			{
				i->parent->right = NULL;
			}
			else 
			{
				i->parent->left = NULL;
			}
		}
	}
};

void BinarySearchTree::TREE_INSERT(int d)
{
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->key = d;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;

	while (x != NULL)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else if (z->key > x->key)
			x = x->right;
		else
		{
			cout << " Already exists in tree!" << endl;
			return;
		}
	}

	z->parent = y;
	if (y == NULL)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

void BinarySearchTree::INORDER_TREE_WALK(node* x)
{
	if (x != NULL)
	{
		if (x->left) INORDER_TREE_WALK(x->left);
		cout << " " << x->key << " ";
		if (x->right) INORDER_TREE_WALK(x->right);
	}
}

// Main driver
int main()
{
	BinarySearchTree bst;
	int choice, key;
	while (true)
	{
		cout << endl;
		cout << " --------------------------" << endl;
		cout << " Binary Search Tree Example" << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insert " << endl;
		cout << " 2. Pre-Order Traversal " << endl;
		cout << " 3. Post-Order Traversal " << endl;
		cout << " 4. In-Order Traversal " << endl;
		cout << " 5. Find Max " << endl;
		cout << " 6. Remove Max " << endl;
		cout << " 7. The Successor " << endl;
		cout << " 8. Delete " << endl;
		cout << " 9. Quit " << endl;
		cout << " ----------------------------- " << endl;
		cout << " Select the following options: ";
		cin >> choice;
		switch (choice)
		{

		// 1. Insert
		case 1: 
			cout << " Enter key (int value) to be inserted : ";
			cin >> key;
			bst.TREE_INSERT(key);
			break;
		
		// 2. Pre-Order Traversal
		case 2: 
			cout << endl;
			cout << " Pre-Order Traversal " << endl;
			cout << " ------------------- " << endl;
			bst.pre_order_Traversal(bst.root);
			break;

		// 3. Post-Order Traversal
		case 3: 
			cout << endl;
			cout << " Post-Order Traversal " << endl;
			cout << " -------------------- " << endl;
			bst.post_order_Traversal(bst.root);
			break;

		// 4. In-Order Traversal
		case 4:
			cout << endl;
			cout << " In-Order Traversal " << endl;
			cout << " ------------------ " << endl;
			bst.INORDER_TREE_WALK(bst.root);
			break;

		// 5. Find Max
		case 5:
			bst.find_max_Val(bst.root);
			break;

		// 6. Remove Max
		case 6:
			bst.rem_max_Val(bst.root);
			break;

		// 7. The Successor
		case 7:
			cout << " Enter key to find successor: ";
			cin >> key;
			bst.the_successor(key);
			break;
		
		// 8. Delete
		case 8:
			cout << " Enter key you wish to remove: ";
			cin >> key;
			bst.remove(key);
			break;

		// 9. Quit
		case 9:
			cout << " Goodbye!" << endl;
			exit(1);
			break;

		default:
			cout << " Out of range!" << endl;
		}
	}
	return 0;
}