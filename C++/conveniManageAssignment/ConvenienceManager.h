/*
* 파일명 : CoinvenienceManager.h
* 기능설명 : 최종 관리를 위한 클래스 선언 파일
*/

#include "Convenience.h"
#include "Consumer.h"
#include <ctime>

#define MINIMUM_WAGE 9000 // 최저시급

#ifndef MANAGE //헤더 파일이 한번만 선언되도록 하는 조건
#define MANAGE

class ConvenManager {
private:
	time_t timeNow; // 시간 저장
	int totalRevenue; // 총 수익. 현재 편의점의 이익 상황을 나타낸다. -는 적자인 상황, +는 흑자인 상황
	Store * store; // 연계된 가게
	bool LoadToday(); // 지난번에 저장된 편의점 상황을 로드하여 시작한다.
	bool SaveToday(); // 오늘 편의점 상황을 저장한다
	vector<map<Product, int>> ordering; //고객의 주문 목록
	vector<map<Product, int>> storing; //입고 목록
public:
	ConvenManager(); // 생성자. 매니저 프로그램 시작 설정
	~ConvenManager(); // 소멸자. 매니저 프로그램 종료
	void CheckNow(); // 현재 편의점 상황을 체크한다
	void Displaying(); // 진열
	void OrderingToHead(); // 본사에 입고 요청을 한다
	
	void OrderCustomer(); // 고객의 주문 요청
	void ReturnCustomer(); // 고객의 반품 요청

	void TaxReturning(); // 지금까지 내역을 정산한 후 저장한다
};

#endif
