/*
* ���� : QueueMovie.h
* Ư¡ : ��� ����
* ���� : ť�� �ʿ��� ������ �̸� ����
*/

#include "Movie.h"

#ifndef QM
#define QM

class DLNode {
private:
	MovieProcess process;
	DLNode* next;
public:
	DLNode(MovieProcess pro, DLNode* next);
	//~DLNode();
	friend class MovieQueue;
};

class MovieQueue {
private:
	DLNode* front;
	DLNode* rear;
public:
	int count;
	MovieQueue();
	bool isQueueEmpty();
	bool EnQueue(MovieProcess data);
	MovieProcess DeQueue();
	MovieProcess Peek();
	//void PrintQueue();
};


#endif // !QM
