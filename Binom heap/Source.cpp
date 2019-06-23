#include <iostream>
#include <cstdlib>
#include <list>

using namespace std;

struct Node
{
	int data, degree;
	Node *child;
	Node* sibling;
	Node* parent;
};

Node* newNode(int key)
{
	Node* temp = new Node;
	temp->data = key;
	temp->degree = 0;
	temp->child = temp->parent = temp->sibling = 0;
	return temp;
}

Node* mergeBinomialTrees(Node *b1, Node *b2)
{
	if (b1->data > b2->data)
		swap(b1, b2);

	b2->parent = b1;
	b2->sibling = b1->child;
	b1->child = b2;
	b1->degree++;

	return b1;
}

list<Node*> unionBionomialHeap(list<Node*> l1, list<Node*> l2)
{
	list<Node*> _new;
	list<Node*>::iterator oldHeap = l1.begin();
	list<Node*>::iterator newHeap = l2.begin();
	while (oldHeap != l1.end() && newHeap != l2.end())
	{
		if ((*oldHeap)->degree <= (*newHeap)->degree)
		{
			_new.push_back(*oldHeap);
			oldHeap++;
		}
		else
		{
			_new.push_back(*newHeap);
			newHeap++;
		}
	}

	while (oldHeap != l1.end())
	{
		_new.push_back(*oldHeap);
		oldHeap++;
	}

	while (newHeap != l2.end())
	{
		_new.push_back(*newHeap);
		newHeap++;
	}
	return _new;
}

list<Node*> adjust(list<Node*> _heap)
{
	if (_heap.size() <= 1)
		return _heap;
	list<Node*> new_heap;
	list<Node*>::iterator it1, it2, it3;
	it1 = it2 = it3 = _heap.begin();

	//showData(_heap, it1,it2,it3);

	if (_heap.size() == 2)
	{
		it2 = it1;
		it2++;
		it3 = _heap.end();
	}
	else
	{
		it2++;
		it3 = it2;
		it3++;
	}
	while (it1 != _heap.end())
	{
		//showData(_heap, it1,it2,it3);
		if (it2 == _heap.end())
			it1++;

		else if ((*it1)->degree < (*it2)->degree)
		{
			it1++;
			it2++;
			if (it3 != _heap.end())
				it3++;
		}

		else if (it3 != _heap.end() &&
			(*it1)->degree == (*it2)->degree &&
			(*it1)->degree == (*it3)->degree)
		{
			it1++;
			it2++;
			it3++;
		}

		else if ((*it1)->degree == (*it2)->degree)
		{
			//Node *temp;
				//showData(_heap, it1,it2,it3);
			*it1 = mergeBinomialTrees(*it1, *it2);
			it2 = _heap.erase(it2);
			if (it3 != _heap.end())
				it3++;
		}
	}
	return _heap;
}

list<Node*> insertATreeInHeap(list<Node*> _heap, Node *tree)
{
	list<Node*> temp;
	temp.push_back(tree);
	temp = unionBionomialHeap(_heap, temp);

	return adjust(temp);
}

list<Node*> removeMinFromTreeReturnBHeap(Node *tree)
{
	list<Node*> heap;
	if (tree == NULL) return heap;

	Node *temp = tree->child;
	Node *lo;

	while (temp)
	{
		lo = temp;
		temp = temp->sibling;
		lo->sibling = NULL;
		heap.push_front(lo);
	}
	return heap;
}

list<Node*> insert(list<Node*> _head, int key)
{
	Node *temp = newNode(key);
	return insertATreeInHeap(_head, temp);
}

Node* getMin(list<Node*> _heap)
{
	list<Node*>::iterator it = _heap.begin();
	Node *temp = *it;
	while (it != _heap.end())
	{
		if ((*it)->data < temp->data)
			temp = *it;
		it++;
	}
	return temp;
}

list<Node*> DeleteMin(list<Node*> _heap)
{
	list<Node*> new_heap, lo;
	Node *temp;

	temp = getMin(_heap);
	list<Node*>::iterator it;
	it = _heap.begin();
	while (it != _heap.end())
	{
		if (*it != temp)
		{
			new_heap.push_back(*it);
		}
		it++;
	}
	lo = removeMinFromTreeReturnBHeap(temp);
	new_heap = unionBionomialHeap(new_heap, lo);
	new_heap = adjust(new_heap);
	return new_heap;
}

void printTree(Node *h)
{
	while (h)
	{

		cout << h->data;

		if (h->child == NULL) return;

		cout << " ( ";
		printTree(h->child);
		cout << " ) ";
		h = h->sibling;
	}
}

void printHeap(list<Node*> _heap)
{
	if (_heap.begin() == _heap.end())
	{
		cout << "Heap is empty\n";
		return;
	}

	list<Node*> ::iterator it;
	it = _heap.begin();
	while (it != _heap.end())
	{
		printTree(*it);
		it++;
		if (it != _heap.end()) cout << " <--> ";
	}
}

bool Continue()
{
	cout << endl;
	cout << " Back to menu (y(YES)/n(NO))?";
	char tmp;
	cin >> tmp;
	if (tmp == 'n')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Function(list<Node*> heap)
{
	bool cont = true;

	do
	{
		cout << " Our heap : ";
		printHeap(heap);
		cout << endl;
		int i;
		cout << " 1 - Insert element\n 2 - Delete minimum element of heap\n 3 - Finish\n" << endl;
		cout << " write number ";
		cin >> i;
		cout << endl;

		switch (i)
		{
		case 1:
			int el;
			cout << " Put element : ";
			cin >> el;

			heap = insert(heap, el);

			cout << " Pushed element is " << el << endl;
			cout << " Heap after insertion of element\n";
			cout << " ";
			printHeap(heap);
			cont = Continue();
			break;
		case 2:
			heap = DeleteMin(heap);
			cout << " Heap after deletion of minimum element\n";
			cout << " ";
			printHeap(heap);
			cont = Continue();
			break;
		case 3:
			cont = false;
			break;
		}
		cout << endl;
		cout << " ---------------------------------------------------------------- " << endl << endl;
	} while (cont);
	cout << " -----------------------| RESULT OF WORK |-----------------------\n " << endl;
	cout << " \tOur list : ";
	printHeap(heap);
	cout << "\n ---------------------------------------------------------------- " << endl << endl;
}

int main()
{
	list<Node*> heap;
	Function(heap);
	return 0;
}


