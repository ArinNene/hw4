#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
h as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
		static Node<Key,Value>* successor(Node<Key,Value>* current);

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap(Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static void clearHelper(Node<Key, Value> *input);
    static int balancedChecker(Node<Key,Value>* root);
		static void moveUp(Node<Key,Value>* op, Node<Key,Value>* child);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
} 

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return this->current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
	this->current_ = successor(this->current_);
	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Value operativeValue = keyValuePair.second;
    Key operativeKey = keyValuePair.first;
    

    if (root_ == NULL){
        if (empty()) {
            Node<Key,Value>* temp = new Node<Key,Value>(operativeKey,operativeValue,NULL);
            root_ = temp;
            return;
        }
    }
    else {
        Node<Key,Value>* parent;
        Node<Key,Value>* operativeRoot = root_;
        while (operativeRoot != NULL) {
            Key focusKey = operativeRoot->getKey();
            if (focusKey == operativeKey) { //if key already exists in tree, just switch in the value
                for (int i = 0; i < 1; i++) {
                    operativeRoot->setValue(operativeValue);
										return;
                }
            }
            else if (operativeKey > focusKey) { //if key greater than current key, move right. If it was equal, then key would've been found.
							for (int i = 0; i < 1; i++) {
								parent = operativeRoot;
								operativeRoot = operativeRoot->getRight();
							}
						}
						else if (operativeKey < focusKey) { //if key is less than current key, move left
							for (int i = 0; i < 1; i++) {
								parent = operativeRoot;
								operativeRoot = operativeRoot->getLeft();
							}
						}
        }
				Node<Key,Value>* temp = new Node<Key,Value>(operativeKey,operativeValue,NULL); //insert value
				if (temp->getKey() > parent->getKey()) {
					parent->setRight(temp);
				}
				else {
					parent->setLeft(temp);
				}
				temp->setParent(parent);
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::moveUp(Node<Key,Value>* op, Node<Key,Value>* child) {
	if (child == NULL || op == NULL) {
		return;
	}
	Node<Key,Value>* parent = op->getParent();
	for (int i = 0; i < 1; i++) {
		child->setParent(parent);
		if (parent == NULL) {
			if (parent == NULL) {
				//do nothing.
			}
		}
		else if (op == parent->getRight()) {
			parent->setRight(child);
		}
		else {
			parent->setLeft(child);
		}
	}
	op->setParent(child);
	op->setRight(NULL);
	op->setLeft(NULL);
}
/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
		Node<Key,Value>* removeThis = internalFind(key);
		//base case: node does not exist.
		if (removeThis == NULL) {
			return;
		}
		else {
			//cases: if it is the only node in the tree or if it has no children
			if (removeThis == root_ && removeThis->getRight() == NULL && removeThis->getLeft() == NULL) { // only node
				for (int i = 0; i < 1; i++) {
					delete removeThis;
					root_ = NULL;
					return;
				}
			}
			else {
				Node<Key,Value>* swapThis;
				while (removeThis->getLeft() != NULL && removeThis->getRight() != NULL) {
					for (int i = 0; i < 1; i++) {
						bool swapRoot;
						if (removeThis == root_) { //check if the node to be removed is also the root.
							swapRoot = true;
						}
						else {
							swapRoot = false;
						}
						if (removeThis->getRight() != NULL && removeThis->getLeft() == NULL) { //if there is only a right child, move it up
							swapThis = removeThis->getRight();
							moveUp(swapThis,removeThis);
						}
						else if (removeThis->getLeft() != NULL && removeThis->getRight() != NULL) { //if removeThis has 2 children, swap in its predecessor
							swapThis = predecessor(removeThis);
							nodeSwap(removeThis,swapThis);
						}
						else { //If node only has one left child, move it up
							swapThis = removeThis->getLeft();
							moveUp(swapThis,removeThis);
						}
						if (swapRoot == true) { //otherwise, if you need to swap root... set root to the node to be swapped in
							root_ = swapThis;
						}
					}
				}
				if (removeThis->getParent() == NULL) {/*do nothing*/}
				else if (removeThis == removeThis->getParent()->getRight()) { //if removeThis is the right child, delete it
					removeThis->getParent()->setRight(NULL);
				}
				else if (removeThis == removeThis->getParent()->getLeft()) { //if removeThis is the left child, delete it
					removeThis->getParent()->setLeft(NULL);
				}
				delete removeThis;
			}
		}
}



template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    Node<Key, Value>* p = current;
    if (p == NULL) { //if current is null, just return null.
        return p;
    }
    if (p->getLeft() == NULL) { //if there is no child, go up the chain until we are at a right child
        if (p->getLeft() == NULL) {
            while ( (p->getParent() != NULL) && (p->getParent()->getRight() != p) ) {
                p = p->getParent();
            }
						for (int i = 0; i < 1; i++) {
            	p = p->getParent();
						}
        }
    }
    else if (p->getLeft() != NULL) {//if there IS a left child, go to the rightmost child of this left child
        if (p->getLeft() != NULL) {
            Node<Key, Value>* a = p->getLeft();
            p = a;
            while (p->getRight() != NULL) {
                p = p->getRight();
            }
        }
    }
    return p;
}

template<typename Key, typename Value>
Node<Key,Value>*
BinarySearchTree<Key,Value>::successor(Node<Key,Value>* current) {
	Node<Key,Value>* next = current;
	if (next->getRight() == NULL) { //if right child doesn't exist, go back up the chain until you reach a node 
		Node<Key, Value>* up = next->getParent();
		while ( (next->getParent() != NULL) && (next == next->getParent()->getRight()) ) {
			next = up;
			up = up->getParent();
		}
		next = next->getParent();
	}
	else if (next->getRight() != NULL) { // if right child exists, go its leftmost child
		next = next->getRight(); 
		while (next->getLeft() != NULL) { //iteratively going down tree
			next = next->getLeft();
		}
	}
	return next;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* input) {
	if (input == NULL) {
		return;
	}
	for (int i = 0; i < 1; i++) {
		clearHelper(input->getLeft()); //initially go left until you hit a leftmost null child. 
		clearHelper(input->getRight()); //then go right until you hit a rightmost null child.
	}
	delete input; //delete on the way up.
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    this->clearHelper(root_);
    root_ = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if (root_ == NULL) {//base case
        return NULL;
    }
    Node<Key, Value>* smallestNode = root_;
    //smallest node will be on leftmost side of tree.
    //traverse down leftmost side of tree until end to find smallest node.
    if (smallestNode->getLeft() == NULL) { //if next left is empty, return current left
        return smallestNode;
    }
    else {
        while (smallestNode->getLeft() != NULL) {
            smallestNode = smallestNode->getLeft();
        }
        return smallestNode;
    }
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	Node<Key, Value>* p = this->root_;
	if (p == NULL) {
		return NULL;
	}
	else {
		while (p != NULL) {
			if ( key < p->getKey() ) {
				p = p->getLeft();
			}
			else if (key >= p->getKey()) {
				p = p->getRight();
			}
		}
		if ((p!= NULL) && (p->getKey() == key)) {
			return p;
		}
		else {
			return NULL;
		}
	}
}

template<typename Key,typename Value>
int BinarySearchTree<Key,Value>::balancedChecker(Node<Key,Value>* root) { //using my equalpaths code.
  if (root == NULL) return 0; //if root is empty
	if (root->getLeft() == NULL && root->getRight() == NULL) { //base case: leaf node
		return 1;
	}
	int leftH = -1;
	int rightH = -1;
	if (root->getLeft() != nullptr) { //if left exists
		leftH = balancedChecker(root->getLeft())+1; //find left height
	}
	if (root->getRight() != nullptr) { //if right exists
		rightH = balancedChecker(root->getRight())+1; //find right height
	}
	if (leftH <= rightH) { //if left is less than or equal to right
		return rightH; //send up right
	}
	else if (leftH > rightH) {
		return leftH;
	}
	return 0;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
  if (this->root_ == nullptr) { //base: if input node is empty
		return true;
	}
	if (this->root_->getLeft() == nullptr && this->root_->getRight() == nullptr) { //base case: whole tree has just one node
		return true;
	}
	Node<Key, Value>* temp = this->root_;
	int rightH = balancedChecker(temp->getLeft());
	int leftH = balancedChecker(temp->getRight());
	if ( (leftH == 0 && rightH == 1) || (leftH == 1 && rightH == 0) ) { //base case: tree is just one node with one leaf node (1 left OR 1 right)
		return true;
	}
	else {
		return (rightH == leftH); //Check if the heights of left and right are balanced.
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
