#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    void rotationFix(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2, AVLNode<Key,Value>* n3);
    void rotateLeft(AVLNode<Key,Value>* n1);
    void rotateRight(AVLNode<Key,Value>* n1);
    void removeFix(AVLNode<Key,Value>* current);



};

template<typename Key,typename Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* current) {
    AVLNode<Key,Value>* parent = current->getParent();
    AVLNode<Key, Value>* right = current->getRight();
    if (current == this->root_) {
        this->root_ = right;
    }
    AVLNode<Key,Value>* tempRotate;
    if (right == NULL) {
        return;
    }
    if (right->getLeft() == NULL) {
        tempRotate = NULL;
    }
    else {
        tempRotate = right->getLeft();
    }
    for (int i = 0; i < 1; i++) {
        current->setRight(tempRotate);
        current->setParent(right);
    }
    for (int i = 0; i < 1; i++) {
        right->setParent(parent);
        right->setLeft(current);
    }
    if (parent != NULL) {
        if (parent->getRight() == current) {
            parent->setLeft(right);
        }
        else if (parent->getLeft() == current) {
            parent->setRight(right);
        }
    }
    if (tempRotate == NULL) {
        // do nothing
    }
    else if (tempRotate != NULL) {
        tempRotate->setParent(current);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* current) {
    //Not done in time.
}

template<class Key,class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* current) {
    AVLNode<Key,Value>* parent = current->getParent();
    AVLNode<Key, Value>* left = current->getLeft();
    if (current == this->root_) {
        this->root_ = left;
    }
    AVLNode<Key,Value>* tempRotate;
    if (left == NULL) {
        return;
    }
    if (left->getRight() == NULL) {
        tempRotate = NULL;
    }
    else {
        tempRotate = left->getLeft();
    }
    for (int i = 0; i < 1; i++) {
        current->setLeft(tempRotate);
        current->setParent(left);
    }
    for (int i = 0; i < 1; i++) {
        left->setParent(parent);
        left->setRight(current);
    }
    if (parent != NULL) {
        for (int i = 0; i < 1; i++) {
            if (parent->getRight() == current) {
                parent->setRight(left);
            }
            else if (parent->getLeft() == current) {
                parent->setLeft(left);
            }
        }
    }
    if (tempRotate == NULL) {
        // do nothing
    }
    else if (tempRotate != NULL) {
        tempRotate->setParent(current);
    }
}

template<typename Key,typename Value>
void AVLTree<Key, Value>::rotationFix(AVLNode<Key,Value>* current, AVLNode<Key,Value>* parent, AVLNode<Key,Value>* leaf) {
    /*CASES:
    Needs left-right rotation, which has initial arrangement
       current 
      / 
     parent
      \ 
       leaf
    Then needs right-left rotation, which has initial arrangement
        parent
         \ 
          current
         /
        leaf
    Or needs left-left
        parent
           \ 
            current
              \ 
              leaf
     OR needs right-right
          parent 
            /
       current
         /
       leaf */
    if (current == parent->getLeft() && leaf == current->getRight()) { //left,then right rotation
        rotateLeft(current);
        rotateRight(parent);
        leaf->setBalance(0);
    }
    else if (current == parent->getRight() && leaf == current->getLeft()) { //right-left
        rotateRight(current);
        rotateLeft(parent);
        leaf->setBalance(0);
    }
    else if (current == parent->getRight() && leaf == current->getRight()) { //right
        rotateLeft(parent);
        parent->setBalance(0);
        current->setBalance(0);
    }
    else {
        rotateRight(parent);
        parent->setBalance(0);
        current->setBalance(0);
    }
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* current, AVLNode<Key,Value>* fixedNode) {
    //base case: current is null OR current's parent doesn't exist.
    //in order to avoid bad access.
    if (current == NULL || current->getParent() == NULL) {
        return;
    }
    else {
        AVLNode<Key,Value>* parent = current->getParent();
        if (current != parent->getLeft()) {
            parent->updateBalance(1);
        }
        else {
            parent->updateBalance(-1);
        }
        if (parent->getBalance() == 0) { //if node is balanced, just return.
            return;
        }
        if (parent->getBalance() != 0) {
            insertFix(parent,current);
        }
        else {
            rotationFix(current,parent,fixedNode);
        }
    }

}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{ //modifying code used in bst for use with avl
    Value operativeValue = new_item.second;
    Key operativeKey = new_item.first;

    if (this->root_ == NULL){
        AVLNode<Key,Value>* temp = new AVLNode<Key,Value>(operativeKey,operativeValue,NULL);
        if (this->empty()) { //New tree! set balance to 0.
            temp->setBalance(0);
            this->root_ = temp;
        }
        return;
    }
    else {
        AVLNode<Key,Value>* operativeRoot = static_cast<AVLNode<Key, Value>*>(this->root_); //avoid working directly with data member pointer
        AVLNode<Key,Value>* opNode = new AVLNode<Key,Value>(operativeKey,operativeValue,operativeRoot);
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
                    if (NULL == operativeRoot->getRight()) {
                        operativeRoot->setRight(opNode);
                        operativeRoot->updateBalance(1);
                    }
                }
                operativeRoot = operativeRoot->getRight(); //move up right child
            }
            else if (operativeKey < focusKey) { //if key is less than current key, move left
                for (int i = 0; i < 1; i++) {
                    if (NULL == operativeRoot->getLeft()) { 
                        operativeRoot->setLeft(opNode);
                        operativeRoot->updateBalance(-1);
                    }
                }
                operativeRoot = operativeRoot->getLeft(); //move up left child
            }
        }
        if (operativeRoot->getBalance() == 0) {
            //no need for action.
            return;
        }
        else {
            insertFix(operativeRoot,opNode);
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
