/*
* 작성자 : 2022112443 안치환
* 파일명 : main.cpp
* 기능설명 : Headoffice 헤더파일 안에 있는 클래스 함수 작성
*/

#include <iostream>
#include <fstream>
#include "Headoffice.h"

HeadOffice::HeadOffice() { //본사의 상품 목록을 초기화
	prodList.clear();
	prodList.push_back(Product("컵라면", 1100));
	prodList.push_back(Product("핫바", 900));
	prodList.push_back(Product("삼각김밥", 1100));
	prodList.push_back(Product("햄버거", 2000));
	prodList.push_back(Product("소주", 2000, true)); //상품 목록을 지정
}

vector<Product> HeadOffice::GetProductList() { // 상품 목록을 받아오기
	return prodList;
}

void HeadOffice::ProfitDistribution(int& profit) { //수익은 본사와 이익분배
	if(profit >= 0) profit = (int)(profit - (profit * 0.3));
}

void CheckProductMap(map<Product, int> prods) { // 상품 map을 확인하는 함수
	map<Product, int>::iterator iter;
	for (iter = prods.begin(); iter != prods.end(); ++iter) {
		std::cout << "상품명 : " << ((Product)iter->first).GetName() << ", 개수 : " << iter->second << std::endl; //map 형태로 불러와진 상품 map을 돌아가며 확인하여 출력
	}
}