/*
* 파일 : QueueMovie.h
* 특징 : 헤더 파일
* 설명 : 큐에 필요한 내용을 미리 선언
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
