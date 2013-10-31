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
#Set Motor PWM Range:0-2047 0-1023 Is backward 1024-2047 Is forward 
if [ "$1" -le "2047" ] && [ "$1" -ge "1024" ]; then
	gpio pwm 1 $[$1-1024] 
	gpio write 0 0
elif [ "$1" -ge "0" ] && [ "$1" -le "1023" ]; then
	gpio pwm 1 $1
	gpio write 0 1
elif [ "$1" -lt "0" ]; then
	gpio pwm 1 0
	gpio write 0 1
elif [ "$1" -gt "2047" ]; then
    gpio pwm 1 1023
	gpio write 0 0
fi

#Set Servo PWM Range:150-250
if [ "$2" -le "250" ] && [ "$2" -ge "50" ]; then
	echo 3=$2 > /dev/servoblaster
#   echo "ok2"
elif [ "$2" -gt "250" ]; then
	echo 3=250 > /dev/servoblaster
elif [ "$2" -lt "50" ]; then
	echo 3=50 > /dev/servoblaster
fi

#IFS=$OFS
echo motor:$1 servo:$2
