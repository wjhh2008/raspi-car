#!/usr/bin/env python
import os
import serial
import struct
DEVFILE = '/dev/ArduinoServer'
port = "/dev/ttyAMA0"
serl = serial.Serial(port,115200)
try:
	if os.path.exists(DEVFILE):
		os.unlink(DEVFILE)
	os.mkfifo(DEVFILE)
	os.chmod(DEVFILE,0666)
	fd = os.open(DEVFILE,os.O_RDWR)
except:
	print 'Creat Pipe Error!'
else:
	while True:
		line = ''
		while True:
			s = os.read(fd,1)
			if s == '\n':
				c = line.split('=')		
				#c[0] must in [0,255] for motor   c[1] must in [0,180] for servo
				#ATTENTION NO ERROR DETECT!
				cmd = int(int(c[0])<0)
				motor = abs(int(c[0]))  
				servo = int(c[1])
				if servo==255:
					os.system('poweroff')
					break
				serl.write(struct.pack('BBB',cmd,motor,servo))
				break
			line += s
			if len(line) > 126:
				print "Input too long"
				break
	
