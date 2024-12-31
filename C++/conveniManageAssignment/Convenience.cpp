/*
* 파일명 : main.cpp
* 기능설명 : Convenience 헤더파일 안에 있는 클래스 함수 작성
*/

#include <iostream>
#include "Convenience.h"

using std::cout;
using std::cin;
using std::endl;


// 판매자 클래스
Sellor::Sellor(string name) { // 가게 주인을 초기화
	this->name = name;
}

void Sellor::DisplayingProduct(Store* store) { // 상품을 진열한다
	map<Product, int>::iterator iter;
	bool isDisplayed = false;
	for (iter = store->displayedProduct.begin(); iter != store->displayedProduct.end(); ++iter) {
		if (store->storageProduct[iter->first] > 0 && iter->second < 10) {
			isDisplayed = true;
			int count = (store->storageProduct[iter->first] - iter->second > 10) ? (10 - iter->second) : (store->storageProduct[iter->first] - iter->second); //상품 진열 가능 최대 개수 10을 맞추기 위한 개수를 계산한다.
			iter->second += count;
			store->storageProduct[iter->first] -= count; // 저장에서는 빼고 진열대에는 더한다.
		}
	}
	if(isDisplayed)cout << "상품 진열 완료." << endl << endl;
	else { cout << "재고가 없거나 이미 완전히 진열되어 있어 상품을 진열할 수 없습니다." << endl << endl; } // 진열을 안했을 시 뜨는 메세지
}

//가게 상황 클래스
Store::Store(Sellor owner) { // 초기 가게 준비
	this->owner = owner;
	storageProduct.insert({ headOffice.GetProductList().at(0), 0 });
	storageProduct.insert({ headOffice.GetProductList().at(1), 0 });
	storageProduct.insert({ headOffice.GetProductList().at(2), 0 });
	storageProduct.insert({ headOffice.GetProductList().at(3), 0 });
	storageProduct.insert({ headOffice.GetProductList().at(4), 0 });

	displayedProduct.insert({ headOffice.GetProductList().at(0), 0 });
	displayedProduct.insert({ headOffice.GetProductList().at(1), 0 });
	displayedProduct.insert({ headOffice.GetProductList().at(2), 0 });
	displayedProduct.insert({ headOffice.GetProductList().at(3), 0 });
	displayedProduct.insert({ headOffice.GetProductList().at(4), 0 }); // 가게의 창고 상황 등을 모두 초기화함. 본사에서 얻어올 수 있는 상품을 이용해 map을 구성한다.

	revenue = 0;
}

void Store::TaxReturn(int& total){ // 정산
	int rev = revenue;
	revenue = 0;
	headOffice.ProfitDistribution(rev); // headoffice에 수익을 일부 준다.
	total += rev; // 총 수익을 더한다.
}

bool Store::Buy(Consumer consumer){ // 상품을 구매하는 클래스
	int totalPrice = 0;
	cout << "영수증" << endl;
	map<Product, int> ordered = consumer.GetOrder();
	map<Product, int>::iterator iter;
	for (iter = ordered.begin(); iter != ordered.end(); ++iter) {
		if (ordered[iter->first] <= 0) continue;
		std::cout << "상품명 : " << ((Product)iter->first).GetName() << ", 개수 : " << iter->second << ", 개당 가격 : " << ((Product)iter->first).GetPrice() << std::endl;
		totalPrice += ((Product)iter->first).GetPrice() * iter->second;

	} // 주문 내역 출력, 주문한 총 가격을 계산한다.
	if (totalPrice <= 0) return false; // 가격에 오류가 있을경우 오류로 간주
	cout << "총 " << totalPrice << "원 결제 되었습니다." << endl;
	revenue += totalPrice;
	return true;
}

bool Store::ReturningProduct(map<Product, int>* needReturn) { // 고객의 반품 요청
	while (true) {
		cout << endl;
		cout << "***************반품 선택***************" << endl;
		cout << " 1. " << headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << headOffice.GetProductList().at(4).GetName() << endl; // 반품 가능 품목을 headOffice에서 받아와서 리스트에 적는다
		cout << " 6. 반품 종료" << endl;
		cout << "**************************************" << endl;
		cout << "반품하고자 하는 물품 선택 >> ";
		int index;
		cin >> index;
		if (!index) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
		switch (index) // 1~5까지는 index가 구분하고, 다른 메뉴는 따로 구분하기 위한 switch case문
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			int count;
			cout << "구매 내역에서 개수 : " << (*needReturn)[headOffice.GetProductList().at(index - 1)] << endl;
			cout << endl << headOffice.GetProductList().at(index - 1).GetName() << " 몇 개를 반품할 것인가요? >> ";
			cin >> count;
			if (count <= 0) cout << "반품을 취소하였습니다." << endl << endl;
			else if (!count) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
			else if (count > (*needReturn)[headOffice.GetProductList().at(index - 1)]) cout << "판매된 것보다 많이 반품할 수 없습니다. 다시 시도해 주세요." << endl << endl; // 반품 개수를 체크
			else {
				(*needReturn)[headOffice.GetProductList().at(index - 1)] -= count;//반품 시 구매 내역을 직접 바꿔서 주소로 저장한다.
				revenue -= headOffice.GetProductList().at(index - 1).GetPrice() * count; //이익을 뺀다
				storageProduct[headOffice.GetProductList().at(index - 1)] += count; //반품한 상품을 다시 창고로 보관한다.
			}
			break;
		case 6:
			return true;
			break;
		default:
			cout << "확인되지 않은 메뉴 입력. 다시 입력해 주세요.\n\n" << endl;
			break;
		}
	}
	return true;
}



