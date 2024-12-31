/*
* 파일 : QueueMovie.cpp
* 특징 : 클래스 함수 정의 파일
* 설명 : 큐에 필요한 함수를 미리 정의함
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

/*************************************클래스 함수 구분선******************************************/

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
			cout << "사전에 입력된 작업과 중복된 자리의 작업입니다." << endl;
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
		cout << "큐 내부는 비어있습니다." << endl;
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
		cout << "큐 내부는 비어있습니다." << endl;
		return nullMP;
	}
	return rear->process;
}

/*void MovieQueue::PrintQueue() {
	if (isQueueEmpty()) {
		cout << "큐 내부는 비어있습니다." << endl;
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