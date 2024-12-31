/*
* ���� : main.cpp
* ���� : �̷� ���� �Է¹ް�, ����Ѵ�.
*/

#include <iostream>
#include "MazeFind.h"

using namespace std;

int main() {
	int mazeMap[7][7];

	cout << "���� �� �Է�(������ : 7x7)" << endl;
	cout << "EX) " << endl;
	cout << "0 0 0 0 0 0 0" << endl;
	cout << "0 1 1 1 1 1 0" << endl;
	cout << "0 0 0 1 0 0 0" << endl;
	cout << "1 1 0 1 0 1 1" << endl;
	cout << "1 1 0 0 0 0 1" << endl;
	cout << "1 1 0 1 1 0 0" << endl;
	cout << "1 0 0 0 0 0 0" << endl;
	cout << "���� �� ���� ������ �Ʒ� ���� ���� �ڵ����� ��� - �������� ������" << endl;
	cout << "1�� ��, 0�� ���" << endl;
	cout << "�Է� ����" << endl;
	
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			cin >> mazeMap[i][j];
		}
	}// ���� �� �Է¹ޱ�
	mazeMap[0][0] = 0;
	mazeMap[6][6] = 0; // ó���� ���� ���� �����ؾ� �ϹǷ� ����� 0���� ��ȯ

	cout << "���� �� �Է��� �Ϸ�Ǿ����ϴ�. ������ Ǫ�� ��� ��θ� Ž���մϴ�." << endl << endl;
	for (int i = 0; i < 8; i++) {
		if (i > 0) cout << (char)('A' + i - 1) << ". ";
		else cout << "   ";
		for (int j = 0; j < 7; j++) {
			if (i == 0) cout << j + 1 << " ";
			else cout << mazeMap[i - 1][j] << " ";
		}
		cout << endl;
	} // ��ο� ǥ���� ��ǥ�� �����ֱ� ���� ���� ���� �ٽ� ����Ѵ�
	cout << endl;
	cout << "������ ���� �̷� �ʿ��� �̷θ� Ż���ϴ� ���" << endl;
	FindingMaze fm(mazeMap);
	vector<vector<Point>> Route = fm.ReturnRoute();

	if (Route.size() <= 0) {
		cout << endl << "��ΰ� �������� �ʽ��ϴ�" << endl;
		return 0;
	} // Ż�� ��ΰ� ���� �������� ����

	cout << endl << "�̵� ����� ��� ��ǥ" << endl;
	for (int i = 0; i < Route.size(); i++) {
		cout << "��� " << i + 1 << " : ";
		for (int j = 0; j < Route.at(i).size(); j++) {
			cout << "(" << (char)(Route.at(i).at(j).x + 'A') << ", " << Route.at(i).at(j).y + 1 << ") -> ";
		}
		cout << "����" << endl;
	} // ��� �̵� ��ǥ�� ����Ѵ�

	cout << endl << "����� ������� ǥ���� ��ǥ" << endl;
	for (int i = 0; i < Route.size(); i++) {
		cout << "��� " << i + 1 << " : ";
		bool directionPrint = false; // ������ ������ ��µ��� ���� bool
		for (int j = 0; j < Route.at(i).size(); j++) {
			Point nextDirection(0, 0);
			Point prevDirection(0, 0);
			if (j < Route.at(i).size() - 1) {
				nextDirection.x = Route.at(i).at(j + 1).x - Route.at(i).at(j).x;
				nextDirection.y = Route.at(i).at(j + 1).y - Route.at(i).at(j).y;
			} // �� ��ǥ�� ���� ������ �����Ѵ�
			if (j > 0) {
				prevDirection.x = Route.at(i).at(j).x - Route.at(i).at(j - 1).x; 
				prevDirection.y = Route.at(i).at(j).y - Route.at(i).at(j - 1).y;
			} // �� ��ǥ�� ���� ������ �����Ѵ�
			if (nextDirection == prevDirection && !directionPrint) { // ������, ���̴� ���� �ƴϰ� ������ ������� �ʾ��� ���
				if(prevDirection == Point(-1,0))cout << "���� -> ";
				else if (prevDirection == Point(0, 1))cout << "������ -> ";
				else if (prevDirection == Point(1, 0))cout << "�Ʒ��� -> ";
				else if (prevDirection == Point(0, -1))cout << "���� -> "; // x, y�� ���� ��, ������ �ľ��Ͽ� ������ �����ϰ�, �̸� ����Ѵ�
				directionPrint = true;
			}
			else if(!(nextDirection == prevDirection) && !(Route.at(i).at(j) == Point(6,6))) { // ������, ���̴� ���϶�
				cout << "(" << (char)(Route.at(i).at(j).x + 'A') << ", " << Route.at(i).at(j).y + 1 << ") -> ";
				directionPrint = false;
			}
		}
		cout << "(G, 7) -> ����" << endl;
	}

	return 0;
}