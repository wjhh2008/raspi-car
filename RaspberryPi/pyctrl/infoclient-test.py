#!/usr/bin/python

import sys
import socket


serverHost = '127.0.0.1'
serverPort = 2014
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    # create a TCP socket
s.connect((serverHost, serverPort)) # connect to server on the port
s.send("2015")               # send the data
#s.close()
#s = None

#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#host = ''
#port = 2015
#s.bind((host, port))
#s.listen(10)

while True:
	#c, addr = s.accept()
	#print c.recv(1024)
	#c.close()
	print s.recv(1024)
