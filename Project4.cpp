#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Exception {};

//Array class exceptions
class ArrayException : public Exception {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};

//binary tree exceptions
class BinaryTreeException : public Exception {};
class BinaryTreeMemory : public BinaryTreeException {};
class BinaryTreeGaveSubtreeToEmptyTree : public BinaryTreeException {};
class BinaryTreeEmptyTree : public BinaryTreeException {};

//The node class that will be used by the ArrayBT class is implemented here
template <class DT>
class ArrayBTNode
{
protected:
	DT* _info;//holds the value to be held in the node
	int _left;//holds the position of the left child inside the ArrayBT 
	int _right;//holds the position of the right child inside the ArrayBT 
	void copy(const ArrayBTNode<DT>& a);//copy method to be used by the constructor and operator=
public:
	ArrayBTNode();//empty constructor
	ArrayBTNode(DT v);//constructor initializing a value to the node
	ArrayBTNode(const ArrayBTNode<DT>& a);//copy constructor
	virtual ~ArrayBTNode();//deconstructor
	//all the operator overrides
	void operator= (const ArrayBTNode<DT>& a);
	bool operator< (const ArrayBTNode<DT>& a);
	bool operator> (const ArrayBTNode<DT>& a);
	bool operator== (const ArrayBTNode<DT>& a);
	bool operator<= (const ArrayBTNode<DT>& a);
	bool operator>= (const ArrayBTNode<DT>& a);
	bool operator!= (const ArrayBTNode<DT>& a);
	friend ostream& operator<<(ostream& s, ArrayBTNode<DT>& p) {
		p.display(s);
		return s;
	}

	bool isEmpty();//checks the value of _info
	int getLeft();//returns _left
	int getRight();//returns _right
	DT* getInfo();//returns _info
	void setRight(int v);//set method for _right
	void setLeft(int v);//set method for _left
	void setInfo(const DT& v);//set method for _info
	bool isLeaf();//checks values of _left _right
	void display(ostream& s);//display method
};

template <class DT>
void ArrayBTNode<DT>::copy(const ArrayBTNode<DT>& a) {
	_info = a._info;
	_left = a._left;
	_right = a._right;
}

template <class DT>
ArrayBTNode<DT>::ArrayBTNode() {
	_info = NULL;
	_left = -1;
	_right = -1;
}

template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT v) {
	_info = new DT(v);
	_left = -1;
	_right = -1;
}

template <class DT>
ArrayBTNode<DT>::~ArrayBTNode() {
	if (_info != NULL) {
		delete _info;
		_info = NULL;
	}
}

template <class DT>
ArrayBTNode<DT>::ArrayBTNode(const ArrayBTNode<DT>& a)
{
	copy(a);
}

template <class DT>
void ArrayBTNode<DT>::operator=(const ArrayBTNode<DT>& a)
{
	copy(a);
}

template <class DT>
bool ArrayBTNode<DT>::operator<(const ArrayBTNode<DT>& a)
{
	return (*_info < *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::operator>(const ArrayBTNode<DT>& a)
{
	return (*_info > *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::operator==(const ArrayBTNode<DT>& a)
{
	return (*_info == *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::operator<=(const ArrayBTNode<DT>& a)
{
	return (*_info <= *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::operator>=(const ArrayBTNode<DT>& a)
{
	return (*_info >= *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::operator!=(const ArrayBTNode<DT>& a)
{
	return (*_info != *(a._info));
}

template <class DT>
bool ArrayBTNode<DT>::isEmpty()
{
	return (_info == NULL);
}

template <class DT>
int ArrayBTNode<DT>::getLeft()
{
	return _left;
}

template <class DT>
int ArrayBTNode<DT>::getRight()
{
	return _right;
}

template <class DT>
DT* ArrayBTNode<DT>::getInfo()
{
	return _info;
}

template <class DT>
void ArrayBTNode<DT>::setRight(int v)
{
	_right = v;
}

template <class DT>
void ArrayBTNode<DT>::setLeft(int v)
{
	_left = v;
}

template <class DT>
void ArrayBTNode<DT>::setInfo(const DT& v)
{
	if (_info != NULL)
		delete _info;
	_info = new DT(v);
}

template <class DT>
bool ArrayBTNode<DT>::isLeaf()
{
	return (_left==-1 && _right==-1);
}

template <class DT>
void ArrayBTNode<DT>::display(ostream& s) {
	if (_info != NULL)
		s << *_info;
	else
		s << "Empty Node";
}

//the ArrayBT implementation
template <class DT>
class ArrayBT
{
protected:
	vector<ArrayBTNode<DT>*>* theRows;//vector to hold all the nodes
	int _root; // index position of the root of the binary tree in the vector
	int _noNodes; // the number of nodes in the binary tree
	int _size; // the maximum size of the vector
	stack<int> freeLocations; // STL stack
	void copy(const ArrayBT<DT>& a);//copy method to be used by copy constructor and operator=
	void deleteRows();//deletion method to be used by the deconstructor
public:
	ArrayBT();//empty constructor
	ArrayBT(int n);//constructor giving vector an initial size
	ArrayBT(int n, const DT& v);//constructor giving vector an initial size and one value to give to all nodes
	ArrayBT(const ArrayBT<DT>& a);//copy constructor
	virtual ~ArrayBT();//deconstructor
	void operator= (const ArrayBT<DT>& a);//operator=
	virtual ArrayBTNode<DT>& operator[] (int index);//operator[]
};

const int ARRAYBT_CLASS_DEFAULT_SIZE = 100;

template <class DT>
ArrayBT<DT>::ArrayBT()
{
	_root = -1;
	_noNodes = 0;
	_size = ARRAYBT_CLASS_DEFAULT_SIZE;
	theRows = new vector<ArrayBTNode<DT>*>(ARRAYBT_CLASS_DEFAULT_SIZE);
	if (theRows == NULL)
		throw ArrayMemoryException();
	for (int i = 0; i < ARRAYBT_CLASS_DEFAULT_SIZE; i++) {
		(*theRows)[i] = new ArrayBTNode<DT>();
		freeLocations.push(ARRAYBT_CLASS_DEFAULT_SIZE - 1 - i);
	}
	if ((*theRows)[0] == NULL)
	{
		throw ArrayMemoryException();
	}
}

template <class DT>
ArrayBT<DT>::ArrayBT(int n)
{
	_root = -1;
	_noNodes = 0;
	_size = n;
	theRows = new vector<ArrayBTNode<DT>*>(n);
	if (theRows == NULL)
		throw ArrayMemoryException();
	for (int i = 0; i < n; i++) {
		(*theRows)[i] = new ArrayBTNode<DT>();
		freeLocations.push(n - 1 - i);
	}
	if ((*theRows)[0] == NULL)
	{
		throw ArrayMemoryException();
	}
}

template <class DT>
ArrayBT<DT>::ArrayBT(int n,const DT& v)
{
	_root = -1;
	_noNodes = 0;
	_size = n;
	theRows = new vector<ArrayBTNode<DT>*>(n);
	if (theRows == NULL)
		throw ArrayMemoryException();
	for (int i = 0; i < n; i++) {
		(*theRows)[i] = new ArrayBTNode<DT>(v);
		freeLocations.push(n - 1 - i);
	}
	if ((*theRows)[0] == NULL)
	{
		throw ArrayMemoryException();
	}
}

template <class DT>
void ArrayBT<DT>::deleteRows()
{
	if (theRows != NULL)
	{
		for (int i = 0; i < _size; i++)
		{
			if ((*theRows)[i] != NULL) {
				delete (*theRows)[i];
				(*theRows)[i] = NULL;
			}
		}
		delete theRows;
		theRows = NULL;
	}
}

template <class DT>
ArrayBT<DT>::~ArrayBT()
{
	deleteRows();
}

template <class DT>
void ArrayBT<DT>::copy(const ArrayBT<DT>& a)
{
	deleteRows(); 
	_root = a._root;
	_noNodes = a._noNodes;
	_size = a._size;
	freeLocations = a.freeLocations;
	theRows = new vector <ArrayBTNode<DT>*>(_size);
	if (theRows == NULL)
		throw ArrayMemoryException();
	for (int i = 0; i < _size; i++)
	{
		(*theRows)[i] = new ArrayBTNode<DT> (a[i]);
		if ((*theRows)[i] == NULL)
			throw ArrayMemoryException();
	}
}

template <class DT>
ArrayBT<DT>::ArrayBT(const ArrayBT<DT>& a)
{
	copy(a);
}

template <class DT>
void ArrayBT<DT>::operator=(const ArrayBT<DT>& a)
{
	copy(a);
}

template <class DT>
ArrayBTNode<DT>& ArrayBT<DT>::operator[] (int index)
{
	return (*((*theRows)[index]));
}

class BinarySearchTreeNotFound : public BinaryTreeException {};

template <class DT>
class ArrayBST : virtual public ArrayBT<DT>
{
public:
	ArrayBST();//empty constructor
	ArrayBST(int n);//vector size given constructor calls superconstructor
	ArrayBST(int n, const DT& v);//vector size and value for nodes given constructor calls superconstructor
	ArrayBST(const ArrayBST<DT>& a);//copy constructor, constructor calls superconstructor
	virtual ~ArrayBST();//deconstructor
	void operator= (const ArrayBST& a);//operator=
	int _find(const DT& data);//find returns the location of value or location of closest value 
	int find(const DT& q);//returns the same as _find but will throw exception if exact value is not found
	void resetChildLocation(int v);//finds the node that points to an empty child and sets it to -1
	void setChildLocation(int v, int n);//finds the node that points to an empty child and sets it to n
	void insert(const DT& data);//inserts a value into the BST
	void remove(const DT& data);//removes a value from the BST
	void display(ostream& s);//display method handles both preorder and inorder traversals
	void DisplayRaw();//raw diplay method as specified in description
	//operator<< override
	friend ostream& operator<<(ostream& s, ArrayBST<DT>& p) {
		p.display(s);
		return s;
	}
};

template <class DT>
ArrayBST<DT>::ArrayBST():ArrayBT<DT>() {}

template <class DT>
ArrayBST<DT>::ArrayBST(int n) :ArrayBT<DT>(n) {}

template <class DT>
ArrayBST<DT>::ArrayBST(int n, const DT& v) :ArrayBT<DT>(n, v) {}

template <class DT>
ArrayBST<DT>::~ArrayBST()
{
	deleteRows();
}

template <class DT>
ArrayBST<DT>::ArrayBST(const ArrayBST<DT>& a):ArrayBT<DT>(a) {}

template <class DT>
void ArrayBST<DT>::operator=(const ArrayBST<DT>& a) {
	copy(a);
}

template <class DT>
int ArrayBST<DT>::_find(const DT& data)
{
	//start looking at the root
	int index = _root;

	//get the node at that position
	ArrayBTNode<DT>* node = (*theRows)[index];

	//create another node for comparison purposes
	ArrayBTNode<DT> findMe(data);
	
	while (true)//loop to find what we need
	{
		if (*node < findMe)//what we are looking for is greater than current node, move right
		{
			if (node->getRight() == -1)//we cannot move right because there is no right child so we return
				return index;
			index = node->getRight();
		}
	
		else if (*node > findMe)//what we are looking for is less than current node, move left
		{
			if (node->getLeft() == -1)//we cannot move right because there is no left child so we return
				return index;
			index = node->getLeft();
		}

		else//we found an exact match
			return index;

		node = (*theRows)[index];
	}
}

template<class DT>
int ArrayBST<DT>::find(const DT& q)
{
	int foundPosition = _find(q);
	ArrayBTNode<DT>* node = (*theRows)[foundPosition];
	ArrayBTNode<DT> check(q);
	if (*node!=check)//this checks if an exact match is found
		throw BinarySearchTreeNotFound();
	return foundPosition;
}

template<class DT>
void ArrayBST<DT>::resetChildLocation(int v)
{
	//search through the vector to find the value to reset
	for (int i = 0; i < _size; i++) {
		if ((*theRows)[i]->getRight() == v) {
			(*theRows)[i]->setRight(-1);
			break;
		}
		if ((*theRows)[i]->getLeft() == v) {
			(*theRows)[i]->setLeft(-1);
			break;
		}
	}
}

template<class DT>
void ArrayBST<DT>::setChildLocation(int v , int n)
{
	//search through the vector to find the value to set to n
	for (int i = 0; i < _size; i++) {
		if ((*theRows)[i]->getRight() == v) {
			(*theRows)[i]->setRight(n);
			break;
		}
		if ((*theRows)[i]->getLeft() == v) {
			(*theRows)[i]->setLeft(n);
			break;
		}
	}
}


template<class DT>
void ArrayBST<DT>::insert(const DT& q)
{
	//if there are no nodes in the vector
	if (_root == -1) {
		_root = 0;
		delete (*theRows)[_root];
		(*theRows)[_root] = new ArrayBTNode<DT>(q);
		freeLocations.pop();
	}
	//there are nodes already in the vector
	else {
		//node found using _find
		ArrayBTNode<DT>* node = (*theRows)[_find(q)];

		//create this to check what we need to insert against what we found using _find
		ArrayBTNode<DT> insertMe(q);

		if ((*node) < insertMe)//needs to become a right child
		{
			//there are free spots available in the vector
			if (!freeLocations.empty())
			{
				node->setRight(freeLocations.top());
				delete (*theRows)[freeLocations.top()];
				(*theRows)[freeLocations.top()] = new ArrayBTNode<DT>(q);
				freeLocations.pop();
			}
			//no free spots left but we can increase the size of our vector
			else {
				theRows->push_back(new ArrayBTNode<DT>(q));
				node->setRight(_size);
				_size++;
			}
			_noNodes++;
		}
		else if ((*node) > insertMe)//needs to become a left child
		{
			if (!freeLocations.empty())//there are free spots available in the vector
			{
				node->setLeft(freeLocations.top());
				delete (*theRows)[freeLocations.top()];
				(*theRows)[freeLocations.top()] = new ArrayBTNode<DT>(q);
				freeLocations.pop();
			}
			//no free spots left but we can increase the size of our vector
			else {
				theRows->push_back(new ArrayBTNode<DT>(q));
				node->setLeft(_size);
				_size++;
			}
			_noNodes++;
		}
	}
}

template<class DT>
void ArrayBST<DT>::remove(const DT& q)
{
	int position = _find(q);//save the position found using _find
	int newRight;//to be used in the only right child case
	int newLeft;//to be used in the only left child case
	ArrayBTNode<DT>* node = (*theRows)[position];//node at found position
	ArrayBTNode<DT>* node2;//to be used in the two child case
	ArrayBTNode<DT> check(q);//use to check against found

	//check if the node is actually in the vector
	if (*node != check)
		throw BinarySearchTreeNotFound();
	//three cases follow, node to be removed is a leaf, has one child, has two children
	if (node->isLeaf()) {
		delete (*theRows)[position];
		(*theRows)[position] = new ArrayBTNode<DT>();
		resetChildLocation(position);
		freeLocations.push(position);
		if (_root == position) {
			_root = -1;
		}
		_noNodes--;
	}
	//only has right child
	else if (node->getLeft() == -1 && node->getRight() != -1)
	{
		newRight = node->getRight();
		delete (*theRows)[position];
		(*theRows)[position] = new ArrayBTNode<DT>();
		setChildLocation(position,newRight);
		freeLocations.push(position);
		if (_root == position) {
			_root = newRight;
		}
		_noNodes--;

	}
	//only has left child
	else if (node->getLeft() != -1 && node->getRight() == -1)
	{
		newLeft = node->getLeft();
		delete (*theRows)[position];
		(*theRows)[position] = new ArrayBTNode<DT>();
		setChildLocation(position, newLeft);
		freeLocations.push(position);
		if (_root == position) {
			_root = newLeft;
		}
		_noNodes--;
	}
	//has both children
	else
	{
		//finding the left most child of the right child
		node2 = (*theRows)[node->getRight()];
		while (node2->getLeft() != -1)
		{
			node2 = (*theRows)[node2->getLeft()];
		}
		int newInfo = *(node2->getInfo());
		//calls remove on that left most child of the right child
		remove(*(node2->getInfo()));
		node->setInfo(newInfo);
	}	
}

template <class DT>
void ArrayBST<DT>::display(ostream& s) {
	//case of an empty tree
	if (_root == -1) {
		s << "Empty Tree" << endl;
	}
	//diplay both preorder and inorder traversals
	else {
		stack<ArrayBTNode<DT>*> snack;
		ArrayBTNode<DT>* x;
		ArrayBTNode<DT>* y;
		snack.push((*theRows)[_root]);
		s << "Preorder Traversal: ";
		while (!snack.empty())
		{
			x = snack.top();
			snack.pop();
			cout << *x << " ";
			if (x->getRight() != -1)
				snack.push((*theRows)[x->getRight()]);
			if (x->getLeft() != -1)
				snack.push((*theRows)[x->getLeft()]);
		}
		cout << endl;
		cout << "Inorder Traversal: ";
		snack.push((*theRows)[_root]);
		y = (*theRows)[_root];
		while (y->getLeft() != -1)
		{
			snack.push((*theRows)[y->getLeft()]);
			y = (*theRows)[y->getLeft()];
		}
		while (!snack.empty())
		{
			x = snack.top();
			snack.pop();
			cout << *x << " ";
			if (x->getRight() != -1)
			{
				y = (*theRows)[x->getRight()];
				snack.push(y);
				while (y->getLeft() != -1)
				{
					snack.push((*theRows)[y->getLeft()]);
					y = (*theRows)[y->getLeft()];
				}
			}
		}
	}
}

template <class DT>
void ArrayBST<DT>::DisplayRaw() {
	cout << "cat" << _root << endl;
	//display contents of vector as described in the project description
	for (int i = 0; i < _size; i++)
	{
		cout << "Position: " << i << ", Info: " << *(*theRows)[i] << ", Left Position: " 
			<< (*theRows)[i]->getLeft() << ", Right Position: " << (*theRows)[i]->getRight() << endl;
	}
	//display the contents of the stack as stated in the project description
	stack<int> copy = freeLocations;
	cout << "Free Locations in the stack:";
	if (copy.empty())
	cout << " none" << endl;
	else {
		while (!copy.empty()) {
			cout << " " << copy.top();
			copy.pop();
		}
		cout << endl;
	}
}

int main() {

	int value;//holds the integers to be read in
	char command;//holds the character to be read in

	cin >> value;//read in line 1 with the initial size of the vector
	cout << value << endl;//output the value read in

	ArrayBST<int>* myT = new ArrayBST<int>(value);

	myT->insert(9);
	myT->insert(5);
	myT->insert(3);

	myT->DisplayRaw();
	myT->remove(9);
	myT->DisplayRaw();

	cin >> command;//read in the first command from input file (priming read)
	//while there are more inputs
	while (!cin.eof()) {
	//5 cases for the command input
	//both output cases do not need to read in an integer value from the user
	switch (command) {

		case 'I': // insert

			cin >> value; //value to be inserted into the binary tree
			//cout << command << " " << value << endl; //print out the values given by the user

			myT->insert(value);

			break;

		case 'R': // remove

			cin >> value; // value to be removed from the binary tree
			cout << command << " " << value << endl; //print out the values given by the user

			try {
				myT->remove(value);
			}
			catch (BinarySearchTreeNotFound& e) {
				cout << "Integer value was not removed because it was not found in the binary search tree" << endl;
			}

			break;

		case 'F': // search

			cin >> value; // value to find in the binary tree
			cout << command << " " << value << endl; //print out the values given by the user

			try {
				cout << "Integer found at position: " << myT->find(value) << endl;
			}
			catch (BinarySearchTreeNotFound& e) {
				cout << "Integer value was not found in the binary search tree" << endl;
			}
			break;

		case 'O': // output the tree using the ostream operator

			cout << command << endl; // print out the command given by the user

			cout << *myT << endl;
			break;

		case 'A': // output using DisplayRaw method

			cout << command << endl; // print out the command given by the user
			myT->DisplayRaw();
			break;
		}

		cin >> command;//read in command or ends the while loop
	}
	delete myT;
	return 0;
}