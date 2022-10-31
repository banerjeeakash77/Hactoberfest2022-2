// C++ Code for the above approach

#include <bits/stdc++.h>
using namespace std;

/* A binary tree node has data,
a pointer to left child
and a pointer to right child */
class Node {
public:
	int data;
	Node* left;
	Node* right;
};

// Function to return a new Node
Node* newNode(int data)
{
	Node* node = new Node();
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

// Function to convert bst to
// a doubly linked list
void bstTodll(Node* root, Node*& head)
{
	// if root is NULL
	if (!root)
		return;

	// Convert right subtree recursively
	bstTodll(root->right, head);

	// Update root
	root->right = head;

	// if head is not NULL
	if (head) {

		// Update left of the head
		head->left = root;
	}

	// Update head
	head = root;

	// Convert left subtree recursively
	bstTodll(root->left, head);
}

// Function to merge two sorted linked list
Node* mergeLinkedList(Node* head1, Node* head2)
{

	/*Create head and tail for result list*/
	Node* head = NULL;
	Node* tail = NULL;

	while (head1 && head2) {

		if (head1->data < head2->data) {

			if (!head)
				head = head1;
			else {

				tail->right = head1;
				head1->left = tail;
			}

			tail = head1;
			head1 = head1->right;
		}

		else {

			if (!head)
				head = head2;
			else {
				tail->right = head2;
				head2->left = tail;
			}

			tail = head2;
			head2 = head2->right;
		}
	}

	while (head1) {
		tail->right = head1;
		head1->left = tail;
		tail = head1;
		head1 = head1->right;
	}

	while (head2) {
		tail->right = head2;
		head2->left = tail;
		tail = head2;
		head2 = head2->right;
	}

	// Return the created DLL
	return head;
}

// function to convert list to bst
Node* sortedListToBST(Node*& head, int n)
{
	// if no element is left or head is null
	if (n <= 0 || !head)
		return NULL;

	// Create left part from the list recursively
	Node* left = sortedListToBST(head, n / 2);

	Node* root = head;
	root->left = left;
	head = head->right;

	// Create left part from the list recursively
	root->right = sortedListToBST(head, n - (n / 2) - 1);

	// Return the root of BST
	return root;
}

// This function merges two balanced BSTs
Node* mergeTrees(Node* root1, Node* root2, int m, int n)
{
	// Convert BSTs into sorted Doubly Linked Lists

	Node* head1 = NULL;
	bstTodll(root1, head1);
	head1->left = NULL;

	Node* head2 = NULL;
	bstTodll(root2, head2);
	head2->left = NULL;

	// Merge the two sorted lists into one
	Node* head = mergeLinkedList(head1, head2);

	// Construct a tree from the merged lists
	return sortedListToBST(head, m + n);
}

void printInorder(Node* node)
{
	// if current node is NULL
	if (!node) {
		return;
	}

	printInorder(node->left);

	// Print node of current data
	cout << node->data << " ";

	printInorder(node->right);
}

/* Driver code*/
int main()
{
	/* Create following tree as first balanced BST
	100
	/ \
	50 300
	/ \
	20 70 */

	Node* root1 = newNode(100);
	root1->left = newNode(50);
	root1->right = newNode(300);
	root1->left->left = newNode(20);
	root1->left->right = newNode(70);

	/* Create following tree as second balanced BST
			80
			/ \
		40 120
	*/
	Node* root2 = newNode(80);
	root2->left = newNode(40);
	root2->right = newNode(120);

	// Function Call
	Node* mergedTree = mergeTrees(root1, root2, 5, 3);

	cout << "Following is Inorder traversal of the merged "
			"tree \n";
	printInorder(mergedTree);

	return 0;
}

// This code is contributed by Tapesh(tapeshdua420)
