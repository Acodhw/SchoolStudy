/*
* ���� : GraphQueue.h
* ���� : �׷����� �ʺ� �켱 Ž���� �����ϱ� ���� �ʿ��� ť Ŭ���� ����
*/

#include "Point.h"
#include <vector>

using namespace std;

#ifndef Q
#define Q

class QNode {
private:
	vector<Point> data; // �̷� ���� ������ ��ǥ
	QNode* next;
public:
	QNode(vector<Point> dat, QNode* next = nullptr); // ��� ����
	friend class GraphQueue; // ť���� �ٷ�� ���ϵ��� ������ ����
};

class GraphQueue {
private :
	QNode* front;
	QNode* rear;
public :
	GraphQueue(); // ť �ʱ�ȭ
	bool isQueueEmpty(); // ť �������
	bool EnQueue(vector<Point> data); // ��� �߰�
	vector<Point> DeQueue(); // �տ��ִ°� ����
	vector<Point> Peek(); // �տ��ִ°�Ȯ��
};

#endif // !Q
