/*
* 파일명 : Headoffice.h
* 기능설명 : 편의점 본사 기능(상품 주문, 수익 수수료 전달) 클래스 선언
*/

#include "Product.h"
#include <vector>
#include <map>

using std::map;
using std::vector;

#ifndef HEDO //헤더 파일이 한번만 선언되도록 하는 조건
#define HEDO

void CheckProductMap(map<Product, int> prods); // 상품 map을 확인하는 함수

class HeadOffice {
private:
	vector<Product> prodList; //본사가 베포하는 상품
	const int profitDistributionRatio = 30; //본사와 나누는 수익률
public:
	HeadOffice(); //본사의 상품 목록을 초기화
	vector<Product> GetProductList(); // 상품 목록을 받아오기
	void ProfitDistribution(int& profit); //수익은 본사와 이익분배
};

#endif
