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
	bzero((void *)&year, sizeof(echarinfo));
	bzero((void *)&mon,  sizeof(echarinfo));
	bzero((void *)&day,  sizeof(echarinfo));
	bzero((void *)&hour, sizeof(echarinfo));

	time_t result;
	result = time(NULL);
	now = localtime(&result);

	year.input = now->tm_year;
	mon.input  = now->tm_mon;
	day.input  = now->tm_mday;
	hour.input = now->tm_hour;

}

eightchar::~eightchar() {
	// TODO Auto-generated destructor stub
}

eightchar::eightchar(int y, int m, int d, int h) {
	bzero((void *)&year, sizeof(echarinfo));
	bzero((void *)&mon,  sizeof(echarinfo));
	bzero((void *)&day,  sizeof(echarinfo));
	bzero((void *)&hour, sizeof(echarinfo));

	setdate(y,m,d,h);
}

int eightchar::setdate(int y, int m, int d, int h){

	year.input = y;
	mon.input  = m;
	day.input  = d;
	hour.input = h;

	yearinfo();
	moninfo();
	dayinfo();
	hourinfo();

	return 0;
}

int eightchar::yearinfo(void) {
	year.sky   = ( ( year.input + 6 ) % 10 );
	year.earth = ( ( year.input + 8 ) % 12 );

	return 0;
}

int eightchar::moninfo(void) {
	mon.sky = ( ( ( ( year.sky + 1 ) % 5 ) * 2 ) + ( mon.input - 1 ) ) % 10 ;
	mon.earth = ( mon.input + 1 ) % 12;

	return 0;
}

int eightchar::dayinfo(void) {
	return 0;
}

int eightchar::hourinfo(void) {
	return 0;
}

int eightchar::hiddenSky(struct echarinfo einfo) {
	switch (einfo.sky)
	{
	case 0:
		einfo.hidden1 = 9;
		einfo.hidden2 = -1;
		einfo.hidden3 = -1;
		break;
	case 1:
		einfo.hidden1 = 6;
		einfo.hidden2 = 9;
		einfo.hidden3 = 7;
		break;

	}
	return 0;
}
