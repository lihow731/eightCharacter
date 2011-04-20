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

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	eightchar e(1978, 7 , 31, 10);
	cout << "year : " << e.year.input << "\t" << e.year.sky << " " << e.year.earth << endl;
	cout << "month: " << e.mon.input << "\t" << e.mon.sky << " " << e.mon.earth << endl;
	cout << "day  : " << e.day.input << "\t" << e.day.sky << " " << e.day.earth << endl;
	cout << "hour : " << e.hour.input << "\t" << e.hour.sky << " " << e.hour.earth << endl;
	return 0;
}
