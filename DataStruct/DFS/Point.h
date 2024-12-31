/*
* 파일 : Point.h
* 설명 : 좌표 정보를 담는 구조체 선언
*/

#ifndef P
#define P

struct Point
{
	int x;
	int y;
	Point(int x = 0, int y = 0) { this->x = x; this->y = y; }
	bool operator==(const Point& p) const {
		return (x == p.x && y == p.y); //==연산자중복
	}
};

#endif // !Q
