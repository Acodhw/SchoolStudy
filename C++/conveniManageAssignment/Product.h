/*
* �ۼ��� : 2022112443 ��ġȯ
* ���ϸ� : product.h
* ��ɼ��� : ��ǰ Ŭ������ ����
*/

#include<iostream>
using std::string;


#ifndef PROD // ��� ������ �ѹ��� ����ǵ��� �ϴ� ����
#define PROD

class Product {
private:
	string productName; // ��ǰ �̸�
	int price; // ��ǰ ����
	bool isR18; // û�ҳ��� �� �� ���� ��������
public:
	Product(string name, int price = 0, bool isR18 = false); // ��ǰ ���� �ʱ�ȭ
	string GetName(); // ��ǰ �̸� �޾ƿ���
	int GetPrice(); // ��ǰ ���� �޾ƿ���
	bool GetisR18(); // ��ǰ�� û�ҳ� �Ǹű������� �޾ƿ���

	bool operator<(const Product& i) const {
		return productName < i.productName;
	} // ������ ���� ������ �ߺ�
};

#endif
