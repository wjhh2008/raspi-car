#!/bin/bash

#Split paramters with "&"
OFS=$IFS
IFS="${IFS}&"
set $QUERY_STRING
#IFS=$OFS
#Args="$*"
#$* = $QUERY_STRING
echo $QUERY_STRING
echo $*
#Set Motor PWM Range:0-4000 0-2000 Is backward 2000-4000 Is forward 
if [ "$1" -le "4000" ] && [ "$1" -ge "2000" ]; then
	echo 1=$[$1-2000] > /dev/servoblaster
	echo 3=0 > /dev/servoblaster
elif [ "$1" -ge "0" ] && [ "$1" -lt "2000" ]; then
	echo 1=0 > /dev/servoblaster
	echo 3=$[2000-$1] > /dev/servoblaster
elif [ "$1" -lt "0" ]; then
	echo 1=0 > /dev/servoblaster
	echo 3=2000 > /dev/servoblaster
elif [ "$1" -gt "4000" ]; then
    echo 1=2000 > /dev/servoblaster
	echo 3=0 > /dev/servoblaster
fi

#Set Servo PWM Range:150-250
if [ "$2" -le "250" ] && [ "$2" -ge "50" ]; then
	echo 2=$2 > /dev/servoblaster
#   echo "ok2"
elif [ "$2" -gt "250" ]; then
	echo 2=250 > /dev/servoblaster
elif [ "$2" -lt "50" ]; then
	echo 2=50 > /dev/servoblaster
fi

#IFS=$OFS
echo motor:$1 servo:$2
