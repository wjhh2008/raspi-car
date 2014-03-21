#!/usr/bin/env python
import os
import serial
import struct
#DEVFILE = '/dev/ArduinoServer'
port = "/dev/ttyACM0"
serl = serial.Serial(port,115200)
while True:
	line = ''
	while True:
		s = raw_input("Send sth :")
		cmd = s.split(' ')
		serl.write(struct.pack('BBB',int(cmd[0]),int(cmd[1]),int(cmd[2])))

