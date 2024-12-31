/*
* 파일명 : Consumer.h
* 기능설명 : 고객 클래스(상품 구매, 나이) 클래스 선언
*/

#include "Headoffice.h"
#include <ctime>

#ifndef CONS //헤더 파일이 한번만 선언되도록 하는 조건
#define CONS

class Consumer { // 상품을 구매하는 사람
private:
	int age; // 소비자의 나이. 나이 기준은 만. 청불 물품은 18살부터 구매 가능
	map<Product, int> buyedProduct; // 고객이 주문한 상품
public:
	Consumer(); // 소비자의 생성자. 
	Consumer(int age); // 소비자의 생성자. 나이 지정
	void ChangeOrder(map<Product, int> order); // 고객의 주문 변경
	map<Product, int> GetOrder(); // 고객의 주문 확인
	bool AgeCheck(); // 소비자가 청불 상품 구매가 가능한 나이인지 체크
};

#endif
