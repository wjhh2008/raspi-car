#!/bin/bash

echo "Content-type: text/html"
echo ""

echo '<html>'
echo '<head>'
echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">'
echo '<title>Environment Variables</title>'
echo '</head>'
echo '<body>'

# Save the old internal field separator.
OIFS="$IFS"

# Set the field separator to & and parse the QUERY_STRING at the ampersand.
IFS="${IFS}&"
set $QUERY_STRING
Args="$*"
IFS="$OIFS"

# Next parse the individual "name=value" tokens.

ARGX=""
ARGY=""
ARGZ=""

for i in $Args ;do

#       Set the field separator to =
IFS="${OIFS}="
set $i
IFS="${OIFS}"

case $1 in
# Don't allow "/" changed to " ". Prevent hacker problems.
motor) ARGX="`echo $2 | sed 's|[\]||g' | sed 's|%20| |g'`"
;;
# Filter for "/" not applied here
servo) ARGY="`echo $2 | sed 's|%20| |g'`"
;;
xixi) ARGZ="${2/\// /}"
;;
*)     echo "<hr>Warning:"\
		"<br>Unrecognized variable \'$1\' passed by FORM in QUERY_STRING.<hr>"
		;;

		esac
		done

		echo 'Parsed Values:' 
		echo '<br>'
		echo $ARGX
		echo 1=$ARGX > /dev/servoblaster
		echo '<br>'
		echo $ARGY
		echo 2=$ARGY > /dev/servoblaster
		echo '<br>'
		echo $ARGZ

		echo '</body>'
		echo '</html>'

		exit 0

