/*
* 작성자 : 2022112443 안치환
* 파일명 : main.cpp
* 기능설명 : ConvenienceManager을 이용하여 실질적으로 돌아가는 메인 함수를 작성하는 파일
*/

#include <iostream>
#include "ConvenienceManager.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	try {
		ConvenManager manager;
		while (true) {
			cout << "**********편의점 관리 프로그램**********" << endl;
			cout << " 1. 현재 가게 상황 확인" << endl;
			cout << " 2. 입고 신청" << endl;
			cout << " 3. 진열하기" << endl;
			cout << " 4. 고객의 주문하기" << endl;
			cout << " 5. 고객의 반품하기" << endl;
			cout << " 6. 정산" << endl;
			cout << " 7. 프로그램 종료" << endl;
			cout << "**************************************" << endl;
			int selected = 0;
			cout << "메뉴를 선택하세요 >> ";
			cin >> selected;
			if (!selected) throw "치명적 입력 오류로 인해 프로그램을 종료합니다.";
			switch (selected) //manager 클래스에 존재하는 관리 함수로 선택한 번호에 따라 연결해준다.
			{
			case 1:
				manager.CheckNow(); 
				break;
			case 2:
				manager.OrderingToHead();
				break;
			case 3:
				manager.Displaying();
				break;
			case 4:
				manager.OrderCustomer();
				break;
			case 5:
				manager.ReturnCustomer();
				break;
			case 6:
				manager.TaxReturning();
				break;
			case 7:
				return 0;
				break;
			default:
				cout << "확인되지 않은 메뉴 입력. 다시 입력해 주세요.\n\n" << endl;
				break;
			}
		}
	}
	catch (const char* str) {
		cout << str << endl;
	}
	return 0;
}