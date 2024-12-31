/*
* 작성자 : 2022112443 안치환
* 파일명 : product.h
* 기능설명 : 상품 클래스를 선언
*/

#include<iostream>
using std::string;


#ifndef PROD // 헤더 파일이 한번만 선언되도록 하는 조건
#define PROD

class Product {
private:
	string productName; // 상품 이름
	int price; // 상품 가격
	bool isR18; // 청소년이 살 수 없는 물건인지
public:
	Product(string name, int price = 0, bool isR18 = false); // 상품 내용 초기화
	string GetName(); // 상품 이름 받아오기
	int GetPrice(); // 상품 가격 받아오기
	bool GetisR18(); // 상품이 청소년 판매금지인지 받아오기

	bool operator<(const Product& i) const {
		return productName < i.productName;
	} // 정렬을 위한 연산자 중복
};

#endif
