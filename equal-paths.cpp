#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int heightTrace(Node * root) { //helper function!
	if (root == nullptr) return 0; //if root is empty
	if (root->left == nullptr && root->right == nullptr) { //base case: leaf node
		return 1;
	}
	int leftH = -1;
	int rightH = -1;
	if (root->left != nullptr) { //if left exists
		leftH = heightTrace(root->left)+1; //find left height
	}
	if (root->right != nullptr) { //if right exists
		rightH = heightTrace(root->right)+1; //find right height
	}
	if (leftH <= rightH) { //if left is less than or equal to right
		return rightH; //send up right
	}
	else if (leftH > rightH) {
		return leftH;
	}
	return 0;
}

bool equalPaths(Node * root)
{
  if (root == nullptr) { //base: if input node is empty
		return true;
	}
	if (root->left == nullptr && root->right == nullptr) { //base case: whole tree has just one node
		return true;
	}
	int rightH = heightTrace(root->left);
	int leftH = heightTrace(root->right);
	if ( (leftH == 0 && rightH == 1) || (leftH == 1 && rightH == 0) ) { //base case: tree is just one node with one leaf node (1 left OR 1 right)
		return true;
	}
	else {
		return (rightH == leftH); //Check if the heights of left and right are balanced.
	}
}