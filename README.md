RaspberryPi-car
===============
RaspberryPi-car is a remote car which is controlled by RaspberryPi. The goal of this project is to make a easily controlled access to the user.The details do as follows.

1.Arduino Project
-----------------
Arduino Project make the car controlled by the incomming commond. The incomming commond include 3 byte. The first byte is the direction of travel indicated by 0 or 1. The second byte is the power of motor between 0,255. The third byte is the servo steering teach between 0,180.
Connect RaspberryPi with Arduino Uno via Usb serial port.
Programming the code in ./Aruidno/carctrl/carctrl.ino to Arduino.

2.RaspberryPi Project
---------------------

1)Connect with Arduino
Set up a server waiting commond at '/dev/ArduinoServer' and sending the commond to Arduino. The format is 'M=S'. 'M' indicated the power of moter between -255,255. 'S' indicated the servo steering teach between 0,180. Both 'M' and 'S' are strings. They are split by '='.
The shell commond to make this operate is as follows:
`sudo apt-get install python-serial
sudo cp ./RaspberryPi/pyctrl/arduinoserver.py /usr/local/bin
sudo cp ./RaspberryPi/init.d/ArduinoServer /etc/init.d/
sudo update-rc.d ArduinoServer start `

2)Controlled by TCP

