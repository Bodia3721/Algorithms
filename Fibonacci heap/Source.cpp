
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

// Creating a structure to represent a node in the heap
struct node {
	node* parent; 
	node* child; 
	node* left; 
	node* right; 
	int key; 
	int degree; // Degree of the node
	char mark; // Black or white mark of the node
	char c; // Flag for assisting in the Find node function
};



class FibonacciHeap {
public:
	FibonacciHeap();
	FibonacciHeap(int data);
	void insertion(int val);
	void Fibonnaci_link(node* ptr2, node* ptr1);
	void Consolidate();
	void Extract_min();
	void Cut(node* found, node* temp);
	void Cascase_cut(node* temp);
	void Decrease_key(node* found, int val);
	void Find(node* min, int old_val, int val);
	void Deletion(int val);
	void display();
	int getNodeNum() { return no_of_nodes; }
	void setNodeNum(int n) { no_of_nodes = n; }
	node*& GetMin();

public:
	node* root;
	node* min;
	int no_of_nodes;

};

FibonacciHeap::FibonacciHeap() {
	min = nullptr;
	root = new node;
	root->parent = nullptr;
	root->child = nullptr;
	root->left = nullptr;
	root->right = nullptr;
	root->key = -1;
	root->degree = 0;
	root->mark = 0;
	root->c = 0;
	this->no_of_nodes = 0;
}

FibonacciHeap::FibonacciHeap(int data) {
	min = nullptr;
	root = new node;
	root->parent = nullptr;
	root->child = nullptr;
	root->left = nullptr;
	root->right = nullptr;
	root->key = data;
	root->degree = 0;
	root->mark = 0;
	root->c = 0;
	this->no_of_nodes = 0;
}

node*& FibonacciHeap::GetMin() {
	return min;
}

// Function to insert a node in heap
void FibonacciHeap::insertion(int val)
{
	node* new_node = new node;
	new_node->key = val;
	new_node->degree = 0;
	new_node->mark = 'W';
	new_node->c = 'N';
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	if (this->min != NULL) {
		(this->min->left)->right = new_node;
		new_node->right = this->min;
		new_node->left = this->min->left;
		this->min->left = new_node;
		if (new_node->key < this->min->key)
			this->min = new_node;
	}
	else {
		this->min = new_node;
	}
	this->no_of_nodes++;
}
// Linking the heap nodes in parent child relationship
void FibonacciHeap::Fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	if (ptr1->right == ptr1)
		this->min = ptr1;
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->key < (ptr1->child)->key)
		ptr1->child = ptr2;
	ptr1->degree++;
}
// Consolidating the heap

void FibonacciHeap::Consolidate()
{
	int temp1;
	double temp2 = (log(this->no_of_nodes)) / (log(2));
	//int temp3 = temp2;
	node* arr[100];
	for (int i = 0; i <= 100; i++)
		arr[i] = NULL;
	node* ptr1 = this->min;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do {
		ptr4 = ptr4->right;
		temp1 = ptr1->degree;
		while (arr[temp1] != NULL) {
			ptr2 = arr[temp1];
			if (ptr1->key > ptr2->key) {
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == this->min)
				this->min = ptr1;
			Fibonnaci_link(ptr2, ptr1);
			if (ptr1->right == ptr1)
				this->min = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->right;
	} while (ptr1 != this->min);
	this->min = NULL;
	for (int j = 0; j <= 100; j++) {
		if (arr[j] != NULL) {
			arr[j]->left = arr[j];
			arr[j]->right = arr[j];
			if (this->min != NULL) {
				(this->min->left)->right = arr[j];
				arr[j]->right = this->min;
				arr[j]->left = this->min->left;
				this->min->left = arr[j];
				if (arr[j]->key < this->min->key)
					this->min = arr[j];
			}
			else {
				this->min = arr[j];
			}
			if (this->min == NULL)
				this->min = arr[j];
			else if (arr[j]->key < this->min->key)
				this->min = arr[j];
		}
	}
}

// Function to extract minimum node in the heap
void FibonacciHeap::Extract_min()
{
	if (this->min == NULL)
		cout << "The heap is empty" << endl;
	else {
		node* temp = this->min;
		node* pntr;
		pntr = temp;
		node* x = NULL;
		if (temp->child != NULL) {

			x = temp->child;
			do {
				pntr = x->right;
				(this->min->left)->right = x;
				x->right = this->min;
				x->left = this->min->left;
				this->min->left = x;
				if (x->key < this->min->key)
					this->min = x;
				x->parent = NULL;
				x = pntr;
			} while (pntr != temp->child);
		}
		(temp->left)->right = temp->right;
		(temp->right)->left = temp->left;
		this->min = temp->right;
		if (temp == temp->right && temp->child == NULL)
			this->min = NULL;
		else {
			this->min = temp->right;
			Consolidate();
		}
		this->no_of_nodes--;
	}
}

// Cutting a node in the heap to be placed in the root list
void FibonacciHeap::Cut(struct node* found, struct node* temp)
{
	if (found == found->right)
		temp->child = NULL;

	(found->left)->right = found->right;
	(found->right)->left = found->left;
	if (found == temp->child)
		temp->child = found->right;

	temp->degree = temp->degree - 1;
	found->right = found;
	found->left = found;
	(this->min->left)->right = found;
	found->right = this->min;
	found->left = this->min->left;
	this->min->left = found;
	found->parent = NULL;
	found->mark = 'B';
}

// Recursive cascade cutting function
void FibonacciHeap::Cascase_cut(struct node* temp)
{
	node* ptr5 = temp->parent;
	if (ptr5 != NULL) {
		if (temp->mark == 'W') {
			temp->mark = 'B';
		}
		else {
			Cut(temp, ptr5);
			Cascase_cut(ptr5);
		}
	}
}

// Function to decrease the value of a node in the heap
void FibonacciHeap::Decrease_key(struct node* found, int val)
{
	if (this->min == NULL)
		cout << "The Heap is Empty" << endl;

	if (found == NULL)
		cout << "Node not found in the Heap" << endl;

	found->key = val;

	struct node* temp = found->parent;
	if (temp != NULL && found->key < temp->key) {
		Cut(found, temp);
		Cascase_cut(temp);
	}
	if (found->key < this->min->key)
		this->min = found;
}

// Function to find the given node
void FibonacciHeap::Find(struct node* min, int old_val, int val)
{
	struct node* found = NULL;
	node* temp5 = this->min;
	temp5->c = 'Y';
	node* found_ptr = NULL;
	if (temp5->key == old_val) {
		found_ptr = temp5;
		temp5->c = 'N';
		found = found_ptr;
		Decrease_key(found, val);
	}
	if (found_ptr == NULL) {
		if (temp5->child != NULL)
			Find(temp5->child, old_val, val);
		if ((temp5->right)->c != 'Y')
			Find(temp5->right, old_val, val);
	}
	temp5->c = 'N';
	found = found_ptr;
}

// Deleting a node from the heap
void FibonacciHeap::Deletion(int val)
{
	if (this->min == NULL)
		cout << "The heap is empty" << endl;
	else {

		// Decreasing the value of the node to 0
		Find(this->min, val, 0);

		// Calling Extract_min function to
		// delete minimum value node, which is 0
		Extract_min();
		cout << "Key Deleted" << endl;
	}
}

// Function to display the heap
void FibonacciHeap::display()
{
	node* ptr = this->min;
	if (ptr == NULL)
		cout << "The Heap is Empty" << endl;

	else {
		cout << "The root nodes of Heap are: " << endl;
		int i = getNodeNum();
		do {
			cout << ptr->key;
			ptr = ptr->right;
			//if (ptr != this->min) {
			cout << "-->";
			//}
		} while (--i);//ptr != this->min && ptr->right != NULL);
		cout << endl
			<< "The heap has " << this->no_of_nodes << " nodes" << endl
			<< endl;
	}
}

FibonacciHeap* UnionFibonacciHeap(FibonacciHeap &H1, FibonacciHeap &H2) {
	FibonacciHeap* H = new FibonacciHeap;
	H->GetMin() = H1.GetMin();
	if (H1.GetMin()->key > H2.GetMin()->key) {
		std::swap(H1, H2);
	}
	node* an = H1.GetMin()->right;
	node* bp = H2.GetMin()->left;
	H1.GetMin()->right = H2.GetMin();
	H2.GetMin()->left = H1.GetMin();
	an->left = bp;
	bp->right = an;
	H->setNodeNum(H1.getNodeNum() + H2.getNodeNum());

	return H;
}




// Driver code
int main()
{
	// We will create H1 heap and insert 3 nodes into it
	cout << "Creating an initial heap" << endl;
	FibonacciHeap h;
	h.insertion(5);
	h.insertion(2);
	h.insertion(8);
	h.insertion(15);
	h.insertion(12);
	h.insertion(18);

	// Now we will display the root list of the heap
	h.display();

	h.Extract_min();
	h.display();
	h.Extract_min();
	h.display();
	h.Extract_min();
	h.display();
	h.Extract_min();
	h.display();
	h.Extract_min();
	h.display();
	h.Extract_min();
	h.display();

	system("pause");
	return 0;
}



