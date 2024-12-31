/*
* ���� : main.c
* Ư¡ : cpp �����Լ� ����
* ���� : �����Լ� �� ��� ���࿡ �ʿ��� �Լ��� �ۼ�
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "QueueMovie.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fill_n;
using std::to_string;

class MovieManager {
	MovieQueue mvQ;
	string MovieSits_1[5][6] = { "" };
	string MovieSits_4[6][7] = { "" };
	string MovieSits_9[7][8] = { "" };

	bool isTicketedSits();
	bool FindTicketSits(string code, Movie& getMov, int& getVer, int& getHor);
	bool isCanFindTicketSits(string code);

	void CheckSits(int movie, bool LastSkip = true);
	void CheckAllSits(bool LastSkip = true);

	void MovieTicketingOrder();
	bool TicketingOrder(Movie movie, int maxv, int maxh);

	void MovieTicketChangeOrder();
	bool ChangeOrder(string before, Movie movie, int maxv, int maxh);

	void MovieTicketCancelOrder();


	bool MovieTicketing(MovieProcess mp);
	bool MovieTicketChange(MovieProcess mp);
	bool MovieTicketCancel(MovieProcess mp);

	void OrderCheck(MovieProcess mp);
public:
	void SetOrder(int order);
	MovieManager() {
		srand((unsigned int)time(NULL));
	};
};


int main() {
	MovieManager movieManager;
	int order;
	while (true) {
		cout << "---------------��ȭ ���� ���α׷�-------------------" << endl;
		cout << " 1. ��ȭ ����" << endl;
		cout << " 2. ��ȭ ���� ����" << endl;
		cout << " 3. ��ȭ ���� ���" << endl;
		cout << " 4. ��ȭ �¼� ��Ȳ Ȯ��" << endl;
		cout << " 5. ���α׷� ����" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "�����ϰ��� �ϴ� ��ȣ �Է� >> ";
		cin >> order;

		if(order == 5) break;

		movieManager.SetOrder(order);		
	}
	return 0;
}

//��� �ڸ��� ����ִ� �� Ȯ���ϴ� �Լ�
bool MovieManager::isTicketedSits() {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (MovieSits_1[i][j] != "") return true;
		}
	}
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			if (MovieSits_4[i][j] != "") return true;
		}
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 8; j++) {
			if (MovieSits_9[i][j] != "") return true;
		}
	}
	return false;
}
//Ƽ�� ��ȣ�� ������ �׿� �´� ��ȭ�� ��ǥ ������ �����ϴ� �Լ�
bool MovieManager::FindTicketSits(string code, Movie& getMov, int& getVer, int& getHor) {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (MovieSits_1[i][j] == code)
			{
				getMov = JohnWick;
				getVer = i;
				getHor = j;
				return true;
			}
		}
	}
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			if (MovieSits_4[i][j] == code)
			{
				getMov = Rebound;
				getVer = i;
				getHor = j;
				return true;
			}
		}
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 8; j++) {
			if (MovieSits_9[i][j] == code)
			{
				getMov = KillingRomence;
				getVer = i;
				getHor = j;
				return true;
			}
		}
	}
	return false;
}
//Ƽ�� ��ȣ�� ������ �� Ƽ�� ��ȣ�� �ִ� ��ȣ���� Ȯ���ϴ� �Լ�
bool MovieManager::isCanFindTicketSits(string code) {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (MovieSits_1[i][j] == code)
			{
				return true;
			}
		}
	}
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			if (MovieSits_4[i][j] == code)
			{
				return true;
			}
		}
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 8; j++) {
			if (MovieSits_9[i][j] == code)
			{
				return true;
			}
		}
	}
	return false;
}

//����� �޾Ƽ� �� ����� ����-�ٸ� �Լ��� �����ϰ� ť ��尡 7�� �̻��� �� ó���� ����ϴ� �Լ�
void MovieManager::SetOrder(int order) {
	switch (order)
	{
	case 1:
		MovieTicketingOrder();
		break;
	case 2:
		MovieTicketChangeOrder();
		break;
	case 3:
		MovieTicketCancelOrder();
		break;
	case 4:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------�¼� Ȯ��---------------------" << endl;
		cout << " 1. ��ü �󿵰� �¼� Ȯ��" << endl;
		cout << " 2. ���� �󿵰� �¼� Ȯ��" << endl;
		cout << " 3. ���" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "�����ϰ��� �ϴ� ��ȣ �Է� >> ";
		cin >> order;
		if (order != 1 && order != 2) return;
		if (order == 1) {
			CheckAllSits();
			return;
		}
		cout << "\n\n\n\n\n\n" << endl;
		cout << "---------------Ȯ�� ������ �¼� ����Ʈ---------------" << endl;
		cout << " 1. 1��(��ȭ : �� ��4)" << endl;
		cout << " 2. 4��(��ȭ : ���ٿ��)" << endl;
		cout << " 3. 4��(��ȭ : ų�� �θེ)" << endl;
		cout << " 4. ���" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "�����ϰ��� �ϴ� ��ȣ �Է� >> ";
		cin >> order;
		if (order != 1 && order != 2 && order != 3) return;
		CheckSits(order);
		break;
	default:
		cout << "�߸��� ����� �ԷµǾ����ϴ�.\n" << endl;
		break;
	}
	if (mvQ.count >= 7) {
		cout << "\n\n����� ��� ó����....." << endl;
		while (mvQ.count > 0) {
			OrderCheck(mvQ.DeQueue());
		}
		cout << "��� ó�� �Ϸ�Ǿ����ϴ�......\n\n" << endl;
	}
}

//Ư�� ��ȭ�� �ڸ� ������ Ȯ���ϴ� �Լ�
void MovieManager::CheckSits(int order, bool LastSkip) {
	switch (order)
	{
	case 1:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------1��(��ȭ : �� �� 4)�� �ڸ� ����---------------------" << endl;
		for (int i = 0; i < 5; i++) {
			cout << (char)(i + 'A') << "�� : ";
			for (int j = 0; j < 6; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_1[i][j] == "") {
					cout << "{         ����        } ";
				}
				else {
					cout << "{ ���Ź�ȣ : " << MovieSits_1[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	case 2:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------4��(��ȭ : ���ٿ��)�� �ڸ� ����---------------------" << endl;
		for (int i = 0; i < 6; i++) {
			cout << (char)(i + 'A') << "�� : ";
			for (int j = 0; j < 7; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_4[i][j] == "") {
					cout << "{         ����        } ";
				}
				else {
					cout << "{ ���Ź�ȣ : " << MovieSits_4[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	case 3:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------9��(��ȭ : ų�� �θེ)�� �ڸ� ����---------------------" << endl;
		for (int i = 0; i < 7; i++) {
			cout << (char)(i + 'A') << "�� : ";
			for (int j = 0; j < 8; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_9[i][j] == "") {
					cout << "{         ����        } ";
				}
				else {
					cout << "{ ���Ź�ȣ : " << MovieSits_9[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	default:
		cout << "�ش� �ڸ� ������ �����ϴ�." << endl;
		break;
	}
	if(LastSkip)cout << "\n\n\n\n\n\n" << endl;
}
//��� ��ȭ �ڸ� ������ Ȯ���ϴ� �Լ�
void MovieManager::CheckAllSits(bool LastSkip) {
	cout << "----------------------������ ���� ��ȭ �ڸ��� �˻��Ǿ����ϴ�.---------------------\n" << endl;
	cout << "----------------------1��(��ȭ : �� �� 4)�� �ڸ� ����---------------------" << endl;
	for (int i = 0; i < 5; i++) {
		cout << (char)(i + 'A') << "�� : ";
		for (int j = 0; j < 6; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_1[i][j] == "") {
				cout << "{         ����        } ";
			}
			else {
				cout << "{ ���Ź�ȣ : " << MovieSits_1[i][j] << " } ";
			}
		}
		cout << endl;
	}

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------4��(��ȭ : ���ٿ��)�� �ڸ� ����---------------------" << endl;
	for (int i = 0; i < 6; i++) {
		cout << (char)(i + 'A') << "�� : ";
		for (int j = 0; j < 7; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_4[i][j] == "") {
				cout << "{         ����        } ";
			}
			else {
				cout << "{ ���Ź�ȣ : " << MovieSits_4[i][j] << " } ";
			}
		}
		cout << endl;
	}

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------9��(��ȭ : ų�� �θེ)�� �ڸ� ����---------------------" << endl;
	for (int i = 0; i < 7; i++) {
		cout << (char)(i + 'A') << "�� : ";
		for (int j = 0; j < 8; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_9[i][j] == "") {
				cout << "{         ����        } ";
			}
			else {
				cout << "{ ���Ź�ȣ : " << MovieSits_9[i][j] << " } ";
			}
		}
		cout << endl;
	}

	if(LastSkip) cout << "\n\n\n\n\n\n" << endl;
}

//���� ����� Ȯ���ϰ�, ��ȭ ������ �Ʒ� ���� ���� �Լ��� ������ �Լ�
void MovieManager::MovieTicketingOrder() {
	int order;

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------��ȭ ���---------------------" << endl;
	cout << " 1. 1��(��ȭ : �� ��4)" << endl;
	cout << " 2. 4��(��ȭ : ���ٿ��)" << endl;
	cout << " 3. 9��(��ȭ : ų�� �θེ)" << endl;
	cout << " 4. ���" << endl;
	cout << "---------------------------------------------------" << endl;
	while (1) {
		cout << "�����ϰ��� �ϴ� ��ȣ �Է� >> ";
		cin >> order;
		switch (order)
		{
		case 1:
			CheckSits(1, false);
			if (TicketingOrder(JohnWick, 5, 6)) return;
			break;
		case 2:
			CheckSits(2, false);
			if (TicketingOrder(Rebound, 6, 7)) return;
			break;
		case 3:
			CheckSits(3, false);
			if (TicketingOrder(KillingRomence, 7, 8)) return;
			break;
		case 4:
			cout << "\n\n\n\n\n\n" << endl;
			return;
			break;
		default:
			cout << "�߸��� ����� �ԷµǾ����ϴ�.";
			break;
		}

		cout << "\n" << endl;
	}
}
//�ڸ��� ���� ����ó���� �ϰ� ���� ���μ����� ť�� ����ִ� �Լ�
bool MovieManager::TicketingOrder(Movie movie, int maxv, int maxh) {
	MovieProcess mp;
	char ver, check;
	int hor;
	
	cout << "\n���ϴ� �¼� �Է�(�Է� �� (A-5)�� : A 5) >> ";
	cin >> ver >> hor;
	ver = toupper(ver);
	if (ver < 'A' || ver >('A' + maxv - 1) || hor < 1 || hor > maxh) {
		cout << "���� �ڸ��Դϴ�. �ٽ� �ѹ� �Է��� �ּ���." << endl;
		return false;
	}
	else if ((movie == JohnWick && MovieSits_1[(ver - 'A')][hor - 1] != "") || (movie == Rebound && MovieSits_4[(ver - 'A')][hor - 1] != "") || (movie == KillingRomence && MovieSits_9[(ver - 'A')][hor - 1] != "")) {
		cout << "�� �ڸ��� �̹� ���Ű� �Ǿ� �ֽ��ϴ�." << endl;
		return true;
	}
	else {
		check = 0;
		while (toupper(check) != 'Y' && toupper(check) != 'N') {
			cout << "�¼� (" << ver << "-" << hor << ") �� �����մϴ�. ����Ͻðڽ��ϱ�(y/n)? >> ";
			cin >> check;
		}
		if (toupper(check) == 'Y') {
			mp.type = Ticketing;
			mp.movie = movie;		
			string movCode;
			switch (movie)
			{
			case JohnWick:
				movCode = "JW";
				mp.seat = &(MovieSits_1[(ver - 'A')][hor - 1]);
				break;
			case Rebound:
				movCode = "RB";
				mp.seat = &(MovieSits_4[(ver - 'A')][hor - 1]);
				break;
			case KillingRomence:
				movCode = "KR";
				mp.seat = &(MovieSits_9[(ver - 'A')][hor - 1]);
				break;
			default:
				break;
			}
			mp.code = movCode + ver + to_string(hor) + to_string((rand() % 9000) + 1000);
			if (mvQ.EnQueue(mp))
				cout << "�ڸ� ���Ű� ����Ǿ����ϴ�." << endl;
			else
				cout << "�ڸ� ���� ���� ������ �߻��߽��ϴ�. �ٽ� ������ �ּ���." << endl;
		}
		else cout << "��ҵǾ����ϴ�." << endl;
		cout << "\n\n\n\n\n\n" << endl;
		return true;
	}
}

//���� ����� Ȯ���ϰ�, ������ ���ϴ� ���� ���� ��ȣ�� ��ȭ ������ �Ʒ� ���� ���� �Լ��� ������ �Լ�
void MovieManager::MovieTicketChangeOrder() {
	string ch;
	CheckAllSits(false);
	if (!isTicketedSits()) {
		cout << "\n��ü �����Դϴ�. �ٲ� �ڸ��� �����ϴ�.\n\n\n\n\n" << endl;
		return;
	}
	while (1) {
		cout << "\n������ �¼� ���� ��ȣ �Է�(-1�� ���) >> ";
		cin >> ch;
		if (ch == "-1") return;
		if (!isCanFindTicketSits(ch)) {
			cout << "���� ������ ã�� �� �����ϴ�." << endl;
			continue;
		}

		int order;
		cout << "\n\n\n\n\n\n" << endl;
		cout << "--------------�����ϰ��� �ϴ� ��ȭ ���--------------" << endl;
		cout << " 1. 1��(��ȭ : �� ��4)" << endl;
		cout << " 2. 4��(��ȭ : ���ٿ��)" << endl;
		cout << " 3. 9��(��ȭ : ų�� �θེ)" << endl;
		cout << " 4. ���" << endl;
		cout << "---------------------------------------------------" << endl;
		while (1) {
			cout << "�����ϰ��� �ϴ� ��ȣ �Է� >> ";
			cin >> order;
			switch (order)
			{
			case 1:
				CheckSits(1, false);
				if (ChangeOrder(ch, JohnWick, 5, 6)) return;
				break;
			case 2:
				CheckSits(2, false);
				if (ChangeOrder(ch, Rebound, 6, 7)) return;
				break;
			case 3:
				CheckSits(3, false);
				if (ChangeOrder(ch, KillingRomence, 7, 8)) return;
				break;
			case 4:
				cout << "\n\n\n\n\n\n" << endl;
				return;
				break;
			default:
				cout << "�߸��� ����� �ԷµǾ����ϴ�.";
				break;
			}

			cout << "\n" << endl;
		}
	}
}
//�ڸ��� ���� ���� ó���� �ϰ� ���� ���μ����� ť�� ����ִ� �Լ�
bool MovieManager::ChangeOrder(string before, Movie movie, int maxv, int maxh) {
	MovieProcess mp;
	char ver, check;
	int hor;
	cout << "\n���ϴ� �¼� �Է�(�Է� �� (A-5)�� : A 5) >> ";
	cin >> ver >> hor;
	ver = toupper(ver);
	if (ver < 'A' || ver >('A' + maxv - 1) || hor < 1 || hor > maxh) {
		cout << "���� �ڸ��Դϴ�. �ٽ� �ѹ� �Է��� �ּ���." << endl;
		return false;
	}
	else if ((movie == JohnWick && MovieSits_1[(ver - 'A')][hor - 1] != "") || (movie == Rebound && MovieSits_4[(ver - 'A')][hor - 1] != "") || (movie == KillingRomence && MovieSits_9[(ver - 'A')][hor - 1] != "")) {
		cout << "�� �ڸ��� �̹� ���Ű� �Ǿ� �ֽ��ϴ�." << endl;
		return true;
	}
	else {
		check = 0;
		while (toupper(check) != 'Y' && toupper(check) != 'N') {
			cout << "�¼� (" << ver << "-" << hor << ") �� �����մϴ�. ����Ͻðڽ��ϱ�(y/n)? >> ";
			cin >> check;
		}
		if (toupper(check) == 'Y') {
			mp.type = Change;
			mp.movie = movie;
			mp.before = before;
			string movCode;
			switch (movie)
			{
			case JohnWick:
				movCode = "JW";
				mp.seat = &(MovieSits_1[(ver - 'A')][hor - 1]);
				break;
			case Rebound:
				movCode = "RB";
				mp.seat = &(MovieSits_4[(ver - 'A')][hor - 1]);
				break;
			case KillingRomence:
				movCode = "KR";
				mp.seat = &(MovieSits_9[(ver - 'A')][hor - 1]);
				break;
			default:
				break;
			}
			mp.code = movCode + ver + to_string(hor) + to_string((rand() % 9000) + 1000);
			if (mvQ.EnQueue(mp))
				cout << "�ڸ� ���� ����Ǿ����ϴ�." << endl;
			else
				cout << "�ڸ� ���� ���� ������ �߻��߽��ϴ�. �ٽ� ������ �ּ���." << endl;
		}
		else cout << "��ҵǾ����ϴ�." << endl;
		cout << "\n\n\n\n\n\n" << endl;
		return true;
	}
}

//���� ��ȣ�� �Է¹޾� ���� ���μ����� ť�� ����ִ� �Լ�
void MovieManager::MovieTicketCancelOrder() {
	MovieProcess mp;
	string ch;
	CheckAllSits(false);
	if (!isTicketedSits()) {
		cout << "\n��ü �����Դϴ�. �ٲ� �ڸ��� �����ϴ�.\n\n\n\n\n" << endl;
		return;
	}
	while (1) {
		cout << "\n������ �¼� ���� ��ȣ �Է�(-1�� ���) >> ";
		cin >> ch;
		if (ch == "-1") return;
		if (!isCanFindTicketSits(ch)) {
			cout << "���� ������ ã�� �� �����ϴ�." << endl;
			continue;
		}
		mp.type = Cancel;
		mp.before = ch;
		if (mvQ.EnQueue(mp))
			cout << "�ڸ� ��� ����Ǿ����ϴ�." << endl;
		else
			cout << "�ڸ� ��� ���� ������ �߻��߽��ϴ�. �ٽ� ������ �ּ���." << endl;
		return;
	}
}

//���� ����� �����ϴ� �Լ�
bool MovieManager::MovieTicketing(MovieProcess mp) {
	if (mp.seat == nullptr || mp.code == "") return false;
	*(mp.seat) = mp.code;
	return true;
}
//���� ����� �����ϴ� �Լ�
bool MovieManager::MovieTicketChange(MovieProcess mp) {
	if (mp.seat == nullptr || mp.code == "" || mp.before == "") return false;
	Movie m;
	int h, v;	
	if (!FindTicketSits(mp.before, m, v, h)) return false;
	switch (m)
	{
	case JohnWick:
		MovieSits_1[v][h] = "";
		break;
	case Rebound:
		MovieSits_4[v][h] = "";
		break;
	case KillingRomence:
		MovieSits_9[v][h] = "";
		break;
	default:
		break;
	}
	*(mp.seat) = mp.code;
	return true;
}
//���� ����� �����ϴ� �Լ�
bool MovieManager::MovieTicketCancel(MovieProcess mp) {
	if (mp.before == "") return false;
	Movie m;
	int h, v;
	if (!FindTicketSits(mp.before, m, v, h)) return false;
	switch (m)
	{
	case JohnWick:
		MovieSits_1[v][h] = "";
		break;
	case Rebound:
		MovieSits_4[v][h] = "";
		break;	
	case KillingRomence:
		MovieSits_9[v][h] = "";
		break;
	default:
		break;
	}
	return true;
}

//���� ������ �� ���� �Լ��� �Ѱ��ִ� �Լ�
void MovieManager::OrderCheck(MovieProcess mp) {
	switch (mp.type)
	{
	default:
	case Ticketing:
		if (!MovieTicketing(mp)) {
			cout << "���� ����� ����� ����� ������� �ʾҽ��ϴ�. ����" << endl;
		}
		break;
	case Cancel:
		if (!MovieTicketCancel(mp)) {
			cout << "���� ����� ����� ����� ������� �ʾҽ��ϴ�. ���" << endl;
		}
		break;
	case Change:
		if (!MovieTicketChange(mp)) {
			cout << "���� ����� ����� ����� ������� �ʾҽ��ϴ�. ��ȯ" << endl;
		}
		break;
	}
}