/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : main.cpp
* ��ɼ��� : ConvenienceManager�� �̿��Ͽ� ���������� ���ư��� ���� �Լ��� �ۼ��ϴ� ����
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
			cout << "**********������ ���� ���α׷�**********" << endl;
			cout << " 1. ���� ���� ��Ȳ Ȯ��" << endl;
			cout << " 2. �԰� ��û" << endl;
			cout << " 3. �����ϱ�" << endl;
			cout << " 4. ���� �ֹ��ϱ�" << endl;
			cout << " 5. ���� ��ǰ�ϱ�" << endl;
			cout << " 6. ����" << endl;
			cout << " 7. ���α׷� ����" << endl;
			cout << "**************************************" << endl;
			int selected = 0;
			cout << "�޴��� �����ϼ��� >> ";
			cin >> selected;
			if (!selected) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
			switch (selected) //manager Ŭ������ �����ϴ� ���� �Լ��� ������ ��ȣ�� ���� �������ش�.
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
				cout << "Ȯ�ε��� ���� �޴� �Է�. �ٽ� �Է��� �ּ���.\n\n" << endl;
				break;
			}
		}
	}
	catch (const char* str) {
		cout << str << endl;
	}
	return 0;
}