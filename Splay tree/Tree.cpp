
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Node {
	Node* left;
	Node* right;
	string name;
	int price;
}Node;



Node* CreateTree(const string & name, const int& price) {
	Node* root = new Node;
	root->name = name;
	root->price = price;
	root->left = root->right = NULL;

	return root;
}

Node* RightRotate(Node* root)
{
	Node* tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	return tmp;
}

Node* LeftRotate(Node* root)
{
	Node* tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	return tmp;
}

Node* Splay(int key, Node* root)
{
	if (!root)
		return NULL;
	Node header;
	header.left = header.right = NULL;
	Node* LeftTreeMax = &header;
	Node* RightTreeMin = &header;
	while (1)
	{
		if (key < root->price)
		{
			if (!root->left)
				break;
			if (key < root->left->price)
			{
				root = RightRotate(root);
				if (!root->left)
					break;
			}
			RightTreeMin->left = root;
			RightTreeMin = RightTreeMin->left;
			root = root->left;
			RightTreeMin->left = NULL;
		}
		else if (key > root->price)
		{
			if (!root->right)
				break;
			if (key > root->right->price)
			{
				root = LeftRotate(root);
				if (!root->right)
					break;
			}
			LeftTreeMax->right = root;
			LeftTreeMax = LeftTreeMax->right;
			root = root->right;
			LeftTreeMax->right = NULL;
		}
		else
			break;
	}

	LeftTreeMax->right = root->left;
	RightTreeMin->left = root->right;
	root->left = header.right;
	root->right = header.left;
	return root;
}

void AddToTree(Node* &root, const string name, const int price) {
	if (!root) {
		root = new Node;
		root->price = price;
		root->name = name;
		root->left = root->right = NULL;
		return;
	}
	if (price > root->price) {
		AddToTree(root->right, name, price);
	}
	else if (price < root->price) {
		AddToTree(root->left, name, price);
	}
	else
		cout << "Number is exist\n";
}



void ShowTree(Node* root, int p = -1) {
	if (root == NULL) {
		return;
	}
	else {
		ShowTree(root->right, ++p);

		for (int i = 0; i < p; i++) {
			cout << " - ";
		}

		cout << root->price << endl;

		p--;
	}
	ShowTree(root->left, ++p);

}

void ShowTreeFinal(Node* root, int p = -1) {
	if (root == NULL) {
		return;
	}
	else {
		ShowTreeFinal(root->right, ++p);
		if (!root->right)
		{
			for (int i = 0; i < p; i++) {
				cout << " - ";
			}
			cout << " - NIL " << endl;
		}
		for (int i = 0; i < p; i++) {
			cout << " - ";
		}

		cout << root->name << " = " << root->price << endl;

		if (!root->left)
		{
			for (int i = 0; i < p; i++) {
				cout << " - ";
			}
			cout << " - NIL" << endl;
		}
		p--;
	}
	ShowTreeFinal(root->left, ++p);

}

Node* FindNode(Node* root, int price)
{
	static Node* SearchNode = NULL;
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		if (root->price == price)
		{
			SearchNode = root;
		}
		FindNode(root->right, price);
		FindNode(root->left, price);
	}
	return SearchNode;
}



Node* Find(int price, Node* root) {
	Node* tmp = FindNode(root, price);
	if (tmp != NULL) {
		return Splay(price, root);
	}
	else {
		cout << " ERROR " << endl;
		return NULL;
	}
}



int main() {
	Node* root = new Node;

	root = CreateTree("Kobzar", 180);
	ShowTree(root);
	cout << "------------------------" << endl;
	AddToTree(root, "Dandelion", 500);
	ShowTree(root);
	cout << "------------------------" << endl;
	AddToTree(root, "Karenina", 230);
	ShowTree(root);
	cout << "------------------------" << endl;
	AddToTree(root, "To Space", 110);
	ShowTree(root);
	cout << "------------------------" << endl;
	AddToTree(root, "Viy", 219);

	ShowTree(root);

	root = Splay(7, root);
	cout << "------------------------" << endl;
	ShowTree(root);
	system("pause");
	return 0;
}
