#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "TreeNode.h"
class BSTree {
private:
	TreeNode* root;
public:
	BSTree() {
		root = NULL;
	}
	TreeNode* GetRoot() {
		return root;
	}
	void BSTInsert(TreeNode** root, int data);
	TreeNode* BSTRemove(TreeNode** root, int target);
	TreeNode* RemoveLeftSubTree(TreeNode* bt);
	TreeNode* RemoveRightSubTree(TreeNode* bt);
	void ChangeLeftSubTree(TreeNode* main, TreeNode* sub);
	void ChangeRightSubTree(TreeNode* main, TreeNode* sub);
	TreeNode* search(TreeNode* bs, int target);
	int GetData(TreeNode* bt);
	TreeNode* GetLeftSubTree(TreeNode* bt);
	TreeNode* GetRightSubTree(TreeNode* bt);
	void MakeLeftSubTree(TreeNode* main, TreeNode* sub);
	void MakeRightSubTree(TreeNode* main, TreeNode* sub);
	void InorderTraverse(TreeNode* bt);
};
#endif