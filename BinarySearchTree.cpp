#include "BinarySearchTree.hpp"
#include<cstring>
#include<iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;

BinarySearchTree::Node::Node(DataType newval)
{
	left = nullptr;
	right = nullptr;
	val = newval;
}

BinarySearchTree::BinarySearchTree()
{
	root_ = nullptr;
	size_ = 0;
}

// Call remove function to delete the root each time
BinarySearchTree::~BinarySearchTree()
{
//	while (root_ != nullptr)
//		remove(root_->val);
}

bool BinarySearchTree::insert(DataType val)
{
	Node *newNode = new Node(val);

	// check if empty
	if (size_ != 0)
	{
		Node *currentNode = root_;

		// while left or right are not null (exit if at leaf)
		while (currentNode->left != nullptr || currentNode->right != nullptr)
		{
			// go right
			if (val > currentNode->val)
			{
				// left subtree exists, but no right subtree
				if (currentNode->right == nullptr)
				{
					currentNode->right = newNode;
					size_++;
					return true;
				}
				currentNode = currentNode->right;
			}
			// go left
			else if (val < currentNode->val)
			{
				// right subtree exists, but no left subtree
				if (currentNode->left == nullptr)
				{
					currentNode->left = newNode;
					size_++;
					return true;
				}
				currentNode = currentNode->left;
			}
			else
				return false;
		}
		// insert right
		if (val > currentNode->val)
		{
			currentNode->right = newNode;
			size_++;
			return true;
		}
		// insert left
		else
		{
			currentNode->left = newNode;
			size_++;
			return true;
		}
	}
	root_ = newNode;
	size_++;
	return true;
}

bool BinarySearchTree::remove(DataType val)
{
	if (size_ != 0)
	{
		Node *currentNode = root_;
		Node *prevNode = nullptr;

		// locating the node we need to remove
		while (currentNode->val != val)
		{
			// go right
			if (val > currentNode->val && currentNode->right != nullptr)
			{
				prevNode = currentNode;
				currentNode = currentNode->right;
			}
			// go left
			else if (val < currentNode->val && currentNode->left != nullptr)
			{
				prevNode = currentNode;
				currentNode = currentNode->left;
			}
			// value does not exist in tree
			else
				return false;
		}
		// leaf node
		if (currentNode->left == nullptr && currentNode->right == nullptr)
		{
			// current Node is the root node
			if (currentNode == root_)
			{
				delete currentNode;
				delete root_;
				currentNode = nullptr;
				root_ = nullptr;
				size_--;
				return true;
			}
			delete currentNode;
			currentNode = nullptr;
			size_--;
			return true;
		}
		// one left child
		else if (currentNode->right == nullptr)
		{
			if (currentNode == root_)
			{
				root_ = root_->left;
				delete currentNode;
				currentNode = nullptr;
				size_--;
				return true;
			}
			else if (currentNode->left->val > prevNode->val)
				prevNode->right = currentNode->left;
			else
				prevNode->left = currentNode->left;

			delete currentNode;
			currentNode = nullptr;
			size_--;
			return true;
		}
		// one right child
		else if (currentNode->left == nullptr)
		{
			if (currentNode == root_)
			{
				root_ = root_->right;
				delete currentNode;
				currentNode = nullptr;
				size_--;
				return true;
			}
			else if (currentNode->right->val > prevNode->val)
				prevNode->right = currentNode->right;
			else
				prevNode->left = currentNode->right;

			delete currentNode;
			currentNode = nullptr;
			size_--;
			return true;
		}
		// two children (navigate right subtree to find lowest on right)
		else
		{
			if(currentNode->right != nullptr)
			{

			}
			Node *replaceNode = currentNode->right;
			DataType tempVal = 0;
			prevNode = nullptr;

			while (replaceNode -> left != nullptr)
			{
				prevNode = replaceNode;
				replaceNode = replaceNode->left;
			}
			// swap
			tempVal = currentNode->val;
			currentNode->val = replaceNode->val;
			replaceNode->val = tempVal;

			// check if the replaced node (with new value) has a right subtree for re-assigning pointers
			if (replaceNode->right != nullptr)
			{
				// prevNode was never set in the while loop
				if (prevNode == nullptr)
				{
					currentNode->right = replaceNode->right;
					delete replaceNode;
					replaceNode = nullptr;
					size_--;
					return true;
				}
				prevNode->left = replaceNode->right;
				delete replaceNode;
				replaceNode = nullptr;
				size_--;
				return true;
			}
			delete replaceNode;
			replaceNode = nullptr;
			size_--;
			return true;
		}
	}
	return false;
}

bool BinarySearchTree::exists(DataType val) const
{
	Node *currentNode = root_;

	while (currentNode != NULL)
	{
		// the current node is the one we've been looking for
		if (currentNode->val == val)
			return true;
		else if (currentNode->val < val)
		{
			currentNode = currentNode->left;
		}
		else
			currentNode = currentNode->right;
	}
	return false;
}

DataType BinarySearchTree::min() const
{
	Node *currentNode = root_;

	while(currentNode->left != nullptr)
		currentNode = currentNode->left;
	return currentNode->val;
}

DataType BinarySearchTree::max() const
{
	Node *currentNode = root_;

	while(currentNode->right != nullptr)
		currentNode = currentNode->right;
	return currentNode->val;
}

unsigned int BinarySearchTree::size() const
{
	return size_;
}

// call get node depth recursively here (depth is getNodeDepth(root_))
unsigned int BinarySearchTree::depth() const
{
	return getNodeDepth(root_);
}

// Level order traversal
void BinarySearchTree::print() const
{

}

int BinarySearchTree::getNodeDepth(Node* n) const
{
	if(n == nullptr)
		return -1;

	int leftMax = 0, rightMax = 0;

	leftMax = getNodeDepth(n->left);
	rightMax = getNodeDepth(n->right);

	if (leftMax <= rightMax)
		return rightMax + 1;
	else
		return leftMax + 1;
}
