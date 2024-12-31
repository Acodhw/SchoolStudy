/*
* 파일명 : Product.cpp
* 기능설명 : Product 헤더 파일 내의 클래스 함수 작성
*/

#include "Product.h"



Product::Product(string name, int price, bool isR18) { // 상품 내용 초기화
	this->productName = name;
	this->price = price;
	this->isR18 = isR18;
}

string Product::GetName() { // 상품 이름 받아오기
	return productName;
}

int Product::GetPrice() { // 상품 가격 받아오기
	return price;
}

bool Product::GetisR18() { // 상품이 청소년 판매금지인지 받아오기
	return isR18;
}

