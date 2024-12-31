/*
* ���� : Point.h
* ���� : ��ǥ ������ ��� ����ü ����
*/

#ifndef P
#define P

struct Point
{
	int x;
	int y;
	Point(int x = 0, int y = 0) { this->x = x; this->y = y; }
	bool operator==(const Point& p) const {
		return (x == p.x && y == p.y); //==�������ߺ�
	}
};

#endif // !Q
