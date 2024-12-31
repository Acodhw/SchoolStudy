/*
* 파일 : MazeFind.h
* 설명 : 지도 탐색용 클래스 선언 헤더파일
*/

#include "GraphQueue.h"


#ifndef MF
#define MF

class FindingMaze {
private:
	vector<vector<Point>> allRoute; // 모든 길 정보
public:
	FindingMaze(int mazeMap[7][7]); // 길찾기
	vector<vector<Point>> ReturnRoute(); // 길 리턴
};

#endif // !MF
