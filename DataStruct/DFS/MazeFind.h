/*
* ���� : MazeFind.h
* ���� : ���� Ž���� Ŭ���� ���� �������
*/

#include "GraphQueue.h"


#ifndef MF
#define MF

class FindingMaze {
private:
	vector<vector<Point>> allRoute; // ��� �� ����
public:
	FindingMaze(int mazeMap[7][7]); // ��ã��
	vector<vector<Point>> ReturnRoute(); // �� ����
};

#endif // !MF
