/*
* ���� : GraphQueue.cpp
* ���� : �ʺ� �켱 Ž���� �ʿ��� ť�� �ʿ��� �Լ� ����
*/

#include <iostream>
#include "GraphQueue.h"

QNode::QNode(vector<Point> dat, QNode* next) {
	data = dat;
	this->next = next;
} // ��� ����



GraphQueue::GraphQueue() {
	front = nullptr;
	rear = nullptr;
}// ť �ʱ�ȭ

bool GraphQueue::isQueueEmpty() {
	return (front == nullptr && rear == nullptr);
}// ť �������

bool GraphQueue::EnQueue(vector<Point> data) {
	QNode* node = new QNode(data);
	if (isQueueEmpty()) { //ť�� ����ִ��� Ȯ��
		front = node;
		rear = node;
		return true; //����������� front rear�� ��� ��带 ����Ŵ
	}
	rear->next = node; //�ƴҰ�� rear �������� node�� ����
	rear = node;
	return true;
}// ��� �߰�

vector<Point> GraphQueue::DeQueue() {
	if (isQueueEmpty()) { //ť�� ����ִ��� Ȯ��
		std::cout << "ť ���δ� ����ֽ��ϴ�." << std::endl;
		return vector<Point>();
	}

	QNode* tmp = front;
	if (front->next == nullptr) { //ť�� �ϳ��ۿ� ������ �ʱ�ȭ
		rear = nullptr;
		front = nullptr;
	}
	else front = front->next; //�ƴҰ�� front�� ���� ���� ����
	vector<Point> tmpPro = tmp->data;
	delete tmp; //��� ��ȯ
	return tmpPro; //������ ����

}// �տ��ִ°� ����

vector<Point> GraphQueue::Peek() {
	if (isQueueEmpty()) { //ť�� ����ִ��� Ȯ��
		std::cout << "ť ���δ� ����ֽ��ϴ�." << std::endl;
		return vector<Point>();
	}
	return front->data; //������ ����
} // �տ��ִ°�Ȯ��
