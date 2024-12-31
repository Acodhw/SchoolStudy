/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : main.cpp
* ��ɼ��� : Headoffice ������� �ȿ� �ִ� Ŭ���� �Լ� �ۼ�
*/

#include <iostream>
#include <fstream>
#include "Headoffice.h"

HeadOffice::HeadOffice() { //������ ��ǰ ����� �ʱ�ȭ
	prodList.clear();
	prodList.push_back(Product("�Ŷ��", 1100));
	prodList.push_back(Product("�ֹ�", 900));
	prodList.push_back(Product("�ﰢ���", 1100));
	prodList.push_back(Product("�ܹ���", 2000));
	prodList.push_back(Product("����", 2000, true)); //��ǰ ����� ����
}

vector<Product> HeadOffice::GetProductList() { // ��ǰ ����� �޾ƿ���
	return prodList;
}

void HeadOffice::ProfitDistribution(int& profit) { //������ ����� ���ͺй�
	if(profit >= 0) profit = (int)(profit - (profit * 0.3));
}

void CheckProductMap(map<Product, int> prods) { // ��ǰ map�� Ȯ���ϴ� �Լ�
	map<Product, int>::iterator iter;
	for (iter = prods.begin(); iter != prods.end(); ++iter) {
		std::cout << "��ǰ�� : " << ((Product)iter->first).GetName() << ", ���� : " << iter->second << std::endl; //map ���·� �ҷ����� ��ǰ map�� ���ư��� Ȯ���Ͽ� ���
	}
}