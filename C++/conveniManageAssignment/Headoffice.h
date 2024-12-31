/*
* ���ϸ� : Headoffice.h
* ��ɼ��� : ������ ���� ���(��ǰ �ֹ�, ���� ������ ����) Ŭ���� ����
*/

#include "Product.h"
#include <vector>
#include <map>

using std::map;
using std::vector;

#ifndef HEDO //��� ������ �ѹ��� ����ǵ��� �ϴ� ����
#define HEDO

void CheckProductMap(map<Product, int> prods); // ��ǰ map�� Ȯ���ϴ� �Լ�

class HeadOffice {
private:
	vector<Product> prodList; //���簡 �����ϴ� ��ǰ
	const int profitDistributionRatio = 30; //����� ������ ���ͷ�
public:
	HeadOffice(); //������ ��ǰ ����� �ʱ�ȭ
	vector<Product> GetProductList(); // ��ǰ ����� �޾ƿ���
	void ProfitDistribution(int& profit); //������ ����� ���ͺй�
};

#endif
