#/usr/bin/env python
#encoding=utf-8

import socket
import os


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = ''
port = 2013
s.bind((host, port)) 
s.listen(10) 
motor = 0
servo = 150
while True:
	c, addr = s.accept() 
	cmd = c.recv(1024).split(' ')
	motor = int(cmd[0])
	servo = int(cmd[1])
	dev = open("/dev/ArduinoServer","w")
	if motor > 255:
		motor = 255
	if motor < -255:
		motor = -255
	if servo > 180:
		servo = 180
	if servo <0:
		servo = 0

	dev.write(str(motor)+"="+str(servo)+"\n")

	dev.flush()
	dev.close()
	c.close()

