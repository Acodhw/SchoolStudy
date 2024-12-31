/*
* 작성자 : 2022112443 안치환
* 파일명 : main.cpp
* 기능설명 : Consumer 헤더파일 안에 있는 클래스 함수 작성
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Consumer.h"
#include <cstdlib>

Consumer::Consumer() { // 소비자의 생성자. 
	srand((unsigned int)time(NULL));
	int age = 8;
	for (int i = 0; i < 2; i++) {
		age += (rand() % 40);
	} //고객의 나이는 랜덤생성. 별도 관리로 나이를 지정할 수 없기 때문에 랜덤으로 생성한다
	this->age = age;
}

Consumer::Consumer(int age) { // 소비자의 생성자. 
	this->age = age;
}

bool Consumer::AgeCheck() { // 소비자가 청불 상품 구매가 가능한 나이인지 체크
	if (age >= 18) return true;
	return false; //18세 이상인지 체크
}

void Consumer::ChangeOrder(map<Product, int> order){ // 고객의 주문 변경
	buyedProduct = order;
}

map<Product, int> Consumer::GetOrder() { // 고객의 주문 확인
	return buyedProduct;
}