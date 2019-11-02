#include <iostream>
#include "BinarySearchTree.h"
using namespace std;


int BSTree::GetData(TreeNode* bt) {
	return bt->key;
}

TreeNode* BSTree::GetLeftSubTree(TreeNode* bt) {
	return bt->left;
}

TreeNode* BSTree::GetRightSubTree(TreeNode* bt) {
	return bt->right;
}

void BSTree::MakeLeftSubTree(TreeNode* main, TreeNode* sub) {
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void BSTree::MakeRightSubTree(TreeNode* main, TreeNode* sub) {
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}

void BSTree::BSTInsert(TreeNode** root, int data) {
	TreeNode* pnode = NULL;//parent Node
	TreeNode* cnode = *root;//Current Node
	TreeNode* nnode = NULL;//New Node

	while (cnode != NULL) {
		if (data == GetData(cnode)) {// data�� �ߺ� �˻�
			cout << data << "�� �̹� �ԷµǾ� �ִ� key�� �Դϴ�.\n\n";
			return;
		}
		pnode = cnode;
		if (GetData(cnode) > data)
			cnode = GetLeftSubTree(cnode);
		else
			cnode = GetRightSubTree(cnode);
	}
	//pnode�� �ڽĳ��� �߰��� �� ��� ����
	nnode = new TreeNode(data);

	if (pnode != NULL) {
		if (data < GetData(pnode))
			MakeLeftSubTree(pnode, nnode);
		else
			MakeRightSubTree(pnode, nnode);
	}
	else// �� ��尡 ��Ʈ���
		*root = nnode;
}

TreeNode* BSTree::RemoveLeftSubTree(TreeNode* bt) {
	TreeNode* delnode=0;

	if (bt) {
		delnode = bt->left;
		bt->left = NULL;
	}
	return delnode;
}

TreeNode* BSTree::RemoveRightSubTree(TreeNode* bt) {
	TreeNode* delnode=0;

	if (bt) {
		delnode = bt->right;
		bt->right = NULL;
	}
	return delnode;
}

void BSTree::ChangeLeftSubTree(TreeNode* main, TreeNode* sub) {
	main->left = sub;
}

void BSTree::ChangeRightSubTree(TreeNode* main, TreeNode* sub) {
	main->right = sub;
}

TreeNode* BSTree::BSTRemove(TreeNode** root, int target) {
	TreeNode* vroot = new TreeNode();//���� ��Ʈ
	TreeNode* node = vroot;//parent node
	TreeNode* cnode = *root;//current node
	TreeNode* dnode;//delete node
	
	ChangeRightSubTree(vroot, *root);//��Ʈ ��带 vroot�� ����Ű�� ����� ������ �ڽ� ��尡 �ǰ� �ϴ� �κ�.

	while (cnode && GetData(cnode) != target) {//���� ����� �Ǵ� ��� Ž��
		node = cnode;
		if (target < GetData(cnode))
			cnode = GetLeftSubTree(cnode);
		else
			cnode = GetRightSubTree(cnode);
	}

	if (cnode == NULL)//���� ����� �������� ���� ���, NULL�� ��ȯ�ϰ� ����
		return NULL;

	dnode = cnode;//���� ��� ��带 dnode�� ����.

	if (GetLeftSubTree(dnode) && !GetRightSubTree(dnode)) {//ù��° ��� : ���� ����� �ܸ������ ���.
		if (GetLeftSubTree(node) == dnode)
			RemoveLeftSubTree(node);
		else
			RemoveRightSubTree(node);
	}

	else if (GetLeftSubTree(dnode) == NULL) {//�� ��° ��� : ���� ����� �ϳ��� �ڽ� ��带 ������ ���.
		TreeNode* dcnode;
		if (GetLeftSubTree(dnode) != NULL)
			dcnode = GetLeftSubTree(dnode);
		else
			dcnode = GetRightSubTree(dnode);

		if (GetLeftSubTree(node) == dnode)
			ChangeLeftSubTree(node, dcnode);
		else
			ChangeRightSubTree(node, dcnode);
	}

	else {//����° ��� : �ΰ��� �ڽ� ��带 ������ ���
		TreeNode* mnode = GetRightSubTree(dnode);//��ü ��� ���� ���� ����
		TreeNode* mpnode = dnode;//��ü ����� �θ��� ������� ����
		int deldata;

		while (GetLeftSubTree(mnode)) {//���� ����� ��ü ��� �˻�
			mpnode = mnode;
			mnode = GetLeftSubTree(mnode);
		}
		//��ü ����� ���� ������ ��忡 ����.
		deldata = GetData(dnode);// ������ ���
		dnode->key = mnode->key;
		//��ü ����� �θ� ���� �ڽ� ��� ����.
		if (GetLeftSubTree(mpnode) == mnode)
			ChangeLeftSubTree(mpnode, GetRightSubTree(mnode));
		else
			ChangeRightSubTree(mpnode, GetRightSubTree(mnode));

		dnode = mnode;
		dnode->key = deldata;
	}
	//��Ʈ ��带 �������� ��쿡 ���� �߰� ó��
	if (GetRightSubTree(vroot) != *root)
		*root = GetRightSubTree(vroot);

	free(vroot);
	return dnode;
}

TreeNode* BSTree::search(TreeNode* bt, int target) {
	TreeNode* cnode = bt;//current node
	int cd;//current data

	while (cnode != NULL) {
		cd = GetData(cnode);

		if (target == cd)
			return cnode;
		else if (target < cd)
			cnode = GetLeftSubTree(cnode);
		else
			cnode = GetRightSubTree(cnode);
	}
	return NULL;//Ž�� ����� ����Ǿ� ���� �ʴ´�.
}

void BSTree::InorderTraverse(TreeNode* bt) {
	if (bt==NULL)
		return;

	InorderTraverse(bt->left);
	cout << bt->key << endl;
	InorderTraverse(bt->right);
}