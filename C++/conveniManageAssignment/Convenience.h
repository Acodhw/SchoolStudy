/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : Coinvenience.h
* ��ɼ��� : ������ ����(�Ǹ���)�� ������ ���� ���α׷��� �ʿ��� Ŭ���� ����
*/

#include "Headoffice.h"
#include "Consumer.h"


#ifndef CONV //��� ������ �ѹ��� ����ǵ��� �ϴ� ����
#define CONV

class Store;

class Sellor { // �Ǹ��� Ŭ����
private:
	string name; // �Ǹ����� �̸�
public:
	Sellor(string name = ""); // ���� ������ �ʱ�ȭ
	void DisplayingProduct(Store* store); // ��ǰ�� ����
	string GetName() { return name; }; // �̸� ������
};

class Store { //���� ��Ȳ(���, ���� ��)�� ���� Ŭ����
private:
	Sellor owner; // ���� ����
	HeadOffice headOffice; // ������ ����
	map<Product, int> displayedProduct; // ������ ��ǰ ���� ���� map
	map<Product, int> storageProduct; // â�� ���� ���� ��ǰ ���� ���� map
	int revenue; // �� ����
public:
	friend class Sellor; // ������ ���� ������ ����
	friend class ConvenManager; // ������ ���� ���� ������ ���� ������ ����
	Store(Sellor owner); // �ʱ� ���� �غ�(�����ε�)
	bool Buy(Consumer consumer); // ���� ���� ��û
	bool ReturningProduct(map<Product, int>* needReturn); // ���� ��ǰ ��û
	void TaxReturn(int& total); // ����
};

#endif
