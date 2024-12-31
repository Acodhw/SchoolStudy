/*
* ���� : MazeFind.cpp
* ���� : ���� Ž���� �Լ� ����
*/

#include "MazeFind.h"
#include <iostream>

FindingMaze::FindingMaze(int mazeMap[7][7]) {
	GraphQueue queue;	// �ʺ� �켱 Ž���� ���� ť
	vector<Point> tmpvec;
	tmpvec.push_back(Point());// �켱���� �����ϱ� ���� 0,0�� ť�� ����ִ´�
	queue.EnQueue(tmpvec);
	do  {		
		vector<Point> getPointVec = queue.DeQueue(); // ������ ���� ť���� ��ť�Ѵ�
		Point endPoint = getPointVec.back(); // ���� ������ �������� ������ ��ǥ�� ����Ѵ�

		if (endPoint.x == 6 && endPoint.y == 6) {
			allRoute.push_back(getPointVec);
			continue;
		} // ��ǥ�� ������ ��ǥ��� �� �̻� ������ �ʿ䰡 ���� �� ��Ʈ�� �־��ش�.
		int i;
		
		if (endPoint.x > 0) {
			if (mazeMap[endPoint.x - 1][endPoint.y] == 0) { // ������ ��ǥ �������� x-1 ���⿡ ���� �ִ°�?
				i = endPoint.x - 1; // �����Ѵ�
				if (find(getPointVec.begin(), getPointVec.end(), Point(i, endPoint.y)) == getPointVec.end()) { // �̹� ������ ������ �Ǻ�
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(i, endPoint.y));
					queue.EnQueue(nextVec); // ������ ���� �ƴ϶�� ����Ʈ�� ���� ��ǥ�� ť�� �ִ´�
				}
			}
		}
		if (endPoint.y > 0) {
			if (mazeMap[endPoint.x][endPoint.y - 1] == 0) {// ������ ��ǥ �������� y-1 ���⿡ ���� �ִ°�?
				i = endPoint.y - 1;
				if (find(getPointVec.begin(), getPointVec.end(), Point(endPoint.x, i)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(endPoint.x, i));
					queue.EnQueue(nextVec);// ���� ����
				}
			}
		}
		if (endPoint.x < 6) {
			if (mazeMap[endPoint.x + 1][endPoint.y] == 0) {// ������ ��ǥ �������� x+1 ���⿡ ���� �ִ°�?
				i = endPoint.x + 1;;
				if (find(getPointVec.begin(), getPointVec.end(), Point(i, endPoint.y)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(i, endPoint.y));
					queue.EnQueue(nextVec);// ���� ����
				}
			}
		}
		if (endPoint.y < 6) {
			if (mazeMap[endPoint.x][endPoint.y + 1] == 0) {// ������ ��ǥ �������� y+1 ���⿡ ���� �ִ°�?
				i = endPoint.y + 1;;
				if (find(getPointVec.begin(), getPointVec.end(), Point(endPoint.x, i)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(endPoint.x, i));
					queue.EnQueue(nextVec);// ���� ����
				}
			}
		}
	} while (!queue.isQueueEmpty());//ť ���ΰ� �� ������ ����

}

vector<vector<Point>> FindingMaze::ReturnRoute() {
	return allRoute; // ��� ��Ʈ ��ȯ
}