/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : main.cpp
* ��ɼ��� : ConvenienceManager ������� �ȿ� �ִ� Ŭ���� �Լ� �ۼ�
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "ConvenienceManager.h"

using std::cout;
using std::cin;
using std::endl;

ConvenManager::ConvenManager() { // ������. �Ŵ��� ���α׷� ���� ����
	cout << "������ ���� ���α׷��� �����մϴ�." << endl;
	if (LoadToday()) {  	
		time(&timeNow);
		return;
	} // ����� �����Ͱ� �ִٸ� �ҷ��´�. �ٸ� �ð��� ���÷� �����.
	cout << "����� �����Ͱ� ���� ���� �����͸� ����ϴ�." << endl; //����� �����Ͱ� ���ٸ� ���۵ȴ�
	string name = "";
	while (name == "") {
		cout << "����� �̸���? >> "; //�̸� �޾ƿ���
		cin >> name;
	}
	store = new Store(Sellor(name)); //Store Ŭ���� �����Ҵ�. �� store ��ü�� �츮�� ������ �������� ��ü�̴�.
	cout << name << "������ ������ ���� ���α׷��� �����մϴ�.\n\n\n\n" << endl;
	time(&timeNow); // ���� �ð��� ���Ѵ�.
	totalRevenue = 0;
	SaveToday(); // �ٽ� ���� �� ������ �ݺ����� �ʵ��� �켱 ���Ϸ� �����Ѵ�.
}

ConvenManager::~ConvenManager() { // �Ҹ���. �Ŵ��� ���α׷� ����
	TaxReturning();// ������ �� ����
	cout << "���α׷��� �����Ͽ����ϴ�." << endl;
	delete store;
}


void ConvenManager::CheckNow() { // ���� ������ ��Ȳ�� üũ�Ѵ�
	cout << endl << endl;
	struct tm* date = localtime(&timeNow);
	cout << "���� ��¥ : " << date->tm_year + 1900 << "-" << date->tm_mon + 1 << "-" << date->tm_mday << endl;
	cout << "������(�Ǹ���) : " << store->owner.GetName() << endl << endl; // ��¥�� ������ ���

	cout << "�� �Ѽ��� : " << totalRevenue << endl << endl; // ��¥�� ������ ���

	cout << "������ ��ǰ : " << endl;
	CheckProductMap(store->displayedProduct);

	cout  << endl;

	cout << "������ ��ǰ : " << endl;
	CheckProductMap(store->storageProduct);
	cout << endl << endl;
}

void ConvenManager::OrderingToHead() { // ���翡 �԰� ��û�� �Ѵ�
	cout << endl << endl;
	map<Product, int> prods;
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // prods�� �����ϱ� ���� �̸� ����� insert�س��´�.
	bool ordering = true; // �ֹ��� �������� üũ�ϱ�
	while (ordering) {
		cout << endl;
		cout << "********�԰� ��û�ϱ�(��ǰ ����)********" << endl;
		cout << " 1. " << store->headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << store->headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << store->headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << store->headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << store->headOffice.GetProductList().at(4).GetName() << endl; // �԰� ��û ��ǰ�� headOffice���� �޾ƿͼ� ����Ʈ�� ���´�
		cout << " 6. �԰� ��û ����" << endl;
		cout << "**************************************" << endl;
		cout << "�ֹ��ϰ��� �ϴ� ��ǰ ���� >> ";
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
			cout << endl << store->headOffice.GetProductList().at(index - 1).GetName() << " ��ǰ�� �� �� �ֹ��Ͻðڽ��ϱ�? >> ";
			cin >> count;
			if (count <= 0) cout << "�ֹ��� ����Ͽ����ϴ�." << endl << endl;
			else if (!count) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
			else {
				prods[store->headOffice.GetProductList().at(index - 1)] += count;
			}
			break;
		case 6:
			cout << "������ ���� �ֹ��� �޾� â�� �԰��Ͽ����ϴ�." << endl << endl;
			CheckProductMap(prods);
			ordering = false;
			break;
		default:
			cout << "Ȯ�ε��� ���� �޴� �Է�. �ٽ� �Է��� �ּ���.\n\n" << endl;
			break;
		}

	}
	map<Product, int>::iterator iter;
	for (iter = prods.begin(); iter != prods.end(); ++iter) {
		store->storageProduct[iter->first] += iter->second;
	} // �ֹ��� ��ǰ�� storageProduct,�� ��ǰ ���ſ� ���Ѵ�.
	storing.push_back(prods); //�԰� ��Ȳ�� ����Ѵ�.
	cout << endl << endl;
}


void ConvenManager::Displaying() {// ����
	store->owner.DisplayingProduct(store);
}

void ConvenManager::OrderCustomer() { // ���� �ֹ� ��û
	Consumer con;
	cout << endl << endl;
	map<Product, int> prods; // �԰� ��û�� �� ��ǰ ����Ʈ
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // prods�� �����ϱ� ���� �̸� ����� insert�س��´�.
	bool ordering = true;
	while (ordering) {
		cout << endl;
		cout << "***************�ֹ� �ޱ�***************" << endl;
		cout << " 1. " << store->headOffice.GetProductList().at(0).GetName() << endl;
		cout << " 2. " << store->headOffice.GetProductList().at(1).GetName() << endl;
		cout << " 3. " << store->headOffice.GetProductList().at(2).GetName() << endl;
		cout << " 4. " << store->headOffice.GetProductList().at(3).GetName() << endl;
		cout << " 5. " << store->headOffice.GetProductList().at(4).GetName() << endl; // ���� ���� ǰ���� headOffice���� �޾ƿͼ� ����Ʈ�� ���´�
		cout << " 6. ���� ����" << endl;
		cout << " 7. ���� ���" << endl;
		cout << "**************************************" << endl;
		cout << "�ֹ��ϰ��� �ϴ� ��ǰ ���� >> ";
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
			if (store->headOffice.GetProductList().at(index - 1).GetisR18() && !con.AgeCheck()) {
				cout << "û�ҳ��� ������ �� ���� ǰ���Դϴ�." << endl << endl;
				break;
			}
			int count;
			cout << "��ǰ ���� ��� : " << store->displayedProduct[store->headOffice.GetProductList().at(index - 1)] << endl;
			cout << endl << store->headOffice.GetProductList().at(index - 1).GetName() << "�ֹ��� ��ǰ ���� >> ";
			cin >> count;
			if (count <= 0) cout << "�ֹ��� ����Ͽ����ϴ�." << endl << endl;
			else if (!count) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
			else if (count > store->displayedProduct[store->headOffice.GetProductList().at(index - 1)]) cout << "���� ���� �̻� ������ �� �����ϴ�. �ٽ� �ֹ��� �ּ���." << endl << endl;
			else {
				prods[store->headOffice.GetProductList().at(index - 1)] += count;
			}
			break;
		case 6:
			con.ChangeOrder(prods);
			ordering = false;
			break;
		case 7:
			cout << "������ ����Ͽ����ϴ�.\n\n" << endl;
			return;
			break;
		default:
			cout << "Ȯ�ε��� ���� �޴� �Է�. �ٽ� �Է��� �ּ���.\n\n" << endl;
			break;
		}
		
	}
	if (store->Buy(con)) { // ���Ű� �̷������� Ȯ���ϱ�
		cout << "������ ���ƽ��ϴ�. �ȳ��� ���ʽÿ�." << endl;
		map<Product, int>::iterator iter;
		for (iter = store->displayedProduct.begin(); iter != store->displayedProduct.end(); ++iter) {
			iter->second -= prods[iter->first];
		} // ���� ������ ��ǰ�� �����뿡�� ����.
		this->ordering.push_back(prods); //�� �ֹ� ������ ���� ������ �߰��Ѵ�.
	}
	else {
		cout << "������ �����Ͽ����ϴ�." << endl;
	}
	cout << endl << endl;
}


void ConvenManager::ReturnCustomer() { // ���� ��ǰ ��û
	cout << endl << endl;

	vector<map<Product, int>>::iterator iter;
	int count = 0;
	for (iter = ordering.begin(); iter != ordering.end(); ++iter) { // ��Ͽ� �����ִ� ��� ���� ������ �ҷ��� ����Ѵ�
		++count;
		cout << count << ". " << endl;
		CheckProductMap((map<Product, int>)(*iter));
		cout << endl;
	}
	int index;
	while (true) { //���� �������� �����ϱ� ���� �ݺ���
		cout << "���� ���� ���� �� ��ǰ�� ���� ������ ������ �ּ���." << endl;
		cout << "��������(-1�� ��ǰ ���) >> ";
		cin >> index;
		if (!index) throw "ġ���� �Է� ������ ���� ���α׷��� �����մϴ�.";
		else if (index > 0 && index <= count) break;
		else if (index == -1) return;
		else {
			cout << endl << "���� ������ �������� �ʽ��ϴ�. �ٽ� ����ּ���." << endl << endl; 
		}
	}
	if(store->ReturningProduct(&ordering.at(index - 1))) {
		cout << "��ǰ �۾��� �Ϸ�Ǿ����ϴ�." << endl; // ��ǰ�� ���������� �������Ǿ�����
	}
	else {
		cout << "��ǰ�� ��ҵǾ����ϴ�." << endl; // ��ǰ�� ����������
	}

	cout << endl << endl;
}


void ConvenManager::TaxReturning() { // ���ݱ��� ������ ������ �� �����Ѵ�
	store->TaxReturn(totalRevenue); //���� ���� ��û
	time(&timeNow); // �ð� ����
	SaveToday(); //���ݱ����� ������ �����Ѵ�.
	cout << "������ �Ϸ�Ǿ� �����մϴ�." << endl << endl << endl;
}

bool ConvenManager::LoadToday() { // ���� ������ ��Ȳ�� �ε��Ͽ� �����Ѵ�.
	std::ifstream file("Savefile.dat");
	if (!file) {
		cout << "������ �� �� �����ϴ�." << endl;
		return false;
	}
	string name;
	file >> name; // �̸�
	store = new Store(Sellor(name));
	file >> totalRevenue; //�Ѽ���

	int count;
	map<Product, int> prods;
	prods.insert({ store->headOffice.GetProductList().at(0), 0 });
	prods.insert({ store->headOffice.GetProductList().at(1), 0 });
	prods.insert({ store->headOffice.GetProductList().at(2), 0 });
	prods.insert({ store->headOffice.GetProductList().at(3), 0 });
	prods.insert({ store->headOffice.GetProductList().at(4), 0 }); // ����� �ҷ����� ��, �԰� ����� ����Ʈ�� �־��ش�.
	//�԰� ��� �ҷ�����(�԰� ��� ����, ���� ���)
	file >> count;
	for (int i = 0; i < count; i++) { // �԰�� ����� �ҷ����� �ҷ����� ��� â�� ����� �����Ѵ�.
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
		storing.push_back(prods); //����Ʈ �ҷ����⸶�� �ٽ� push���ֱ�
	}
	//�ֹ� ��� ����(�ֹ� ��� ����, ���� ��� ����)
	file >> count;
	for (int i = 0; i < count; i++) { // �ֹ� ��� ���¸� ������� �ҷ�����, �ֹ��̹Ƿ� ���ʹ� �ٸ��� â�� ��Ͽ��� ����.
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
		ordering.push_back(prods); //����Ʈ �ҷ����⸶�� �ٽ� push���ֱ�
	}
	//������ ��ǰ�� �ҷ��´�.
	file >> store->displayedProduct[store->headOffice.GetProductList().at(0)];
	store->storageProduct[store->headOffice.GetProductList().at(0)] -= store->displayedProduct[store->headOffice.GetProductList().at(0)]; // �����ִ� ��Ͽ��� ���� ������ �������̹Ƿ� �����ȸ�ŭ â���� ����.
	file >> store->displayedProduct[store->headOffice.GetProductList().at(1)];
	store->storageProduct[store->headOffice.GetProductList().at(1)] -= store->displayedProduct[store->headOffice.GetProductList().at(1)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(2)];
	store->storageProduct[store->headOffice.GetProductList().at(2)] -= store->displayedProduct[store->headOffice.GetProductList().at(2)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(3)];
	store->storageProduct[store->headOffice.GetProductList().at(3)] -= store->displayedProduct[store->headOffice.GetProductList().at(3)];
	file >> store->displayedProduct[store->headOffice.GetProductList().at(4)];
	store->storageProduct[store->headOffice.GetProductList().at(4)] -= store->displayedProduct[store->headOffice.GetProductList().at(4)];
}

bool ConvenManager::SaveToday() { // ���� ������ ��Ȳ�� �����Ѵ�
	std::ofstream file("Savefile.dat");
	if (!file) {
		cout << "������ �� �� �����ϴ�." << endl;
		return false;
	}
	//�̸�, �Ѽ���, �԰� ���, �ֹ� ���, ������ ���� ������ ���Ͽ� ����.
	file << store->owner.GetName() << endl; // �̸�
	file << totalRevenue << endl; //�Ѽ���
	
	//�԰� ��� ����(�԰� ��� ����, ���� ��� ����)
	file << storing.size() << endl;
	vector<map<Product, int>>::iterator iter;
	for (iter = storing.begin(); iter != storing.end(); ++iter) { // �԰�� ��� ���¸� ������� �����Ѵ�
		file << (*iter)[store->headOffice.GetProductList().at(0)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(1)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(2)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(3)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(4)] << endl;
	}
	//�ֹ� ��� ����(�ֹ� ��� ����, ���� ��� ����)
	file << ordering.size() << endl;
	for (iter = ordering.begin(); iter != ordering.end(); ++iter) { // �ֹ� ��� ���¸� ������� �����Ѵ�
		file << (*iter)[store->headOffice.GetProductList().at(0)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(1)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(2)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(3)] << endl;
		file << (*iter)[store->headOffice.GetProductList().at(4)] << endl;
	}
	//������ ��ǰ ����
	file << store->displayedProduct[store->headOffice.GetProductList().at(0)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(1)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(2)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(3)] << endl;
	file << store->displayedProduct[store->headOffice.GetProductList().at(4)] << endl; 
}
