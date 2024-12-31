/*
* 파일 : GraphQueue.cpp
* 설명 : 너비 우선 탐색에 필요한 큐에 필요한 함수 정의
*/

#include <iostream>
#include "GraphQueue.h"

QNode::QNode(vector<Point> dat, QNode* next) {
	data = dat;
	this->next = next;
} // 노드 생성



GraphQueue::GraphQueue() {
	front = nullptr;
	rear = nullptr;
}// 큐 초기화

bool GraphQueue::isQueueEmpty() {
	return (front == nullptr && rear == nullptr);
}// 큐 비었는지

bool GraphQueue::EnQueue(vector<Point> data) {
	QNode* node = new QNode(data);
	if (isQueueEmpty()) { //큐가 비어있는지 확인
		front = node;
		rear = node;
		return true; //비어있을때는 front rear가 모두 노드를 가리킴
	}
	rear->next = node; //아닐경우 rear 뒤쪽으로 node를 붙임
	rear = node;
	return true;
}// 노드 추가

vector<Point> GraphQueue::DeQueue() {
	if (isQueueEmpty()) { //큐가 비어있는지 확인
		std::cout << "큐 내부는 비어있습니다." << std::endl;
		return vector<Point>();
	}

	QNode* tmp = front;
	if (front->next == nullptr) { //큐가 하나밖에 없으면 초기화
		rear = nullptr;
		front = nullptr;
	}
	else front = front->next; //아닐경우 front를 다음 노드로 변경
	vector<Point> tmpPro = tmp->data;
	delete tmp; //노드 반환
	return tmpPro; //데이터 리턴

}// 앞에있는거 빼기

vector<Point> GraphQueue::Peek() {
	if (isQueueEmpty()) { //큐가 비어있는지 확인
		std::cout << "큐 내부는 비어있습니다." << std::endl;
		return vector<Point>();
	}
	return front->data; //데이터 리턴
} // 앞에있는거확인
