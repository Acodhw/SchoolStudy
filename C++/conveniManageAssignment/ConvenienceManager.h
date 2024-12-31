/*
* ���ϸ� : CoinvenienceManager.h
* ��ɼ��� : ���� ������ ���� Ŭ���� ���� ����
*/

#include "Convenience.h"
#include "Consumer.h"
#include <ctime>

#define MINIMUM_WAGE 9000 // �����ñ�

#ifndef MANAGE //��� ������ �ѹ��� ����ǵ��� �ϴ� ����
#define MANAGE

class ConvenManager {
private:
	time_t timeNow; // �ð� ����
	int totalRevenue; // �� ����. ���� �������� ���� ��Ȳ�� ��Ÿ����. -�� ������ ��Ȳ, +�� ������ ��Ȳ
	Store * store; // ����� ����
	bool LoadToday(); // �������� ����� ������ ��Ȳ�� �ε��Ͽ� �����Ѵ�.
	bool SaveToday(); // ���� ������ ��Ȳ�� �����Ѵ�
	vector<map<Product, int>> ordering; //���� �ֹ� ���
	vector<map<Product, int>> storing; //�԰� ���
public:
	ConvenManager(); // ������. �Ŵ��� ���α׷� ���� ����
	~ConvenManager(); // �Ҹ���. �Ŵ��� ���α׷� ����
	void CheckNow(); // ���� ������ ��Ȳ�� üũ�Ѵ�
	void Displaying(); // ����
	void OrderingToHead(); // ���翡 �԰� ��û�� �Ѵ�
	
	void OrderCustomer(); // ���� �ֹ� ��û
	void ReturnCustomer(); // ���� ��ǰ ��û

	void TaxReturning(); // ���ݱ��� ������ ������ �� �����Ѵ�
};

#endif
