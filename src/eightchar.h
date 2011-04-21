/*
 * eightchar.h
 *
 *  Created on: Apr 19, 2011
 *      Author: leon<lihow731@gmail.com>
 */

#ifndef EIGHTCHAR_H_
#define EIGHTCHAR_H_

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

class eightchar {
public:
	eightchar();
	eightchar(int y, int m, int d, int h);
	~eightchar();
	int setdate(int y, int m, int d, int h);

	//
	struct echarinfo year, mon, day, hour;

private:
	struct tm* now;
	int yearinfo(int y, int m, int d);
	int moninfo (int y, int m, int d);
	int dayinfo (void);
	int hourinfo(void);
	int hiddenSky(struct echarinfo *einfo);
};


#endif /* EIGHTCHAR_H_ */
