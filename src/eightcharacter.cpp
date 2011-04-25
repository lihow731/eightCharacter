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

/*
static wchar_t *sixtyNaYin[] = { L"海中金",L"大溪水",L"覆燈火",L"沙中金",L"泉中水",L"山頭火",L"澗下水",L"爐中火",L"沙中土",L"天河水",L"山下火",L"屋上土",L"霹靂火",L"城頭土",L"大林木",L"天上火",L"大驛土",L"平地火",L"壁上土",L"松柏木",L"白蠟金",L"路旁土",L"石榴木",L"釵釧金",L"桑柘木",L"金箔金",L"長流水",L"楊柳木",L"劍鋒金",L"大海水"};
static wchar_t *LONGLIFE[]   = { L"長生", L"沐浴", L"冠帶", L"臨官", L"帝旺", L"衰　", L"病　", L"死　", L"墓　", L"絕　", L"胎　", L"養　"};
static wchar_t *SKY[10]      = { L"甲",L"乙",L"丙",L"丁",L"戊",L"己",L"庚",L"辛",L"壬",L"癸"};
static wchar_t *EARTH[12]    = { L"子",L"丑",L"寅",L"卯",L"辰",L"巳",L"午",L"未",L"申",L"酉",L"戌",L"亥"};
 */

int pinfo(struct echarinfo info) {
	cout << info.sky << " " << info.earth << "\t" << info.longlife << " " << info.sixty << "\t" << info.hidden1 << info.hidden2 << info.hidden3 << endl;
	return 0;
}

int main(int argc, char *argv[]) {
	if ( argc > 4 ) {
		eightchar e(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
		cout << "year : ";
		pinfo(e.year);
		cout << "month: ";// << e.mon.input << "\t" << e.mon.sky << " " << e.mon.earth << endl;
		pinfo(e.mon);
		cout << "day  : ";// << e.day.input << "\t" << e.day.sky << " " << e.day.earth << endl;
		pinfo(e.day);
		cout << "hour : ";// << e.hour.input << "\t" << e.hour.sky << " " << e.hour.earth << endl;
		pinfo(e.hour);

	}

	return 0;
}
