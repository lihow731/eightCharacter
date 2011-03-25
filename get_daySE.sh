#!/bin/bash

# Leon.L <lihow731@gmail.com>


SKY=(甲 乙 丙 丁 戊 己 庚 辛 壬 癸)
EARTH=(子 丑 寅 卯 辰 巳 午 未 申 酉 戌 亥)

monYday_normal=(0 31 59 90 120 151 181 212 243 273 304 334 365)
monYday_leap=(0 31 60 91 121 152 182 213 244 274 305 335 366)

iY=$1
iM=$2
iD=$3
iH=$4

Y1900S=0
Y1900E=10

Y1950S=2
Y1950E=8

Y2000S=4
Y2000E=6

Y2011S=2
Y2011E=4

tempS=$Y2011S
tempE=$Y2011E

tempYS=0
tempYE=0

tempDS=0
tempDE=0

tempHS=0
tempHE=0


#=============================================================================================
# The sky of month and earth of hour must use lunar's database or astronomical calculation.
# 
#=============================================================================================
yearSE(){
	tempYS=$(( ( iY + 6 ) % 10 ))
	tempYE=$(( ( iY + 8 ) % 12 ))
}

# the input of this function must lunar's year and month.
monthSE(){
	# five tiger
	case $tempYS in
	0 | 5)
		tempMS=2
	;;
	1 | 6)
		tempMS=4
	;;
	2 | 7)
		tempMS=6
	;;
	3 | 8)
		tempMS=8
	;;
	4 | 9)
		tempMS=0
	;;
	esac

	tempME=$(( ( ( iM + 1 ) % 12 ) ))
	tempMS=$(( ( tempMS + tempME ) % 10 ))
	#Unfinished
}

#=============================================================================================
# We can compute the sky of day, earth of day, sky of hour and earth of hour. 
#=============================================================================================
isLeap(){
	y=$1
	A=`expr $y % 4`
	B=`expr $y % 100`
	C=`expr $y % 400`
	if ( test $A -eq 0 && test $B -ne 0 || test $C -eq 0 ) ; then
		return 0 #is leap 
	else
		return 1
	fi
}

# from 2011 to find the sky and earth of the first day of 1900
computeD_dec(){
	for y in `seq 2010 -1 1900`
	do
		if `isLeap $y`  ; then
			#echo $y is leap year.
			echo  $((y)) is ${SKY[$(( tempS = ($tempS + 4) % 10))]}  ${EARTH[$(( tempE = ($tempE + 6) % 12 ))]}
		else
			echo  $((y)) is ${SKY[$(( tempS = ($tempS + 5) % 10))]}  ${EARTH[$(( tempE = ($tempE + 7) % 12 ))]}
		fi
	
	done
}

# compute the sky and earth of the first day of certain year base on 1900.
computeD_inc(){

	# for speedup
	local startY=0
	if test $iY -ge 2000 ;then
		tempS=$Y2000S
		tempE=$Y2000E
		startY=2000
	elif test $iY -ge 1950 ; then
		tempS=$Y1950S
		tempE=$Y1950E
		startY=1950
	else
		tempS=$Y1900S
		tempE=$Y1900E
		startY=1900
	fi	

	if test ! -z $1 && test $1 -gt 1900  ; then
		target=`expr $1 - 1`
	else
		target=2050
	fi

	for y in `seq $startY $target`
	do
		if `isLeap $y`  ; then
			#echo $y is leap year.
			#echo $((y + 1)) is ${SKY[$(( tempS = ($tempS + 6) % 10))]}  ${EARTH[$(( tempE = ($tempE + 6) % 12 ))]} > /dev/null
			tempS=$(( ($tempS + 6) % 10 ))
			tempE=$(( ($tempE + 6) % 12 ))
		else
			#echo $((y + 1)) is ${SKY[$(( tempS = ($tempS + 5) % 10))]}  ${EARTH[$(( tempE = ($tempE + 5) % 12 ))]} > /dev/null
			tempS=$(( ($tempS + 5) % 10 ))  
			tempE=$(( ($tempE + 5) % 12 ))
		fi
	
	done
	
	#echo $((y + 1)) is ${SKY[$((tempS))]}  ${EARTH[$((tempE))]}
}

# input year, month and day
# output the Sky of day and Earth of day.
daySE(){
	# using yday to find the Sky of day and Earth of day.
	local y=$1
	local m=$2
	local d=$3
	local ydays=0

	if `isLeap $y`  ; then
		#echo $y is leap year.
		#echo $(( ydays=${monYday_leap[$((m - 1))]} - 1 + d ))
		ydays=$(( ${monYday_leap[$((m - 1))]} - 1 + d ))
		
	else
		#echo $(( ydays=${monYday_normal[$((m - 1))]} - 1 + d))
		ydays=$(( ${monYday_normal[$((m - 1))]} - 1 + d))
	fi

	if test $iH -ge 23 ; then
		tempDS=$(( ($tempS + $ydays ) % 10 + 1 ))
		tempDE=$(( ($tempE + $ydays ) % 12 + 1 ))
	else
		tempDS=$(( ($tempS + $ydays ) % 10 ))
		tempDE=$(( ($tempE + $ydays ) % 12 ))
	fi
	
}

# input the sky of day and the hour number.
# output the sky of hour and the earth of hour.
hourSE(){
	#five mouse
	case $1	in
	0 | 5)
		tempHS=0
	;;
	1 | 6)
		tempHS=2
	;;
	2 | 7)
		tempHS=4
	;;
	3 | 8)
		tempHS=6
	;;
	4 | 9)
		tempHS=8
	;;
	esac
	tempHE=$(( ( ( iH + 1 ) % 24 ) / 2 ))
	tempHS=$(( ( tempHS + tempHE ) % 10 ))
}


if test $# -ge 1 ; then
	yearSE
	computeD_inc $iY
fi
if test $# -ge 3 ; then
	#echo $tempS $tempE
	daySE $iY $iM $iD
	hourSE $tempDS $iH
	echo  $iY $iM $iD $iH is ${SKY[$tempYS]}${EARTH[$tempYE]} 年 # ${SKY[$tempHS]}${EARTH[$tempHE]} 月
	echo  $iY $iM $iD $iH is ${SKY[$tempDS]}${EARTH[$tempDE]} 日 ${SKY[$tempHS]}${EARTH[$tempHE]} 時
fi

