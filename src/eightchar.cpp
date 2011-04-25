/*
 * eightchar.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: leon<lihow731@gmail.com>
 */

#include "eightchar.h"
#include <time.h>
#include <string.h>

eightchar::eightchar() {
	// TODO Auto-generated constructor stub
	memset((void *)&year, 0x0, sizeof(echarinfo));
	memset((void *)&mon,  0x0, sizeof(echarinfo));
	memset((void *)&day,  0x0, sizeof(echarinfo));
	memset((void *)&hour, 0x0, sizeof(echarinfo));

	tfl.readDB();

	time_t result;
	result = time(NULL);
	now = localtime(&result);

	setdate(now->tm_year,now->tm_mon,now->tm_mday,now->tm_hour);
}

eightchar::~eightchar() {
	// TODO Auto-generated destructor stub
}

eightchar::eightchar(int y, int m, int d, int h) {
#ifndef _WINDOWS
	bzero((void *)&year, sizeof(echarinfo));
	bzero((void *)&mon,  sizeof(echarinfo));
	bzero((void *)&day,  sizeof(echarinfo));
	bzero((void *)&hour, sizeof(echarinfo));
#else
	memset((void *)&year, 1, sizeof(echarinfo));
	memset((void *)&mon,  1, sizeof(echarinfo));
	memset((void *)&day,  1, sizeof(echarinfo));
	memset((void *)&hour, 1, sizeof(echarinfo));
#endif

	tfl.readDB();

	setdate(y,m,d,h);
}

int eightchar::setdate(int y, int m, int d, int h){

	year.input = y;
	mon.input  = m;
	day.input  = d;
	hour.input = h;

	int l = 0;

	// transfer y, m, d to lunar calendar.
	tfl.ToLunar(&y, &m, &d, &h, &l);

	// year and month must lunar calendar
	yearinfo(y,m,d);
	moninfo(y,m,d);
	dayinfo();
	hourinfo();

	hiddenSky(&year);
	hiddenSky(&mon);
	hiddenSky(&day);
	hiddenSky(&hour);

	year.longlife = longlifeinfo(day.sky,  year.earth);
	mon.longlife  = longlifeinfo(day.sky,  mon.earth );
	day.longlife  = longlifeinfo(day.sky,  day.earth );
	hour.longlife = longlifeinfo(day.sky,  hour.earth);

	year.sixty = sixtyNaYin(year.sky, year.earth);
	mon.sixty  = sixtyNaYin(mon.sky,  mon.earth );
	day.sixty  = sixtyNaYin(day.sky,  day.earth );
	hour.sixty = sixtyNaYin(hour.sky, hour.earth);

	year.empty = emptyinfo(year.sky, year.earth);
	mon.empty  = emptyinfo(mon.sky,  mon.earth );
	day.empty  = emptyinfo(day.sky,  day.earth );
	hour.empty = emptyinfo(hour.sky, hour.earth);

	return 0;
}

int eightchar::yearinfo(int y, int m, int d) {
	year.sky   = ( ( year.input + 6 ) % 10 );
	year.earth = ( ( year.input + 8 ) % 12 );

	return 0;
}

int eightchar::moninfo(int y, int m, int d) {
	mon.sky = ( ( ( ( year.sky + 1 ) % 5 ) * 2 ) + ( m - 1 ) ) % 10 ;
	mon.earth = ( m + 1 ) % 12;

	return 0;
}

int eightchar::dayinfo(void) {

	/*
	int isLeap(){
		y=$1
		A=`expr $y % 4`
		B=`expr $y % 100`
		C=`expr $y % 400`
		if ( test $A -eq 0 && test $B -ne 0 || test $C -eq 0 ) ; then
			return 0 #is leap
		else
			return 1
		fi
	}
	if `isLeap $y`  ; then
		ydays=$(( ${monYday_leap[$((m - 1))]} - 1 + d ))

	else
		ydays=$(( ${monYday_normal[$((m - 1))]} - 1 + d))
	fi
	if test $iH -ge 23 ; then
		tempDS=$(( ($tempS + $ydays ) % 10 + 1 ))
		tempDE=$(( ($tempE + $ydays ) % 12 + 1 ))
	else
		tempDS=$(( ($tempS + $ydays ) % 10 ))
		tempDE=$(( ($tempE + $ydays ) % 12 ))
	fi
	*/

	static int monYday_normal[]={0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
	static int monYday_leap[]  ={0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

	int ydays = 0;
	int A = year.input % 4;
	int B = year.input % 100;
	int C = year.input % 400;

	if ( ( A == 0 && B != 0 ) || C == 0  )
		ydays = monYday_normal[mon.input - 1] - 1 + day.input;
	else
		ydays = monYday_leap  [mon.input - 1] - 1 + day.input;

	// how many leap day from AD 0
	int countLeapY = ( ( ( year.input - 1 ) / 4 ) - ( ( year.input - 1 ) / 100) + ( ( year.input - 1 ) / 400 ));

	// The first day of the year.
	int firstdayS = ( 9 + (5 * year.input) + countLeapY ) % 10;
	int firstdayE = ( 9 + (5 * year.input) + countLeapY ) % 12;

	if ( hour.input >= 23 ) {
		day.sky   = ( ydays + firstdayS + 1 ) % 10;
		day.earth = ( ydays + firstdayE + 1 ) % 12;
	}
	else {
		day.sky   = ( ydays + firstdayS ) % 10;
		day.earth = ( ydays + firstdayE ) % 12;
	}


	return 0;
}

int eightchar::hourinfo(void) {
	//five mice dung
	int firstHour = (day.sky % 5) * 2;

	hour.earth = ( ( hour.input + 1 ) % 24 ) / 2;
	hour.sky   = ( hour.earth + firstHour ) % 10;
	return 0;
}

int eightchar::hiddenSky(struct echarinfo *einfo) {
	switch (einfo->sky)
	{
	case 0:
		einfo->hidden1 = 9;
		einfo->hidden2 = -1;
		einfo->hidden3 = -1;
		break;
	case 1:
		einfo->hidden1 = 6;
		einfo->hidden2 = 9;
		einfo->hidden3 = 7;
		break;
	case 2:
		einfo->hidden1 = 0;
		einfo->hidden2 = 2;
		einfo->hidden3 = 4;
		break;
	case 3:
		einfo->hidden1 = 1;
		einfo->hidden2 = -1;
		einfo->hidden3 = -1;
		break;
	case 4:
		einfo->hidden1 = 4;
		einfo->hidden2 = 1;
		einfo->hidden3 = 9;
		break;
	case 5:
		einfo->hidden1 = 2;
		einfo->hidden2 = 4;
		einfo->hidden3 = 6;
		break;
	case 6:
		einfo->hidden1 = 3;
		einfo->hidden2 = 5;
		einfo->hidden3 = -1;
		break;
	case 7:
		einfo->hidden1 = 5;
		einfo->hidden2 = 1;
		einfo->hidden3 = 3;
		break;
	case 8:
		einfo->hidden1 = 6;
		einfo->hidden2 = 4;
		einfo->hidden3 = 8;
		break;
	case 9:
		einfo->hidden1 = 7;
		einfo->hidden2 = -1;
		einfo->hidden3 = -1;
		break;
	case 10:
		einfo->hidden1 = 4;
		einfo->hidden2 = 7;
		einfo->hidden3 = 3;
		break;
	case 11:
		einfo->hidden1 = 8;
		einfo->hidden2 = -1;
		einfo->hidden3 = -1;
		break;

	}
	return 0;
}

int eightchar::longlifeinfo(int s, int e) {
	// the long life symbol at earth[0]
	int llTable[] = { 1, 6, 10, 9, 10, 9, 10, 0, 4, 3 };
	int ll = llTable[s];
	int order = 1;
	if ( s % 2 )
		order = -1;

	for ( int i = 0 ; i < e ; i ++) {
		ll += order;
	}

	return (ll + 12) % 12;
};

int eightchar::sixtyNaYin(int s, int e) {
	return ( ( ( ( s - e + 12 ) % 12 ) * 5 ) / 2 ) + ( s / 2);
}

int eightchar::emptyinfo(int s, int e) {
	int empty = -1;
	if ( s % 2 == e % 2 )
	{
		empty = ( e + ( 10 - s ) ) % 12;
		if ( s % 2 != empty % 2 )
			empty ++;
	} 
	
	return empty;
}