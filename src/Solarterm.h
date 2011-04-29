#pragma once

class Solarterm
{
public:
	Solarterm(void);
	~Solarterm(void);
	int readDB24();
	int searchSolarTerm(int y, int m, int d, int h);
	int currentTerm;
	int c_year;
	int c_month;
	int c_day;
	int c_hour;
	int c_minute;
	int c_second;
	int nextTerm;
	int n_year;
	int n_month;
	int n_day;
	int n_hour;
	int n_minute;
	int n_second;

	struct SOLARTERMS{
		int  month  ;
		int  day    ;
		int  hour   ;
		int  minute ;
		int  second ;
	};

private:
	int SMONTHDAY[13];

	struct SOLARTERM24 {
		int year;
		struct SOLARTERMS sts[24];
	} data24[200];

	int haveRead;
};
