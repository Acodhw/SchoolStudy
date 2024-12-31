/*
* 파일 : Movie.h
* 특징 : 헤더 파일
* 설명 : 무비 정보 저장을 위한 자료 선언
*/

using std::string;

#ifndef mov
#define mov

enum Process
{
	Ticketing,
	Cancel,
	Change,
};

enum Movie
{
	JohnWick,
	Rebound,
	KillingRomence,
};


struct MovieProcess {
	Process type;
	Movie movie;
	string code;
	string * seat;
	string before;
	
	bool equals(MovieProcess p) {
		switch (type)
		{
		case Ticketing:			
			switch (p.type)
			{
			case Ticketing:
				return (movie == p.movie && seat == p.seat);
				break;
			case Cancel:
				return false;
				break;
			case Change:
				return (movie == p.movie && seat == p.seat);
				break;
			}
			break;
		case Change:
			switch (p.type)
			{
			case Ticketing:
				return (movie == p.movie && seat == p.seat);
				break;
			case Cancel:
				return (before == p.before);
				break;
			case Change:
				return (movie == p.movie && seat == p.seat && before == p.before); 
				break;
			}
			break;
		case Cancel:
			switch (p.type)
			{
			case Ticketing:
				return false;
				break;
			case Cancel:
				return (before == p.before);
				break;
			case Change:
				return (before == p.before);
				break;
			}
			break;
		}
		
	}
};

#endif // !1

