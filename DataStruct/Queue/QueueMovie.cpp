/*
* ���� : QueueMovie.cpp
* Ư¡ : Ŭ���� �Լ� ���� ����
* ���� : ť�� �ʿ��� �Լ��� �̸� ������
*/

#include <iostream>
#include "QueueMovie.h"

using std::cout;
using std::endl;

MovieProcess nullMP;

DLNode::DLNode(MovieProcess pro, DLNode* next = NULL) {
	process = pro;
	this->next = next;
}

//DLNode::~DLNode()

/*************************************Ŭ���� �Լ� ���м�******************************************/

MovieQueue::MovieQueue() {
	front = nullptr;
	rear = nullptr;
	count = 0;
}

bool MovieQueue::isQueueEmpty() {
	return (count == 0);
}

bool MovieQueue::EnQueue(MovieProcess data) {
	DLNode* node = new DLNode(data);
	if (isQueueEmpty()) {
		front = node;
		rear = node;
		count++;
		return true;
	}
	DLNode* Now = front;
	while (Now != nullptr) {
		if (Now->process.equals(data)) {
			cout << "������ �Էµ� �۾��� �ߺ��� �ڸ��� �۾��Դϴ�." << endl;
			return false;
		}
		Now = Now->next;
	}
	rear->next = node;
	rear = node;
	count++;
	return true;
}

MovieProcess MovieQueue::DeQueue() {
	if (isQueueEmpty()) {
		cout << "ť ���δ� ����ֽ��ϴ�." << endl;
		return nullMP;
	}
	
	DLNode* tmp = front;
	if (front->next == nullptr) {
		rear = nullptr;
		front = nullptr;
	}
	else front = front->next;
	MovieProcess tmpPro = tmp->process;
	count--;
	delete tmp;
	return tmpPro;
}

MovieProcess MovieQueue::Peek() {
	if (isQueueEmpty()) {
		cout << "ť ���δ� ����ֽ��ϴ�." << endl;
		return nullMP;
	}
	return rear->process;
}

/*void MovieQueue::PrintQueue() {
	if (isQueueEmpty()) {
		cout << "ť ���δ� ����ֽ��ϴ�." << endl;
		return;
	}
	cout << "head -> ";
	DLNode* Now = front;
	while (Now->next != nullptr) {
		cout << "{ " << Now->process.movie << ", " << Now->process.type << " } -> ";
		Now = Now->next;
	}

	cout << "{ " << Now->process.movie << ", " << Now->process.type << " } -> rear" << endl;
	
}*/