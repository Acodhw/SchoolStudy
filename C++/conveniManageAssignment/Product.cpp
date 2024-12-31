/*
* ���ϸ� : Product.cpp
* ��ɼ��� : Product ��� ���� ���� Ŭ���� �Լ� �ۼ�
*/

#include "Product.h"



Product::Product(string name, int price, bool isR18) { // ��ǰ ���� �ʱ�ȭ
	this->productName = name;
	this->price = price;
	this->isR18 = isR18;
}

string Product::GetName() { // ��ǰ �̸� �޾ƿ���
	return productName;
}

int Product::GetPrice() { // ��ǰ ���� �޾ƿ���
	return price;
}

bool Product::GetisR18() { // ��ǰ�� û�ҳ� �Ǹű������� �޾ƿ���
	return isR18;
}

