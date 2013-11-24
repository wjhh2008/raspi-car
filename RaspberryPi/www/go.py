#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from cgi import escape
import sys, os, urlparse
from flup.server.fcgi import WSGIServer

def app(environ, start_response):
	start_response('200 OK', [('Content-Type', 'text/html')])

	i = urlparse.parse_qs(environ["QUERY_STRING"])
	yield ('&nbsp;')
#	yield 'fuck'
	dev = open("/dev/ArduinoServer","w")
	motor = 0
	servo = 90
#	yield i["motor"][0]+" "+i["servo"][0]
	if "motor" in i:
		motor = int(i["motor"][0])
	if "servo" in i:
		servo = int(i["servo"][0])
#	yield 'calcok!'
	dev.write(str(motor)+"="+str(servo)+"\n")

WSGIServer(app).run()
