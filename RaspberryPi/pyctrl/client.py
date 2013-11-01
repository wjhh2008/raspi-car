#!/usr/bin/python

import sys
from socket import *
serverHost = "192.168.1.115"        # servername is localhost
serverPort = 2013                   # use arbitrary port > 1024
while True:
	cmd=raw_input("cmd?\n")
	s = socket(AF_INET, SOCK_STREAM)    # create a TCP socket
	s.connect((serverHost, serverPort)) # connect to server on the port
	s.send(cmd)               # send the data
	s.close()	
