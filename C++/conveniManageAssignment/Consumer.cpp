/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : main.cpp
* ��ɼ��� : Consumer ������� �ȿ� �ִ� Ŭ���� �Լ� �ۼ�
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Consumer.h"
#include <cstdlib>

Consumer::Consumer() { // �Һ����� ������. 
	srand((unsigned int)time(NULL));
	int age = 8;
	for (int i = 0; i < 2; i++) {
		age += (rand() % 40);
	} //���� ���̴� ��������. ���� ������ ���̸� ������ �� ���� ������ �������� �����Ѵ�
	this->age = age;
}

Consumer::Consumer(int age) { // �Һ����� ������. 
	this->age = age;
}

bool Consumer::AgeCheck() { // �Һ��ڰ� û�� ��ǰ ���Ű� ������ �������� üũ
	if (age >= 18) return true;
	return false; //18�� �̻����� üũ
}

void Consumer::ChangeOrder(map<Product, int> order){ // ���� �ֹ� ����
	buyedProduct = order;
}

map<Product, int> Consumer::GetOrder() { // ���� �ֹ� Ȯ��
	return buyedProduct;
}