//============================================================================
// Name        : eightcharacter.cpp
// Author      : Leon <lihow731@gmail.com>
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "eightchar.h"
using namespace std;

int pinfo(struct echarinfo info) {
	cout << info.sky << " " << info.earth << "\t" << info.longlife << " " << info.sixty << "\t" << info.hidden1 << info.hidden2 << info.hidden3 << endl;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	eightchar e(1978, 7, 31, 10);
	cout << "year : ";
	pinfo(e.year);
	cout << "month: ";// << e.mon.input << "\t" << e.mon.sky << " " << e.mon.earth << endl;
	pinfo(e.mon);
	cout << "day  : ";// << e.day.input << "\t" << e.day.sky << " " << e.day.earth << endl;
	pinfo(e.day);
	cout << "hour : ";// << e.hour.input << "\t" << e.hour.sky << " " << e.hour.earth << endl;
	pinfo(e.hour);

	char str[3];
	sprintf(str,"%d",e.year.sky);
	setenv("ec_ys",str,1);
	sprintf(str,"%d",e.year.earth);
	setenv("ec_ye",str,1);
	sprintf(str,"%d",e.mon.sky);
	setenv("ec_ms",str,1);
	sprintf(str,"%d",e.mon.earth);
	setenv("ec_me",str,1);
	sprintf(str,"%d",e.day.sky);
	setenv("ec_ds",str,1);
	sprintf(str,"%d",e.day.earth);
	setenv("ec_de",str,1);
	sprintf(str,"%d",e.hour.sky);
	setenv("ec_hs",str,1);
	sprintf(str,"%d",e.hour.earth);
	setenv("ec_he",str,1);
	return 0;
}
