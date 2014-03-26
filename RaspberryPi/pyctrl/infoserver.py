#/usr/bin/env python
#encoding=utf-8

import socket
import os
import time
import threading
import ConfigParser
import serial

cf = ConfigParser.ConfigParser()
cf.read('config.ini')

host = ''
port = int(cf.get('port','info_port'))
serldev = cf.get('serial','serial_port') 

serl = serial.Serial(serldev,115200)

event = threading.Event()
event.clear()
sensor_info = ''

def update_info():
	global sensor_info, event, serl
	while True:
		sensor_info = serl.readline()
		event.set()

threading.Thread(target=update_info).start()

while True:
	#First Connection to get the host address
	print 'Waiting client'
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host, port)) 
	s.listen(5) 
	
	c, ad = s.accept() 
	print '1 host connected'

	#Try to send data to the host with addr	
	wait_time = 10 
	while True:
		event.wait()
		event.clear()
		try:
			c.sendall(sensor_info)
		except socket.error as msg:
			wait_time = wait_time - 1
			if wait_time > 0:
				continue
			else:
				print 'try to send failed!'
				break
	c.close()
	s.close()
	s = None 
			






