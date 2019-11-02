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
		if (data == GetData(cnode)) {// data의 중복 검사
			cout << data << "는 이미 입력되어 있는 key값 입니다.\n\n";
			return;
		}
		pnode = cnode;
		if (GetData(cnode) > data)
			cnode = GetLeftSubTree(cnode);
		else
			cnode = GetRightSubTree(cnode);
	}
	//pnode의 자식노드로 추가할 새 노드 생성
	nnode = new TreeNode(data);

	if (pnode != NULL) {
		if (data < GetData(pnode))
			MakeLeftSubTree(pnode, nnode);
		else
			MakeRightSubTree(pnode, nnode);
	}
	else// 새 노드가 루트라면
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
	TreeNode* vroot = new TreeNode();//가상 루트
	TreeNode* node = vroot;//parent node
	TreeNode* cnode = *root;//current node
	TreeNode* dnode;//delete node
	
	ChangeRightSubTree(vroot, *root);//루트 노드를 vroot가 가리키는 노드의 오른쪽 자식 노드가 되게 하는 부분.

	while (cnode && GetData(cnode) != target) {//삭제 대상이 되는 노드 탐색
		node = cnode;
		if (target < GetData(cnode))
			cnode = GetLeftSubTree(cnode);
		else
			cnode = GetRightSubTree(cnode);
	}

	if (cnode == NULL)//삭제 대상이 존재하지 않을 경우, NULL을 반환하고 종료
		return NULL;

	dnode = cnode;//삭제 대상 노드를 dnode에 저장.

	if (GetLeftSubTree(dnode) && !GetRightSubTree(dnode)) {//첫번째 경우 : 삭제 대상이 단말노드인 경우.
		if (GetLeftSubTree(node) == dnode)
			RemoveLeftSubTree(node);
		else
			RemoveRightSubTree(node);
	}

	else if (GetLeftSubTree(dnode) == NULL) {//두 번째 경우 : 삭제 대상이 하나의 자식 노드를 가지는 경우.
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

	else {//세번째 경우 : 두개의 자식 노드를 가지는 경우
		TreeNode* mnode = GetRightSubTree(dnode);//대체 노드 저장 공간 생성
		TreeNode* mpnode = dnode;//대체 노드의 부모노드 저장공간 생성
		int deldata;

		while (GetLeftSubTree(mnode)) {//삭제 대상의 대체 노드 검색
			mpnode = mnode;
			mnode = GetLeftSubTree(mnode);
		}
		//대체 노드의 값을 삭제할 노드에 대입.
		deldata = GetData(dnode);// 데이터 백업
		dnode->key = mnode->key;
		//대체 노드의 부모 노드와 자식 노드 연결.
		if (GetLeftSubTree(mpnode) == mnode)
			ChangeLeftSubTree(mpnode, GetRightSubTree(mnode));
		else
			ChangeRightSubTree(mpnode, GetRightSubTree(mnode));

		dnode = mnode;
		dnode->key = deldata;
	}
	//루트 노드를 삭제했을 경우에 대한 추가 처리
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
	return NULL;//탐색 대상이 저장되어 있지 않는다.
}

void BSTree::InorderTraverse(TreeNode* bt) {
	if (bt==NULL)
		return;

	InorderTraverse(bt->left);
	cout << bt->key << endl;
	InorderTraverse(bt->right);
}