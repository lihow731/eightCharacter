//============================================================================
// Name        : eightcharacter.cpp
// Author      : Leon <lihow731@gmail.com>
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "eightchar.h"
using namespace std;

int pinfo(struct echarinfo info) {
	cout << info.sky << " " << info.earth << "\t" << info.longlife << " " << info.sixty << "\t" << info.hidden1 << info.hidden2 << info.hidden3 << endl;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	eightchar e(2011, 4 , 21, 14);
	cout << "year : ";
	pinfo(e.year);
	cout << "month: ";// << e.mon.input << "\t" << e.mon.sky << " " << e.mon.earth << endl;
	pinfo(e.mon);
	cout << "day  : ";// << e.day.input << "\t" << e.day.sky << " " << e.day.earth << endl;
	pinfo(e.day);
	cout << "hour : ";// << e.hour.input << "\t" << e.hour.sky << " " << e.hour.earth << endl;
	pinfo(e.hour);
	return 0;
}
