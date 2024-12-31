/*
* 작성자 : 2022112443 안치환
* 파일명 : Coinvenience.h
* 기능설명 : 편의점 주인(판매자)과 편의점 관리 프로그램에 필요한 클래스 선언
*/

#include "Headoffice.h"
#include "Consumer.h"


#ifndef CONV //헤더 파일이 한번만 선언되도록 하는 조건
#define CONV

class Store;

class Sellor { // 판매자 클래스
private:
	string name; // 판매자의 이름
public:
	Sellor(string name = ""); // 가게 주인을 초기화
	void DisplayingProduct(Store* store); // 상품을 진열
	string GetName() { return name; }; // 이름 얻어오기
};

class Store { //가게 상황(재고, 수익 등)을 가진 클래스
private:
	Sellor owner; // 주인 지정
	HeadOffice headOffice; // 지정된 본사
	map<Product, int> displayedProduct; // 진열된 상품 수를 넣은 map
	map<Product, int> storageProduct; // 창고에 보관 중인 상품 수를 넣은 map
	int revenue; // 총 수익
public:
	friend class Sellor; // 정리를 위한 프랜드 선언
	friend class ConvenManager; // 관리를 위한 정보 공유를 위한 프랜드 선언
	Store(Sellor owner); // 초기 가게 준비(오버로딩)
	bool Buy(Consumer consumer); // 고객의 구매 요청
	bool ReturningProduct(map<Product, int>* needReturn); // 고객의 반품 요청
	void TaxReturn(int& total); // 정산
};

#endif
