#include <stdio.h>
#include <time.h>
#include <wchar.h>

wchar_t *SKY=L"甲乙丙丁戊己庚辛壬癸";
wchar_t *EARTH=L"子丑寅卯辰巳午未申酉戌亥";

static inline int isLeap(int y)
{

	return ( y & 3 ) == 0 && ( y % 100 ) != 0 ||  ( y % 400 ) == 0; 

}

const unsigned short int __mon_yday[2][13] =
{
    /* Normal years.  */
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    /* Leap years.  */
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

int yday(int year, int month, int day)
{
	int mon_yday = ((__mon_yday[isLeap (year)][month - 1]) - 1);
  	int lmday = day;
	return ( mon_yday + lmday );
}

int daySky(int year, int month, int day)
{
	int yd = yday(year, month, day);
	return ( 2 + yd ) % 10;
}

int dayEarth(int year, int month, int day)
{
	int yd = yday(year, month, day);
	return ( 4 + yd ) % 12;
}


int main( int argc, char **argv)
{
	time_t result;
	result = time(NULL);
	struct tm* brokentime = localtime(&result);
	printf("%s%ju secs since the Epoch\n", asctime(brokentime), (long)result); 
	printf("Today is the %d day of this year.\n", brokentime->tm_yday);
	printf("---------------------------------\n");

	wprintf(L"%s",SKY);		

	if ( argc >=4 )
	{
		printf( "The day is the %d day of %d.\n", yday(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])), atoi(argv[1]));
		printf( "This year is%sleap year.\n",isLeap(atoi(argv[1]))?" ":" not ");
		//inputDate(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),0,0,0);
		//printf("argv[1] = %d\n", atoi(argv[1]));
		printf("The day is %d, %d\n",( daySky(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) ), ( dayEarth(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]))));
	}

	return(0);

}