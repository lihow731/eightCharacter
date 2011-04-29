/*
 * ToFromLunar.h
 *
 *  Created on: Apr 29, 2011
 *      Author: Leon.L<lihow731@gmail.com>
 */
#pragma once
#define SISLEAP(year)  ( ( ( year % 4  == 0 ) && ( year % 100 != 0 ) )  || ( year % 400 == 0 ) )

class ToFromLunar
{
public:
	ToFromLunar(void);
	~ToFromLunar(void);
	void FromLunar( int*, int*, int*, int ); // year(in, out), mont(in, out)h, day(in, out), leap(in)
	void ToLunar( int*, int*, int*, int*, int*); // year(in, out), mont(in, out)h, day(in, out), hour(in), leap(out)
	void readDB ( );

private:
	int SMONTHDAY[13];// = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	
	struct Sday {
		int month;
		int day;
	};

	struct Lday {
		int month;
		int day;
		int leap;
	};

	struct MappingOfLunarToSolar {
		int year;
		struct Lday Smonth[12]; // From Solar to Lunar
		struct Sday Lmonth[13]; // put the day of Solar. Mean What day the lunar x.1 is?
		int leap;
	} stMOLTS[200];
};
