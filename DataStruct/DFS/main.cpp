/*
* 파일 : main.cpp
* 설명 : 미로 맵을 입력받고, 출력한다.
*/

#include <iostream>
#include "MazeFind.h"

using namespace std;

int main() {
	int mazeMap[7][7];

	cout << "지도 맵 입력(사이즈 : 7x7)" << endl;
	cout << "EX) " << endl;
	cout << "0 0 0 0 0 0 0" << endl;
	cout << "0 1 1 1 1 1 0" << endl;
	cout << "0 0 0 1 0 0 0" << endl;
	cout << "1 1 0 1 0 1 1" << endl;
	cout << "1 1 0 0 0 0 1" << endl;
	cout << "1 1 0 1 1 0 0" << endl;
	cout << "1 0 0 0 0 0 0" << endl;
	cout << "왼쪽 위 끝과 오른쪽 아래 끝은 각각 자동으로 출발 - 도착으로 지정됨" << endl;
	cout << "1은 벽, 0은 통로" << endl;
	cout << "입력 시작" << endl;
	
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cin >> mazeMap[i][j];
		}
	}// 지도 맵 입력받기
	mazeMap[0][0] = 0;
	mazeMap[6][6] = 0; // 처음과 끝은 진행 가능해야 하므로 통로인 0으로 변환

	cout << "지도 맵 입력이 완료되었습니다. 지도를 푸는 모든 경로를 탐색합니다." << endl << endl;
	for (int i = 0; i < 8; i++) {
		if (i > 0) cout << (char)('A' + i - 1) << ". ";
		else cout << "   ";
		for (int j = 0; j < 7; j++) {
			if (i == 0) cout << j + 1 << " ";
			else cout << mazeMap[i - 1][j] << " ";
		}
		cout << endl;
	} // 경로에 표시할 좌표를 보여주기 위해 지도 맵을 다시 출력한다
	cout << endl;
	cout << "다음과 같은 미로 맵에서 미로를 탈출하는 방법" << endl;
	FindingMaze fm(mazeMap);
	vector<vector<Point>> Route = fm.ReturnRoute();

	if (Route.size() <= 0) {
		cout << endl << "경로가 존재하지 않습니다" << endl;
		return 0;
	} // 탈출 경로가 없는 지도인지 구별

	cout << endl << "이동 경로의 모든 좌표" << endl;
	for (int i = 0; i < Route.size(); i++) {
		cout << "경로 " << i + 1 << " : ";
		for (int j = 0; j < Route.at(i).size(); j++) {
			cout << "(" << (char)(Route.at(i).at(j).x + 'A') << ", " << Route.at(i).at(j).y + 1 << ") -> ";
		}
		cout << "도착" << endl;
	} // 모든 이동 좌표를 출력한다

	cout << endl << "방향과 갈림길로 표시한 좌표" << endl;
	for (int i = 0; i < Route.size(); i++) {
		cout << "경로 " << i + 1 << " : ";
		bool directionPrint = false; // 방향이 여러번 출력됨을 막는 bool
		for (int j = 0; j < Route.at(i).size(); j++) {
			Point nextDirection(0, 0);
			Point prevDirection(0, 0);
			if (j < Route.at(i).size() - 1) {
				nextDirection.x = Route.at(i).at(j + 1).x - Route.at(i).at(j).x;
				nextDirection.y = Route.at(i).at(j + 1).y - Route.at(i).at(j).y;
			} // 이 좌표의 다음 방향을 대입한다
			if (j > 0) {
				prevDirection.x = Route.at(i).at(j).x - Route.at(i).at(j - 1).x; 
				prevDirection.y = Route.at(i).at(j).y - Route.at(i).at(j - 1).y;
			} // 이 좌표의 이전 방향을 대입한다
			if (nextDirection == prevDirection && !directionPrint) { // 갈림길, 꺽이는 길이 아니고 방향을 출력하지 않았을 경우
				if(prevDirection == Point(-1,0))cout << "위쪽 -> ";
				else if (prevDirection == Point(0, 1))cout << "오른쪽 -> ";
				else if (prevDirection == Point(1, 0))cout << "아래쪽 -> ";
				else if (prevDirection == Point(0, -1))cout << "왼쪽 -> "; // x, y가 각각 행, 열임을 파악하여 방향을 구별하고, 이를 출력한다
				directionPrint = true;
			}
			else if(!(nextDirection == prevDirection) && !(Route.at(i).at(j) == Point(6,6))) { // 갈림길, 꺽이는 길일때
				cout << "(" << (char)(Route.at(i).at(j).x + 'A') << ", " << Route.at(i).at(j).y + 1 << ") -> ";
				directionPrint = false;
			}
		}
		cout << "(G, 7) -> 도착" << endl;
	}

	return 0;
}