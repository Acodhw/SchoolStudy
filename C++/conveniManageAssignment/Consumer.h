/*
* ���ϸ� : Consumer.h
* ��ɼ��� : �� Ŭ����(��ǰ ����, ����) Ŭ���� ����
*/

#include "Headoffice.h"
#include <ctime>

#ifndef CONS //��� ������ �ѹ��� ����ǵ��� �ϴ� ����
#define CONS

class Consumer { // ��ǰ�� �����ϴ� ���
private:
	int age; // �Һ����� ����. ���� ������ ��. û�� ��ǰ�� 18����� ���� ����
	map<Product, int> buyedProduct; // ���� �ֹ��� ��ǰ
public:
	Consumer(); // �Һ����� ������. 
	Consumer(int age); // �Һ����� ������. ���� ����
	void ChangeOrder(map<Product, int> order); // ���� �ֹ� ����
	map<Product, int> GetOrder(); // ���� �ֹ� Ȯ��
	bool AgeCheck(); // �Һ��ڰ� û�� ��ǰ ���Ű� ������ �������� üũ
};

#endif
