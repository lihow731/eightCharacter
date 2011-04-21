#ifdef __WINDOWS__
#include "StdAfx.h"
#else
#include <string.h>
#include <stdio.h>
#endif
#include "ToFromLunar.h"


ToFromLunar::ToFromLunar(void)
{
	int smonthday[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	memcpy((void *) SMONTHDAY, (void *) smonthday, 13*sizeof(int));
}

ToFromLunar::~ToFromLunar(void)
{
}

void ToFromLunar::FromLunar( int *y, int *m, int *d, int isleap)
{
	if ( ( *y < 1900 ) || ( *y > 2100 ) ) 
		return;
	if ( ( *m < 0 ) || ( *m > 12 ) )
		return;
	if ( ( *d < 1 ) || ( *d > 31 ) )
		return;

	int leap = stMOLTS[*y-1900].leap;
	int Syear = *y;
	int Smonth = 0 ;
	int Sday = 0 ;

	if ( leap == 0 )
	{
		Smonth = stMOLTS[*y-1900].Lmonth[*m - 1].month;
		Sday = stMOLTS[*y-1900].Lmonth[*m - 1].day + (*d) - 1;
	}
	else
	{
		if ( (  ( isleap == 1 ) && ( *m == leap ) ) || ( (  isleap == 0 )  && ( *m > leap )  ) )
		{
			Smonth = stMOLTS[*y-1900].Lmonth[*m ].month;
			Sday = stMOLTS[*y-1900].Lmonth[*m ].day + *d - 1;
		}
		else if ( ( isleap == 0 ) && (*m <= leap ))
		{	
			Smonth = stMOLTS[*y-1900].Lmonth[*m - 1].month;
			Sday = stMOLTS[*y-1900].Lmonth[*m - 1].day + *d - 1;
		}
//		else
//		{
//			printf("No defined!!\n");
//		}
	}
	if ( Sday > SMONTHDAY[Smonth] )
	{
		Sday -= SMONTHDAY[Smonth];
		Smonth ++;
		if ( Smonth >= 13 )
			Smonth = ( Smonth % 12 );
	}

	if ( ( *m > 10 ) && ( Smonth < 3 ) )
		Syear ++ ;

	*y = Syear;
	*m = Smonth;
	*d = Sday;
}

void ToFromLunar::ToLunar( int *y, int *m, int *d, int *h, int *l)
{
	if ( ( *y < 1900 ) || ( *y > 2100 ) ) 
		return;
	if ( ( *m < 1 ) || ( *m > 12 ) )
		return;
	if ( ( *d < 1 ) || ( *d > SMONTHDAY[*m] ) )
		return;
	if ( ( *h < 0)  || ( *h > 24 ) )
		return;

	if ( *h > 23 )
	{
		*d ++;
		if ( *d > SMONTHDAY[*m] )
		{
			*m ++;
			*d = 1;
			if ( *m > 12 )
			{
				*y ++;
				*m = 1;
			}
		}
	};

	int leap   = stMOLTS[*y-1900].leap;
	int Lmonth = 0;
	int Lday   = 0;
	int LtempL = stMOLTS[*y-1900].Smonth[*m - 1].leap;
	int LtempD = 1;	
	int LtempM; 
	int LtempY;
	int tmp;	
	int tmp2;	
	
	Lday   = stMOLTS[*y-1900].Smonth[*m - 1].day + (*d) - 1;
	Lmonth = stMOLTS[*y-1900].Smonth[*m - 1].month;

	// example: 1902. 10. 31 => 1902. 10. 1
	// must to calculate the day of month of lunar then find correct day when Lday > 29.
	if ( Lday > 29 )
	{
		// if next month is leap month..
		if ( leap != 0 && leap == Lmonth && LtempL == 0  )
		{
			LtempM = tmp = stMOLTS[*y-1900].Smonth[*m - 1].month;	
			LtempY = (LtempM > *m)?(*y-1):*y;
			tmp2 = LtempL;
			LtempL = 1;
		}
		else
		{
			LtempM = tmp = ( stMOLTS[*y-1900].Smonth[*m - 1].month % 12 ) + 1;	
			LtempY = (LtempM > *m)?(*y-1):*y;
			tmp2 = LtempL;
			LtempL = 0;
		}
		FromLunar( &LtempY, &LtempM, &LtempD, LtempL); // 1902.9.1

		if ( LtempM == *m )
		{
			if ( LtempD > *d ) 
			{
				Lday = 30;   // day 30
				LtempL = tmp2;
			}
			else
			{
				Lday = 1 + ( *d - LtempD );
				Lmonth = tmp ;
			}
		}
		else if ( LtempM > *m )
		{
			Lmonth = ( Lmonth % 12 ) + 1 ;
			LtempD = 1;

			// if next month is leap month.. (there are some bug, here!!)
			// example:How to prcess 4 5 5(leap)?
			if ( leap != 0 && leap == Lmonth && LtempL == 0  )
			{
				LtempM = stMOLTS[*y-1900].Smonth[*m - 1].month;	
				LtempY = ((LtempM > *m)?(*y-1):*y ); 
				LtempL = 1;
			}
			else
			{
				LtempM = (( stMOLTS[*y-1900].Smonth[*m - 1].month % 12 ) + 2 );
				LtempY = ((LtempM > *m)?(*y-1):*y ); 
				LtempL = 0;
			}
			FromLunar( &LtempY, &LtempM, &LtempD, LtempL); // 1902.10.1



			if ( LtempD <= *d && LtempM == *m )
			{
				Lday = 1 + ( *d - LtempD );	
			}
		}
	}
	if ( Lmonth > *m )
		*y = *y - 1;
	*m = Lmonth;
	*d = Lday;

	if ( leap == Lmonth && LtempL == 1 )
		*l = 1;
	else 
		*l = 0;
	
}

void  ToFromLunar::readDB()
{
	FILE *f;
	if ( ( f = fopen("db2", "rb") ) != NULL )
	{
//		printf("Open db2 successed!!\n");
		fread((void *)stMOLTS, sizeof(MappingOfLunarToSolar), 200 , f);	
		fclose(f);
		
	}
	else
	{
#ifdef __WINDOWS__
		MessageBox(NULL,(LPCWSTR)L"�䤣���ɮ�db2�A�o�i��y���{�������`����", (LPCWSTR)L"File not found", MB_ICONINFORMATION | MB_OK );
#else
		printf("Open db2 file failure!\n");
#endif
	}

}
