#!/usr/bin/env python
import os
import serial
import struct
#DEVFILE = '/dev/ArduinoServer'
port = "/dev/ttyACM0"
serl = serial.Serial(port,115200)
while True:
	print serl.readline()

