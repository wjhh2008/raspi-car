#!/usr/bin/python

import sys
from socket import *
serverHost = ''       # servername is localhost
serverPort = 0# use arbitrary port > 1024

u = raw_input("Sendto:IP port?\n")
serverHost,serverPort= u.split(' ') 
while True:
	strings = raw_input("sendwhat?\n")
	s = socket(AF_INET, SOCK_STREAM)    # create a TCP socket
	s.connect((serverHost, int(serverPort))) # connect to server on the port
	s.send(strings)               # send the data
	s.close()
	s = None
