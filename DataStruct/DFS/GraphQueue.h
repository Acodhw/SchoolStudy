/*
* 파일 : GraphQueue.h
* 설명 : 그래프의 너비 우선 탐색을 진행하기 위해 필요한 큐 클래스 선언
*/

#include "Point.h"
#include <vector>

using namespace std;

#ifndef Q
#define Q

class QNode {
private:
	vector<Point> data; // 미로 지도 정보의 좌표
	QNode* next;
public:
	QNode(vector<Point> dat, QNode* next = nullptr); // 노드 생성
	friend class GraphQueue; // 큐에서 다루기 편하도록 프랜드 선언
};

class GraphQueue {
private :
	QNode* front;
	QNode* rear;
public :
	GraphQueue(); // 큐 초기화
	bool isQueueEmpty(); // 큐 비었는지
	bool EnQueue(vector<Point> data); // 노드 추가
	vector<Point> DeQueue(); // 앞에있는거 빼기
	vector<Point> Peek(); // 앞에있는거확인
};

#endif // !Q
