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
	
	c, ad = s.accept() #addr is acknowlaged
	pt = c.recv(1024)
	addr = (ad[0],int(pt))
	print addr
	c.close()
	s.close()
	s = None
	print '1 host connected'

	#Try to send data to the host with addr
#	ts = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		
	wait_time = 10 
#	print addr
	while True:
		event.wait()
		event.clear()
		ts = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		try:
			ts.connect(addr)
		except socket.error as msg:
			ts.close()
			wait_time = wait_time - 1
			if wait_time > 0:
				continue
			else:
				print 'try to send failed!'
				break
		ts.sendall(sensor_info)
		ts.close()
		ts = None

			
	ts = None






