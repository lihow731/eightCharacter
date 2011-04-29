/*
 * Solarterm.cpp
 *
 *  Created on: Apr 29, 2011
 *      Author: leon
 */

#ifdef __WINDOWS
#include "StdAfx.h"
#endif
#include "Solarterm.h"
#include <string.h>
#include <stdio.h>

Solarterm::Solarterm(void)
{
	haveRead = 0;
	int months[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	memcpy( (void *)SMONTHDAY,(void *) months, sizeof(int) * 13 );
}

Solarterm::~Solarterm(void)
{
}

int Solarterm::readDB24()
{
		FILE *f;
		if ( ( f = fopen("db24", "rb") ) != NULL )
		{
			fread((void *)data24, sizeof(struct SOLARTERM24), 200 , f);	
			fclose(f);
			return 0;  // SUCCESS
		}
		else
		{
#ifdef __WINDOWS
			MessageBox(NULL,(LPCWSTR)"�䤣���ɮ�db24�A�o�N�y���G�Q�|�`���T��ܡC",(LPCWSTR)"File Not Found",MB_OK);
#else
			printf("Open db2 file failure!\n");
#endif
			return 1; // FAIL TO OPEN FILE;
		}

}

int Solarterm::searchSolarTerm(int y, int m, int d, int h)
{

	if ( y < 1900 || y > 2100 )
		return 1;  // INVALID YEAR
	if ( m < 1 || m > 12 )
		return 2;  // INVALID MONTH
	if ( d < 1 || d > SMONTHDAY[m] )
		return 3;  // INVALID DAY
	if ( h < 0 || h > 23 )
		return 4;  // INVALID HOUR


    if ( ! haveRead ) 
    {
         readDB24();
         haveRead = 1;
    }

    		
	int i, j;
	int after, before;
	int afterY = y;
	int beforeY = y;
	int solarTerm = 0;
	int c = -1;

//        case 1
//   n  ------------------
// 	      case *
//  n+1 ------------------
//        case 2

	for ( i = 0 ; i < 12  ; i ++ )
	{
		if ( data24[y-1900].sts[i*2].month == m )
		{
			solarTerm = i;
			if ( data24[y-1900].sts[i*2].day > d )
				c = 1;
			else if ( data24[y-1900].sts[ i * 2 + 1].day < d )
				c = 2;
			else if ( ( data24[y-1900].sts[i * 2].day <= d ) && ( d <= data24[y-1900].sts[i * 2 + 1].day ) )
			{
				if ( ( data24[y-1900].sts[i * 2].day == d ) && ( h < data24[y-1900].sts[i*2].hour ) )
					c = 1;
				else if ( ( d == data24[y-1900].sts[i * 2 + 1].day ) && ( data24[y-1900].sts[i*2].hour <= h ) )
					c = 2;
//				if ( data24[y-1900].sts[i * 2].hour  <= h  && h <= data24[y-1900    ].sts[i * 2 + 1].minute )
//				{
//					if ( mi < data24[y-1900].sts[i*2].minute  )
//						c = 1;
//					if ( data24[y-1900].sts[i*2].minute <= mi )
//						c = 2;
//				}

			}
			break;
		}
	}

	switch ( c )
	{
		case 1:
			if ( solarTerm  == 0 ) 
			{
				if ( y == 1900 )
					return 1;
				afterY = y - 1;
				after = 23;
			}
			else
				after = solarTerm  * 2 - 1;

			before = solarTerm  * 2;
			break;
		case 2:
			after = solarTerm  * 2 + 1;
			if ( solarTerm  == 11 )
			{
				if ( y == 2099 )
					return 1;
				beforeY = y + 1;
				before = 0;
			}
			else
				before = solarTerm  * 2 + 2;
			break;
		default:
			after = solarTerm  * 2;
			before = solarTerm  * 2 + 1;
			break;
	}
	currentTerm = after;
	c_year = afterY;
	c_month = data24[afterY-1900].sts[after].month;
	c_day = data24[afterY-1900].sts[after].day;
	c_hour = data24[afterY-1900].sts[after].hour;
	c_minute = data24[afterY-1900].sts[after].minute;
	c_second = data24[afterY-1900].sts[after].second;

	nextTerm = before;
	n_year = beforeY;
	n_month = data24[beforeY-1900].sts[before].month;
	n_day = data24[beforeY-1900].sts[before].day;
	n_hour = data24[beforeY-1900].sts[before].hour;
	n_minute = data24[beforeY-1900].sts[before].minute;
	n_second = data24[beforeY-1900].sts[before].second;

	return 0; //SUCCESS
}
