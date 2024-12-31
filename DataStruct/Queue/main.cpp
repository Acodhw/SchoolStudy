/*
* 파일 : main.c
* 특징 : cpp 메인함수 파일
* 설명 : 메인함수 및 기능 실행에 필요한 함수를 작성
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
		cout << "---------------영화 관리 프로그램-------------------" << endl;
		cout << " 1. 영화 예매" << endl;
		cout << " 2. 영화 예매 변경" << endl;
		cout << " 3. 영화 예매 취소" << endl;
		cout << " 4. 영화 좌석 현황 확인" << endl;
		cout << " 5. 프로그램 종료" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "실행하고자 하는 번호 입력 >> ";
		cin >> order;

		if(order == 5) break;

		movieManager.SetOrder(order);		
	}
	return 0;
}

//모든 자리가 비어있는 지 확인하는 함수
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
//티켓 번호를 가지고 그에 맞는 영화와 좌표 정보를 제공하는 함수
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
//티켓 번호를 가지고 그 티켓 번호가 있는 번호인지 확인하는 함수
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

//명령을 받아서 그 명령을 구분-다른 함수를 선언하고 큐 노드가 7개 이상일 때 처리를 명령하는 함수
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
		cout << "----------------------좌석 확인---------------------" << endl;
		cout << " 1. 전체 상영관 좌석 확인" << endl;
		cout << " 2. 지정 상영관 좌석 확인" << endl;
		cout << " 3. 취소" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "실행하고자 하는 번호 입력 >> ";
		cin >> order;
		if (order != 1 && order != 2) return;
		if (order == 1) {
			CheckAllSits();
			return;
		}
		cout << "\n\n\n\n\n\n" << endl;
		cout << "---------------확인 가능한 좌석 리스트---------------" << endl;
		cout << " 1. 1관(영화 : 존 윅4)" << endl;
		cout << " 2. 4관(영화 : 리바운드)" << endl;
		cout << " 3. 4관(영화 : 킬링 로멘스)" << endl;
		cout << " 4. 취소" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "실행하고자 하는 번호 입력 >> ";
		cin >> order;
		if (order != 1 && order != 2 && order != 3) return;
		CheckSits(order);
		break;
	default:
		cout << "잘못된 명령이 입력되었습니다.\n" << endl;
		break;
	}
	if (mvQ.count >= 7) {
		cout << "\n\n예약된 명령 처리중....." << endl;
		while (mvQ.count > 0) {
			OrderCheck(mvQ.DeQueue());
		}
		cout << "명령 처리 완료되었습니다......\n\n" << endl;
	}
}

//특정 영화의 자리 내역을 확인하는 함수
void MovieManager::CheckSits(int order, bool LastSkip) {
	switch (order)
	{
	case 1:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------1관(영화 : 존 윅 4)의 자리 내역---------------------" << endl;
		for (int i = 0; i < 5; i++) {
			cout << (char)(i + 'A') << "열 : ";
			for (int j = 0; j < 6; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_1[i][j] == "") {
					cout << "{         공석        } ";
				}
				else {
					cout << "{ 예매번호 : " << MovieSits_1[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	case 2:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------4관(영화 : 리바운드)의 자리 내역---------------------" << endl;
		for (int i = 0; i < 6; i++) {
			cout << (char)(i + 'A') << "열 : ";
			for (int j = 0; j < 7; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_4[i][j] == "") {
					cout << "{         공석        } ";
				}
				else {
					cout << "{ 예매번호 : " << MovieSits_4[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	case 3:
		cout << "\n\n\n\n\n\n" << endl;
		cout << "----------------------9관(영화 : 킬링 로멘스)의 자리 내역---------------------" << endl;
		for (int i = 0; i < 7; i++) {
			cout << (char)(i + 'A') << "열 : ";
			for (int j = 0; j < 8; j++) {
				cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
				if (MovieSits_9[i][j] == "") {
					cout << "{         공석        } ";
				}
				else {
					cout << "{ 예매번호 : " << MovieSits_9[i][j] << " } ";
				}
			}
			cout << endl;
		}
		break;
	default:
		cout << "해당 자리 내역이 없습니다." << endl;
		break;
	}
	if(LastSkip)cout << "\n\n\n\n\n\n" << endl;
}
//모든 영화 자리 내역을 확인하는 함수
void MovieManager::CheckAllSits(bool LastSkip) {
	cout << "----------------------다음과 같은 영화 자리가 검색되었습니다.---------------------\n" << endl;
	cout << "----------------------1관(영화 : 존 윅 4)의 자리 내역---------------------" << endl;
	for (int i = 0; i < 5; i++) {
		cout << (char)(i + 'A') << "열 : ";
		for (int j = 0; j < 6; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_1[i][j] == "") {
				cout << "{         공석        } ";
			}
			else {
				cout << "{ 예매번호 : " << MovieSits_1[i][j] << " } ";
			}
		}
		cout << endl;
	}

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------4관(영화 : 리바운드)의 자리 내역---------------------" << endl;
	for (int i = 0; i < 6; i++) {
		cout << (char)(i + 'A') << "열 : ";
		for (int j = 0; j < 7; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_4[i][j] == "") {
				cout << "{         공석        } ";
			}
			else {
				cout << "{ 예매번호 : " << MovieSits_4[i][j] << " } ";
			}
		}
		cout << endl;
	}

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------9관(영화 : 킬링 로멘스)의 자리 내역---------------------" << endl;
	for (int i = 0; i < 7; i++) {
		cout << (char)(i + 'A') << "열 : ";
		for (int j = 0; j < 8; j++) {
			cout << " (" << (char)(i + 'A') << "-" << j + 1 << ")";
			if (MovieSits_9[i][j] == "") {
				cout << "{         공석        } ";
			}
			else {
				cout << "{ 예매번호 : " << MovieSits_9[i][j] << " } ";
			}
		}
		cout << endl;
	}

	if(LastSkip) cout << "\n\n\n\n\n\n" << endl;
}

//예매 명령을 확인하고, 영화 정보를 아래 예매 수행 함수에 보내는 함수
void MovieManager::MovieTicketingOrder() {
	int order;

	cout << "\n\n\n\n\n\n" << endl;
	cout << "----------------------영화 목록---------------------" << endl;
	cout << " 1. 1관(영화 : 존 윅4)" << endl;
	cout << " 2. 4관(영화 : 리바운드)" << endl;
	cout << " 3. 9관(영화 : 킬링 로멘스)" << endl;
	cout << " 4. 취소" << endl;
	cout << "---------------------------------------------------" << endl;
	while (1) {
		cout << "예매하고자 하는 번호 입력 >> ";
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
			cout << "잘못된 명령이 입력되었습니다.";
			break;
		}

		cout << "\n" << endl;
	}
}
//자리에 대한 예외처리를 하고 예매 프로세스를 큐에 집어넣는 함수
bool MovieManager::TicketingOrder(Movie movie, int maxv, int maxh) {
	MovieProcess mp;
	char ver, check;
	int hor;
	
	cout << "\n원하는 좌석 입력(입력 예 (A-5)석 : A 5) >> ";
	cin >> ver >> hor;
	ver = toupper(ver);
	if (ver < 'A' || ver >('A' + maxv - 1) || hor < 1 || hor > maxh) {
		cout << "없는 자리입니다. 다시 한번 입력해 주세요." << endl;
		return false;
	}
	else if ((movie == JohnWick && MovieSits_1[(ver - 'A')][hor - 1] != "") || (movie == Rebound && MovieSits_4[(ver - 'A')][hor - 1] != "") || (movie == KillingRomence && MovieSits_9[(ver - 'A')][hor - 1] != "")) {
		cout << "그 자리는 이미 예매가 되어 있습니다." << endl;
		return true;
	}
	else {
		check = 0;
		while (toupper(check) != 'Y' && toupper(check) != 'N') {
			cout << "좌석 (" << ver << "-" << hor << ") 에 예매합니다. 계속하시겠습니까(y/n)? >> ";
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
				cout << "자리 예매가 예약되었습니다." << endl;
			else
				cout << "자리 예매 도중 오류가 발생했습니다. 다시 실행해 주세요." << endl;
		}
		else cout << "취소되었습니다." << endl;
		cout << "\n\n\n\n\n\n" << endl;
		return true;
	}
}

//변경 명령을 확인하고, 변경을 원하는 기존 예매 번호와 영화 정보를 아래 변경 수행 함수에 보내는 함수
void MovieManager::MovieTicketChangeOrder() {
	string ch;
	CheckAllSits(false);
	if (!isTicketedSits()) {
		cout << "\n전체 공석입니다. 바꿀 자리가 없습니다.\n\n\n\n\n" << endl;
		return;
	}
	while (1) {
		cout << "\n변경할 좌석 예매 번호 입력(-1은 취소) >> ";
		cin >> ch;
		if (ch == "-1") return;
		if (!isCanFindTicketSits(ch)) {
			cout << "예매 정보를 찾을 수 없습니다." << endl;
			continue;
		}

		int order;
		cout << "\n\n\n\n\n\n" << endl;
		cout << "--------------변경하고자 하는 영화 목록--------------" << endl;
		cout << " 1. 1관(영화 : 존 윅4)" << endl;
		cout << " 2. 4관(영화 : 리바운드)" << endl;
		cout << " 3. 9관(영화 : 킬링 로멘스)" << endl;
		cout << " 4. 취소" << endl;
		cout << "---------------------------------------------------" << endl;
		while (1) {
			cout << "예매하고자 하는 번호 입력 >> ";
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
				cout << "잘못된 명령이 입력되었습니다.";
				break;
			}

			cout << "\n" << endl;
		}
	}
}
//자리에 대한 예외 처리를 하고 변경 프로세스를 큐에 집어넣는 함수
bool MovieManager::ChangeOrder(string before, Movie movie, int maxv, int maxh) {
	MovieProcess mp;
	char ver, check;
	int hor;
	cout << "\n원하는 좌석 입력(입력 예 (A-5)석 : A 5) >> ";
	cin >> ver >> hor;
	ver = toupper(ver);
	if (ver < 'A' || ver >('A' + maxv - 1) || hor < 1 || hor > maxh) {
		cout << "없는 자리입니다. 다시 한번 입력해 주세요." << endl;
		return false;
	}
	else if ((movie == JohnWick && MovieSits_1[(ver - 'A')][hor - 1] != "") || (movie == Rebound && MovieSits_4[(ver - 'A')][hor - 1] != "") || (movie == KillingRomence && MovieSits_9[(ver - 'A')][hor - 1] != "")) {
		cout << "그 자리는 이미 예매가 되어 있습니다." << endl;
		return true;
	}
	else {
		check = 0;
		while (toupper(check) != 'Y' && toupper(check) != 'N') {
			cout << "좌석 (" << ver << "-" << hor << ") 에 예매합니다. 계속하시겠습니까(y/n)? >> ";
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
				cout << "자리 변경 예약되었습니다." << endl;
			else
				cout << "자리 변경 도중 오류가 발생했습니다. 다시 실행해 주세요." << endl;
		}
		else cout << "취소되었습니다." << endl;
		cout << "\n\n\n\n\n\n" << endl;
		return true;
	}
}

//예매 번호를 입력받아 삭제 프로세스를 큐에 집어넣는 함수
void MovieManager::MovieTicketCancelOrder() {
	MovieProcess mp;
	string ch;
	CheckAllSits(false);
	if (!isTicketedSits()) {
		cout << "\n전체 공석입니다. 바꿀 자리가 없습니다.\n\n\n\n\n" << endl;
		return;
	}
	while (1) {
		cout << "\n변경할 좌석 예매 번호 입력(-1은 취소) >> ";
		cin >> ch;
		if (ch == "-1") return;
		if (!isCanFindTicketSits(ch)) {
			cout << "예매 정보를 찾을 수 없습니다." << endl;
			continue;
		}
		mp.type = Cancel;
		mp.before = ch;
		if (mvQ.EnQueue(mp))
			cout << "자리 취소 예약되었습니다." << endl;
		else
			cout << "자리 취소 도중 오류가 발생했습니다. 다시 실행해 주세요." << endl;
		return;
	}
}

//예매 명령을 수행하는 함수
bool MovieManager::MovieTicketing(MovieProcess mp) {
	if (mp.seat == nullptr || mp.code == "") return false;
	*(mp.seat) = mp.code;
	return true;
}
//변경 명령을 수행하는 함수
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
//삭제 명령을 수행하는 함수
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

//받은 정보를 각 수행 함수에 넘겨주는 함수
void MovieManager::OrderCheck(MovieProcess mp) {
	switch (mp.type)
	{
	default:
	case Ticketing:
		if (!MovieTicketing(mp)) {
			cout << "다음 예약된 명령이 제대로 수행되지 않았습니다. 예매" << endl;
		}
		break;
	case Cancel:
		if (!MovieTicketCancel(mp)) {
			cout << "다음 예약된 명령이 제대로 수행되지 않았습니다. 취소" << endl;
		}
		break;
	case Change:
		if (!MovieTicketChange(mp)) {
			cout << "다음 예약된 명령이 제대로 수행되지 않았습니다. 전환" << endl;
		}
		break;
	}
}