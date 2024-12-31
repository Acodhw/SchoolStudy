/*
* 작성자 : 2022112443 안치환
* 파일명 : main.cpp
* 기능설명 : ConvenienceManager 헤더파일 안에 있는 클래스 함수 작성
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "ConvenienceManager.h"

using std::cout;
using std::cin;
using std::endl;

ConvenManager::ConvenManager() { // 생성자. 매니저 프로그램 시작 설정
	cout << "편의점 관리 프로그램을 시작합니다." << endl;
	if (LoadToday()) {  	
		time(&timeNow);
		return;
	} // 저장된 데이터가 있다면 불러온다. 다만 시간은 오늘로 맞춘다.
	cout << "저장된 데이터가 없어 새로 데이터를 만듭니다." << endl; //저장된 데이터가 없다면 시작된다
	string name = "";
	while (name == "") {
		cout << "당신의 이름은? >> "; //이름 받아오기
		cin >> name;
	}
	store = new Store(Sellor(name)); //Store 클래스 동적할당. 이 store 객체가 우리가 관리할 편의점의 객체이다.
	cout << name << "님으로 편의점 관리 프로그램을 시작합니다.\n\n\n\n" << endl;
	time(&timeNow); // 현재 시간을 구한다.
	totalRevenue = 0;
	SaveToday(); // 다시 열때 이 과정을 반복하지 않도록 우선 파일로 저장한다.
}

ConvenManager::~ConvenManager() { // 소멸자. 매니저 프로그램 종료
	TaxReturning();// 나가기 전 정산
	cout << "프로그램을 종료하였습니다." << endl;
	delete store;
}


void ConvenManager::CheckNow() { // 현재 편의점 상황을 체크한다
	cout << endl << endl;
	struct tm* date = localtime(&timeNow);
	cout << "관리 날짜 : " << date->tm_year + 1900 << "-" << date->tm_mon + 1 << "-" << date->tm_mday << endl;
	cout << "관리인(판매자) : " << store->owner.GetName() << endl << endl; // 날짜와 관리인 출력

	cout << "현 총수익 : " << totalRevenue << endl << endl; // 날짜와 관리인 출력

	cout << "진열된 물품 : " << endl;
	CheckProductMap(store->displayedProduct);

	cout  << endl;

	cout << "보관된 물품 : " << endl;
	CheckProductMap(store->storageProduct);
	cout << endl << endl;
}

void ConvenManager::OrderingToHead() { // 본사에 입고 요청을 한다
	cout << endl << endl;
	map<Product, int> prods;
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // prods를 관리하기 쉽게 미리 목록을 insert해놓는다.
	bool ordering = true; // 주문이 끝났는지 체크하기
	while (ordering) {
		cout << endl;
		cout << "********입고 신청하기(물품 선택)********" << endl;
		cout << " 1. " << store->headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << store->headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << store->headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << store->headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << store->headOffice.GetProductList().at(4).GetName() << endl; // 입고 신청 물품을 headOffice에서 받아와서 리스트에 적는다
		cout << " 6. 입고 신청 종료" << endl;
		cout << "**************************************" << endl;
		cout << "주문하고자 하는 물품 선택 >> ";
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
			cout << endl << store->headOffice.GetProductList().at(index - 1).GetName() << " 상품을 몇 개 주문하시겠습니까? >> ";
			cin >> count;
			if (count <= 0) cout << "주문을 취소하였습니다." << endl << endl;
			else if (!count) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
			else {
				prods[store->headOffice.GetProductList().at(index - 1)] += count;
			}
			break;
		case 6:
			cout << "다음과 같은 주문을 받아 창고에 입고하였습니다." << endl << endl;
			CheckProductMap(prods);
			ordering = false;
			break;
		default:
			cout << "확인되지 않은 메뉴 입력. 다시 입력해 주세요.\n\n" << endl;
			break;
		}

	}
	map<Product, int>::iterator iter;
	for (iter = prods.begin(); iter != prods.end(); ++iter) {
		store->storageProduct[iter->first] += iter->second;
	} // 주문한 상품을 storageProduct,즉 상품 구매에 더한다.
	storing.push_back(prods); //입고 상황을 기록한다.
	cout << endl << endl;
}


void ConvenManager::Displaying() {// 진열
	store->owner.DisplayingProduct(store);
}

void ConvenManager::OrderCustomer() { // 고객의 주문 요청
	Consumer con;
	cout << endl << endl;
	map<Product, int> prods; // 입고 요청을 할 상품 리스트
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // prods를 관리하기 쉽게 미리 목록을 insert해놓는다.
	bool ordering = true;
	while (ordering) {
		cout << endl;
		cout << "***************주문 받기***************" << endl;
		cout << " 1. " << store->headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << store->headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << store->headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << store->headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << store->headOffice.GetProductList().at(4).GetName() << endl; // 구매 가능 품목을 headOffice에서 받아와서 리스트에 적는다
		cout << " 6. 결제 시작" << endl;
		cout << " 7. 결제 취소" << endl;
		cout << "**************************************" << endl;
		cout << "주문하고자 하는 물품 선택 >> ";
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
			if (store->headOffice.GetProductList().at(index - 1).GetisR18() && !con.AgeCheck()) {
				cout << "청소년은 구입할 수 없는 품목입니다." << endl << endl;
				break;
			}
			int count;
			cout << "상품 진열 재고 : " << store->displayedProduct[store->headOffice.GetProductList().at(index - 1)] << endl;
			cout << endl << store->headOffice.GetProductList().at(index - 1).GetName() << "주문한 상품 개수 >> ";
			cin >> count;
			if (count <= 0) cout << "주문을 취소하였습니다." << endl << endl;
			else if (!count) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
			else if (count > store->displayedProduct[store->headOffice.GetProductList().at(index - 1)]) cout << "일정 수량 이상 결제할 수 없습니다. 다시 주문해 주세요." << endl << endl;
			else {
				prods[store->headOffice.GetProductList().at(index - 1)] += count;
			}
			break;
		case 6:
			con.ChangeOrder(prods);
			ordering = false;
			break;
		case 7:
			cout << "결제를 취소하였습니다.\n\n" << endl;
			return;
			break;
		default:
			cout << "확인되지 않은 메뉴 입력. 다시 입력해 주세요.\n\n" << endl;
			break;
		}
		
	}
	if (store->Buy(con)) { // 구매가 이뤄졌는지 확인하기
		cout << "결제를 마쳤습니다. 안녕히 가십시오." << endl;
		map<Product, int>::iterator iter;
		for (iter = store->displayedProduct.begin(); iter != store->displayedProduct.end(); ++iter) {
			iter->second -= prods[iter->first];
		} // 고객이 가져간 상품을 진열대에서 뺀다.
		this->ordering.push_back(prods); //고객 주문 내역에 결제 내역을 추가한다.
	}
	else {
		cout << "결제가 실패하였습니다." << endl;
	}
	cout << endl << endl;
}


void ConvenManager::ReturnCustomer() { // 고객의 반품 요청
	cout << endl << endl;

	vector<map<Product, int>>::iterator iter;
	int count = 0;
	for (iter = ordering.begin(); iter != ordering.end(); ++iter) { // 기록에 남아있는 모든 구매 내역을 불러와 출력한다
		++count;
		cout << count << ". " << endl;
		CheckProductMap((map<Product, int>)(*iter));
		cout << endl;
	}
	int index;
	while (true) { //구매 내역에서 선택하기 위한 반복문
		cout << "다음 결제 내역 중 반품할 결제 내역을 선택해 주세요." << endl;
		cout << "결제내역(-1은 반품 취소) >> ";
		cin >> index;
		if (!index) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
		else if (index > 0 && index <= count) break;
		else if (index == -1) return;
		else {
			cout << endl << "결제 내역이 존재하지 않습니다. 다시 골라주세요." << endl << endl; 
		}
	}
	if(store->ReturningProduct(&ordering.at(index - 1))) {
		cout << "반품 작업이 완료되었습니다." << endl; // 반품이 성공적으로 마무리되었을때
	}
	else {
		cout << "반품이 취소되었습니다." << endl; // 반품이 실패했을때
	}

	cout << endl << endl;
}


void ConvenManager::TaxReturning() { // 지금까지 내역을 정산한 후 저장한다
	store->TaxReturn(totalRevenue); //가게 갱신 요청
	time(&timeNow); // 시간 갱신
	SaveToday(); //지금까지의 내역을 저장한다.
	cout << "정산이 완료되어 저장합니다." << endl << endl << endl;
}

bool ConvenManager::LoadToday() { // 오늘 편의점 상황을 로드하여 시작한다.
	std::ifstream file("Savefile.dat");
	if (!file) {
		cout << "파일을 열 수 없습니다." << endl;
		return false;
	}
	string name;
	file >> name; // 이름
	store = new Store(Sellor(name));
	file >> totalRevenue; //총수익

	int count;
	map<Product, int> prods;
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // 목록을 불러오기 전, 입고 목록의 리스트를 넣어준다.
	//입고 목록 불러오기(입고 목록 개수, 실질 목록)
	file >> count;
	for (int i = 0; i < count; i++) { // 입고된 목록을 불러오며 불러오는 즉시 창고 목록을 세팅한다.
		file >> prods[store->headOffice.GetProductList().at(0)];
		store->storageProduct[store->headOffice.GetProductList().at(0)] += prods[store->headOffice.GetProductList().at(0)]; 
		file >> prods[store->headOffice.GetProductList().at(1)];
		store->storageProduct[store->headOffice.GetProductList().at(1)] += prods[store->headOffice.GetProductList().at(1)];
		file >> prods[store->headOffice.GetProductList().at(2)];
		store->storageProduct[store->headOffice.GetProductList().at(2)] += prods[store->headOffice.GetProductList().at(2)];
		file >> prods[store->headOffice.GetProductList().at(3)];
		store->storageProduct[store->headOffice.GetProductList().at(3)] += prods[store->headOffice.GetProductList().at(3)];
		file >> prods[store->headOffice.GetProductList().at(4)];
		store->storageProduct[store->headOffice.GetProductList().at(4)] += prods[store->headOffice.GetProductList().at(4)];
		storing.push_back(prods); //리스트 불러오기마다 다시 push해주기
	}
	//주문 목록 저장(주문 목록 개수, 실질 목록 저장)
	file >> count;
	for (int i = 0; i < count; i++) { // 주문 목록 상태를 순서대로 불러오며, 주문이므로 위와는 다르게 창고 목록에서 뺀다.
		file >> prods[store->headOffice.GetProductList().at(0)];
		store->storageProduct[store->headOffice.GetProductList().at(0)] -= prods[store->headOffice.GetProductList().at(0)];
		file >> prods[store->headOffice.GetProductList().at(1)];
		store->storageProduct[store->headOffice.GetProductList().at(1)] -= prods[store->headOffice.GetProductList().at(1)];
		file >> prods[store->headOffice.GetProductList().at(2)];
		store->storageProduct[store->headOffice.GetProductList().at(2)] -= prods[store->headOffice.GetProductList().at(2)];
		file >> prods[store->headOffice.GetProductList().at(3)];
		store->storageProduct[store->headOffice.GetProductList().at(3)] -= prods[store->headOffice.GetProductList().at(3)];
		file >> prods[store->headOffice.GetProductList().at(4)];
		store->storageProduct[store->headOffice.GetProductList().at(4)] -= prods[store->headOffice.GetProductList().at(4)];
		ordering.push_back(prods); //리스트 불러오기마다 다시 push해주기
	}
	//진열된 상품을 불러온다.
	file >> store->displayedProduct[store->headOffice.GetProductList().at(0)];
	store->storageProduct[store->headOffice.GetProductList().at(0)] -= store->displayedProduct[store->headOffice.GetProductList().at(0)]; // 남아있는 목록에서 빼서 진열해 놓은것이므로 진열된만큼 창고에서 뺀다.
	file >> store->displayedProduct[store->headOffice.GetProductList().at(1)];
	store->storageProduct[store->headOffice.GetProductList().at(1)] -= store->displayedProduct[store->headOffice.GetProductList().at(1)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(2)];
	store->storageProduct[store->headOffice.GetProductList().at(2)] -= store->displayedProduct[store->headOffice.GetProductList().at(2)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(3)];
	store->storageProduct[store->headOffice.GetProductList().at(3)] -= store->displayedProduct[store->headOffice.GetProductList().at(3)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(4)];
	store->storageProduct[store->headOffice.GetProductList().at(4)] -= store->displayedProduct[store->headOffice.GetProductList().at(4)];
}

bool ConvenManager::SaveToday() { // 오늘 편의점 상황을 저장한다
	std::ofstream file("Savefile.dat");
	if (!file) {
		cout << "파일을 열 수 없습니다." << endl;
		return false;
	}
	//이름, 총수익, 입고 목록, 주문 목록, 진열된 상태 순으로 파일에 쓴다.
	file << store->owner.GetName() << endl; // 이름
	file << totalRevenue << endl; //총수익
	
	//입고 목록 저장(입고 목록 개수, 실질 목록 저장)
	file << storing.size() << endl;
	vector<map<Product, int>>::iterator iter;
	for (iter = storing.begin(); iter != storing.end(); ++iter) { // 입고된 목록 상태를 순서대로 저장한다
		file << (*iter)[store->headOffice.GetProductList().at(0)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(1)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(2)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(3)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(4)] << endl;
	}
	//주문 목록 저장(주문 목록 개수, 실질 목록 저장)
	file << ordering.size() << endl;
	for (iter = ordering.begin(); iter != ordering.end(); ++iter) { // 주문 목록 상태를 순서대로 저장한다
		file << (*iter)[store->headOffice.GetProductList().at(0)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(1)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(2)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(3)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(4)] << endl;
	}
	//진열된 상품 저장
	file << store->displayedProduct[store->headOffice.GetProductList().at(0)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(1)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(2)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(3)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(4)] << endl; 
}
