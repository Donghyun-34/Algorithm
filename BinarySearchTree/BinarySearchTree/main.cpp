/*
	만든 목적 : 이진 탐색 트리 구현
	만든 사람 : 김동현(akakak413@naver.com)
	만든 날짜 : 2019년 11월 02일
*/
#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

void print_menu() {
	cout << "\t\tmenu\n(0)\t종료\n(1)\t삽입\n(2)\t삭제\n(3)\t탐색\n(4)\t출력(중위순회)\n";
}

int main() {
	BSTree bs;
	TreeNode* root = bs.GetRoot();
	TreeNode* snode;

	int count = 1, data=0;
	while (count>0) {
		print_menu();
		cin >> count;
		switch (count) {
		case 1:
			cout << "입력하고자 하는 키를 입력하세요 : ";
			cin >> data;
			bs.BSTInsert(&root, data);
			break;
		case 2:
			cout << "삭제하고자 하는 키를 입력하세요 : ";
			cin >> data;
			if (snode = bs.BSTRemove(&root, data)) {
				cout << data << "에 대한 삭제가 성공하였습니다.\n\n";
				free(snode);
			}
			else
				cout << "삭제를 하지 못했습니다.\n\n";
			break;
		case 3:
			cout << "탐색하고자 하는 키를 입력하세요 : ";
			cin >> data;
			if (snode = bs.search(root, data))
				cout << data << "를 탐색하는데 성공하였습니다.\n\n";
			else
				cout << "해당하는 키가 존재하지 않습니다.\n\n";
			break;
		case 4:
			cout << endl << endl;
			bs.InorderTraverse(root);
			break;
		default:
			break;
		}
	}
	return 0;
}