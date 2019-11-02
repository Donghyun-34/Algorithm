/*
	���� ���� : ���� Ž�� Ʈ�� ����
	���� ��� : �赿��(akakak413@naver.com)
	���� ��¥ : 2019�� 11�� 02��
*/
#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

void print_menu() {
	cout << "\t\tmenu\n(0)\t����\n(1)\t����\n(2)\t����\n(3)\tŽ��\n(4)\t���(������ȸ)\n";
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
			cout << "�Է��ϰ��� �ϴ� Ű�� �Է��ϼ��� : ";
			cin >> data;
			bs.BSTInsert(&root, data);
			break;
		case 2:
			cout << "�����ϰ��� �ϴ� Ű�� �Է��ϼ��� : ";
			cin >> data;
			if (snode = bs.BSTRemove(&root, data)) {
				cout << data << "�� ���� ������ �����Ͽ����ϴ�.\n\n";
				free(snode);
			}
			else
				cout << "������ ���� ���߽��ϴ�.\n\n";
			break;
		case 3:
			cout << "Ž���ϰ��� �ϴ� Ű�� �Է��ϼ��� : ";
			cin >> data;
			if (snode = bs.search(root, data))
				cout << data << "�� Ž���ϴµ� �����Ͽ����ϴ�.\n\n";
			else
				cout << "�ش��ϴ� Ű�� �������� �ʽ��ϴ�.\n\n";
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