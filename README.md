RaspberryPi-car
===============
RaspberryPi-car is a remote car which is controlled by RaspberryPi and Arduino. The goal of this project is to make a easily controlled access to the user. This is also my "National Students' Innovation and Entrepreneurship Training Program" project. The details do as follows. 

1.Arduino Project
-----------------
Arduino Project make the car controlled by the incomming commond. The incomming commond include 3 byte. The first byte is the direction of travel indicated by 0 or 1. The second byte is the power of motor between 0,255. The third byte is the servo steering teach between 0,180.
Connect RaspberryPi with Arduino Uno via Usb serial port.
Programming the code in ./Aruidno/carctrl/carctrl.ino to Arduino.

2.RaspberryPi Project
---------------------

1)Connect with Arduino
Set up a server waiting commond at '/dev/ArduinoServer' and sending the commond to Arduino. 
The format is 'M=S'. 
'M' indicated the power of moter between -255,255.
'S' indicated the servo steering teach between 0,180.
Both 'M' and 'S' are strings. They are split by '='.
The shell commond to make it is as follows:
```
sudo apt-get install python-serial
sudo cp ./RaspberryPi/pyctrl/arduinoserver.py /usr/local/bin
sudo cp ./RaspberryPi/init.d/ArduinoServer /etc/init.d/
cd /etc/init.d
sudo update-rc.d ArduinoServer start 
```
Interface Usage:
You can try `echo 255=90 > /dev/ArduinoServer` to let the car forward at full speed. 
Also try `echo 150=50 > /dev/ArduinoServer` to let the car turn right.

2)Controlled by TCP
Set up a server waiting for TCP connecting at port 2013. The data expected is the commond sending by the controller via TCP connection.  
The format of TCP commond is defined : "M S" 
'M' indicated the power of moter between -255,255.
'S' indicated the servo steering teach between 0,180.
Both 'M' and 'S' are strings. They are split by ' '.
The shell commond to make it is as follows:
`sudo cp ./RaspberryPi/pyctrl/carserver.py /usr/local/bin`
`sudo vim /etc/rc.local`
add this line before `exit 0` to start `carserver.py` script on boot:
`python /usr/local/bin/pyctrl/carserver.py`

3)Install mjpg_streamer
The project homepage is "http://sourceforge.net/projects/mjpg-streamer/"
For more information go here: http://wolfpaulus.com/journal/embedded/raspberrypi_webcam
The install commond :
```
sudo apt-get install libjpeg8-dev imagemagick subversion
cd /home/pi
svn co https://mjpg-streamer.svn.sourceforge.net/svnroot/mjpg-streamer mjpg-streamer
cd mjpg-streamer/mjpg-streamer
make
sudo make install
sudo cp ./RaspberryPi/init.d/webcam /etc/init.d/ 
cd /etc/init.d
sudo update-rc.d webcam start 
```

4)Install lighttpd to controlling the car on browser
We run the car's homepage on lighttpd which is a light http server.
The code of homepage is written in HTML5. 
The control device must support *gravity sensing* .  The car is controlled by the sensing.
The vedio in step 3) will appear on the homepage. 
```
sudo apt-get install lighttpd
sudo lighttpd-enable-mod fastcgi
sudo cp ./RaspberryPi/10-fastcgi.conf /etc/httpd/conf-enabled/
sudo cp ./RaspberryPi/www/* /var/www
sudo service lighttpd restart
```
