/*
* 파일 : MazeFind.cpp
* 설명 : 지도 탐색용 함수 정의
*/

#include "MazeFind.h"
#include <iostream>

FindingMaze::FindingMaze(int mazeMap[7][7]) {
	GraphQueue queue;	// 너비 우선 탐색을 위한 큐
	vector<Point> tmpvec;
	tmpvec.push_back(Point());// 우선으로 시작하기 위해 0,0을 큐에 집어넣는다
	queue.EnQueue(tmpvec);
	do  {		
		vector<Point> getPointVec = queue.DeQueue(); // 순차를 위해 큐에서 데큐한다
		Point endPoint = getPointVec.back(); // 가장 마지막 기준으로 마지막 좌표를 계산한다

		if (endPoint.x == 6 && endPoint.y == 6) {
			allRoute.push_back(getPointVec);
			continue;
		} // 좌표가 마지막 좌표라면 더 이상 진행할 필요가 없고 총 루트에 넣어준다.
		int i;
		
		if (endPoint.x > 0) {
			if (mazeMap[endPoint.x - 1][endPoint.y] == 0) { // 마지막 좌표 기준으로 x-1 방향에 벽이 있는가?
				i = endPoint.x - 1; // 전진한다
				if (find(getPointVec.begin(), getPointVec.end(), Point(i, endPoint.y)) == getPointVec.end()) { // 이미 지나온 길인지 판별
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(i, endPoint.y));
					queue.EnQueue(nextVec); // 지나온 길이 아니라면 리스트에 도착 좌표를 큐에 넣는다
				}
			}
		}
		if (endPoint.y > 0) {
			if (mazeMap[endPoint.x][endPoint.y - 1] == 0) {// 마지막 좌표 기준으로 y-1 방향에 벽이 있는가?
				i = endPoint.y - 1;
				if (find(getPointVec.begin(), getPointVec.end(), Point(endPoint.x, i)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(endPoint.x, i));
					queue.EnQueue(nextVec);// 위와 같다
				}
			}
		}
		if (endPoint.x < 6) {
			if (mazeMap[endPoint.x + 1][endPoint.y] == 0) {// 마지막 좌표 기준으로 x+1 방향에 벽이 있는가?
				i = endPoint.x + 1;;
				if (find(getPointVec.begin(), getPointVec.end(), Point(i, endPoint.y)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(i, endPoint.y));
					queue.EnQueue(nextVec);// 위와 같다
				}
			}
		}
		if (endPoint.y < 6) {
			if (mazeMap[endPoint.x][endPoint.y + 1] == 0) {// 마지막 좌표 기준으로 y+1 방향에 벽이 있는가?
				i = endPoint.y + 1;;
				if (find(getPointVec.begin(), getPointVec.end(), Point(endPoint.x, i)) == getPointVec.end()) {
					vector<Point> nextVec = getPointVec;
					nextVec.push_back(Point(endPoint.x, i));
					queue.EnQueue(nextVec);// 위와 같다
				}
			}
		}
	} while (!queue.isQueueEmpty());//큐 내부가 빌 때까지 진행

}

vector<vector<Point>> FindingMaze::ReturnRoute() {
	return allRoute; // 모든 루트 반환
}