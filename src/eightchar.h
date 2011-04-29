/*
 * eightchar.h
 *
 *  Created on: Apr 29, 2011
 *      Author: Leon.L<lihow731@gmail.com>
 */

#ifndef EIGHTCHAR_H_
#define EIGHTCHAR_H_

#include "ToFromLunar.h"
#include "Solarterm.h"

struct echarinfo {
	int input;
	int sky;
	int earth;
	int longlife;
	int sixty;
	int empty;
	int hidden1;
	int hidden2;
	int hidden3;
};

struct solarterminfo{
	int  month  ;
	int  day    ;
	int  hour   ;
	int  minute ;
	int  second ;
};

class eightchar {
public:
	eightchar();
	eightchar(int y, int m, int d, int h);
	~eightchar();
	int setdate(int y, int m, int d, int h);

	// public information
	struct echarinfo year, mon, day, hour;
	struct solarterminfo lastSolarTerm, nextSolarTerm;
	int    sex;

private:
	struct tm* now;
	int yearinfo(int y, int m, int d);
	int moninfo (int y, int m, int d);
	int dayinfo (void);
	int hourinfo(void);
	int hiddenSky(struct echarinfo *einfo);
	int longlifeinfo(int s, int e);
	int sixtyNaYin(int s, int e);
	int emptyinfo(int s, int e);

	ToFromLunar tfl;
	Solarterm st;
};


#endif /* EIGHTCHAR_H_ */
