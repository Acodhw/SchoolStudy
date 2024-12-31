/*
* ���ϸ� : main.cpp
* ��ɼ��� : Convenience ������� �ȿ� �ִ� Ŭ���� �Լ� �ۼ�
*/

#include <iostream>
#include "Convenience.h"

using std::cout;
using std::cin;
using std::endl;


// �Ǹ��� Ŭ����
Sellor::Sellor(string name) { // ���� ������ �ʱ�ȭ
	this->name = name;
}

void Sellor::DisplayingProduct(Store* store) { // ��ǰ�� �����Ѵ�
	map<Product, int>::iterator iter;
	bool isDisplayed = false;
	for (iter = store->displayedProduct.begin(); iter != store->displayedProduct.end(); ++iter) {
		if (store->storageProduct[iter->first] > 0 && iter->second < 10) {
			isDisplayed = true;
			int count = (store->storageProduct[iter->first] - iter->second > 10) ? (10 - iter->second) : (store->storageProduct[iter->first] - iter->second); //��ǰ ���� ���� �ִ� ���� 10�� ���߱� ���� ������ ����Ѵ�.
			iter->second += count;
			store->storageProduct[iter->first] -= count; // ���忡���� ���� �����뿡�� ���Ѵ�.
		}
	}
	if(isDisplayed)cout << "��ǰ ���� �Ϸ�." << endl << endl;
	else { cout << "��� ���ų� �̹� ������ �����Ǿ� �־� ��ǰ�� ������ �� �����ϴ�." << endl << endl; } // ������ ������ �� �ߴ� �޼���
}

//���� ��Ȳ Ŭ����
Store::Store(Sellor owner) { // �ʱ� ���� �غ�
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
	displayedProduct.insert({ headOffice.GetProductList().at(4), 0 }); // ������ â�� ��Ȳ ���� ��� �ʱ�ȭ��. ���翡�� ���� �� �ִ� ��ǰ�� �̿��� map�� �����Ѵ�.

	revenue = 0;
}

void Store::TaxReturn(int& total){ // ����
	int rev = revenue;
	revenue = 0;
	headOffice.ProfitDistribution(rev); // headoffice�� ������ �Ϻ� �ش�.
	total += rev; // �� ������ ���Ѵ�.
}

bool Store::Buy(Consumer consumer){ // ��ǰ�� �����ϴ� Ŭ����
	int totalPrice = 0;
	cout << "������" << endl;
	map<Product, int> ordered = consumer.GetOrder();
	map<Product, int>::iterator iter;
	for (iter = ordered.begin(); iter != ordered.end(); ++iter) {
		if (ordered[iter->first] <= 0) continue;
		std::cout << "��ǰ�� : " << ((Product)iter->first).GetName() << ", ���� : " << iter->second << ", ���� ���� : " << ((Product)iter->first).GetPrice() << std::endl;
		totalPrice += ((Product)iter->first).GetPrice() * iter->second;

	} // �ֹ� ���� ���, �ֹ��� �� ������ ����Ѵ�.
	if (totalPrice <= 0) return false; // ���ݿ� ������ ������� ������ ����
	cout << "�� " << totalPrice << "�� ���� �Ǿ����ϴ�." << endl;
	revenue += totalPrice;
	return true;
}

bool Store::ReturningProduct(map<Product, int>* needReturn) { // ���� ��ǰ ��û
	while (true) {
		cout << endl;
		cout << "***************��ǰ ����***************" << endl;
		cout << " 1. " << headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << headOffice.GetProductList().at(4).GetName() << endl; // ��ǰ ���� ǰ���� headOffice���� �޾ƿͼ� ����Ʈ�� ���´�
		cout << " 6. ��ǰ ����" << endl;
		cout << "**************************************" << endl;
		cout << "��ǰ�ϰ��� �ϴ� ��ǰ ���� >> ";
		int index;
		cin >> index;
		if (!index) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
		switch (index) // 1~5������ index�� �����ϰ�, �ٸ� �޴��� ���� �����ϱ� ���� switch case��
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			int count;
			cout << "���� �������� ���� : " << (*needReturn)[headOffice.GetProductList().at(index - 1)] << endl;
			cout << endl << headOffice.GetProductList().at(index - 1).GetName() << " �� ���� ��ǰ�� ���ΰ���? >> ";
			cin >> count;
			if (count <= 0) cout << "��ǰ�� ����Ͽ����ϴ�." << endl << endl;
			else if (!count) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
			else if (count > (*needReturn)[headOffice.GetProductList().at(index - 1)]) cout << "�Ǹŵ� �ͺ��� ���� ��ǰ�� �� �����ϴ�. �ٽ� �õ��� �ּ���." << endl << endl; // ��ǰ ������ üũ
			else {
				(*needReturn)[headOffice.GetProductList().at(index - 1)] -= count;//��ǰ �� ���� ������ ���� �ٲ㼭 �ּҷ� �����Ѵ�.
				revenue -= headOffice.GetProductList().at(index - 1).GetPrice() * count; //������ ����
				storageProduct[headOffice.GetProductList().at(index - 1)] += count; //��ǰ�� ��ǰ�� �ٽ� â��� �����Ѵ�.
			}
			break;
		case 6:
			return true;
			break;
		default:
			cout << "Ȯ�ε��� ���� �޴� �Է�. �ٽ� �Է��� �ּ���.\n\n" << endl;
			break;
		}
	}
	return true;
}



