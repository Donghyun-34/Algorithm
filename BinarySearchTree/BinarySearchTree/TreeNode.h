#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
class BSTree;

class TreeNode {
	friend class BSTree;
private:
	int key;
	TreeNode *left;
	TreeNode *right;
public:
	TreeNode(int data = 0, TreeNode * left = NULL, TreeNode *right = NULL) {
		key = data;
		this->left = left;
		this->right = right;
	}
};
#endif