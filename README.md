RaspberryPi-car Project
======
Overview
-----
RaspberryPi-car Project is based on   
XX parts  
National Innovation Project  

Part1 on Arduino
-----

### Device
- #### My car  
    Motor : 380  
    Servo : S0270
    Class : SUV  
- #### Arduino mini  
    [Arduino mini pro 5v 16MHZ](http://arduino.cc/en/Main/ArduinoBoardMini)  
    ![arduinomini](/img/arduinomini)
- #### Logic Level Converter  
    3.3v TTL convert to 5.0v TTL.  
    Connect to RaspberryPi by serial.  
    ![Logic Level Converter](/img/logiclevelconverter.jpg)  
- #### BTN7971B Module 
    The motor driver chip with much better performence comparing with L298N.  
    ![BTN7971B](/img/BTN7971B.JPG)  
- #### LM2596ADJ Module  
    The votage regulator chip provide power steering.   
    ![LM2596ADJ](/img/LM2596ADJ.jpg)  
- #### HC-SR04 Sensor Module  
    The HC-SR04 ultrasonic sensor uses sonar to determine distance to an object like bats or dolphins do. It offers excellent non-contact range detection with high accuracy and stable readings in an easy-to-use package. From 2cm to 400 cm or 1” to 13 feet.   
    Used for avoiding obstacles.  
    ![HC-SR04](/img/HC-SR04.jpg)  
- #### Buttery1  
    Votage: 11.1v  
    Discharge current: 25C  
    Usage: power motor and servo  
- #### Buttery2  
    Votage: 5v  
    Discharge current: ?C  
    Usage: power RaspberryPi and Arduino  

### Driver Code
- #### Serial Server  
    Arduino Serial is repeatedly waiting for commond which composed by the three bits of instruction. These three bits represent direction(0 or 1), motor speed(0-255), steering angle(0-180).

- #### Motor Driver  
    Two motor control signal line attach to arduino PIN11 and PIN12. The PWM output pin is PIN11.  
    The setPwmFrequency() method change the default frequence at PIN11 to 31250 Hz decreasing the noise from motor.  
- #### Servo Driver  
    The Servo control signal line attach to PIN9. Use the arduino servo lib.  
- #### Sonar Sensor Driver  
    Used Pins : 2, 4
    Use the arduino lib NEWPING.  
    Get detail information from [here](http://playground.arduino.cc/Code/NewPing).  
- #### [__All Code for Arduino__](/Arduino/minictrl/minictrl.ino)  

Part2 on RaspberryPi 
-----

### About RaspberryPi
- [HomePage](http://www.raspberrypi.org/)
- Module B
- System Raspbian
- [QuickGuide](http://www.raspberrypi.org/quick-start-guide)

### Wireless Host Access Point

- [Setting up a Raspberry Pi as a WiFi access point](http://learn.adafruit.com/setting-up-a-raspberry-pi-as-a-wifi-access-point/overview) 

### Arduino Server

- #### Connect with Arduino
Create a pipe sending the commond to Arduino at '/dev/ArduinoServer'.   
The commond format is 'M=S'.  
'M' indicated the power of moter between -255,255.  
'S' indicated the servo steering teach between 0,180.  
Both 'M' and 'S' are string. They are split by '='.  
The shell commond to make it is as follows:
``` bash
sudo apt-get install python-serial
sudo cp ./RaspberryPi/pyctrl/arduinoserver.py /usr/local/bin
sudo cp ./RaspberryPi/init.d/ArduinoServer /etc/init.d/
sudo update-rc.d ArduinoServer start 
```

- #### Interface Usage:
You can try echo 255=90 > /dev/ArduinoServer to let the car forward at full speed.  
Also try echo 150=50 > /dev/ArduinoServer to let the car turn right.  

### Car TCP Server
- #### TCP Server
Controlled by TCP Set up a server waiting for TCP connecting at port 2013. The data expected is the commond sending by the controller via TCP connection.  
The format of TCP commond is defined : "M S"/.  
'M' indicated the power of moter between -255,255.  
'S' indicated the servo steering teach between 0,180.  
Both 'M' and 'S' are strings. They are split by ' '.  
The shell commond to make it is as follows:
``` bash
sudo cp ./RaspberryPi/pyctrl/carserver.py /usr/local/bin
sudo cp ./RaspberryPi/init.d/CarServer /etc/init.d/
sudo update-rc.d CarServer start 
```

### Vision
- The Mjpg-streamer project. The project homepage is "http://sourceforge.net/projects/mjpg-streamer/".  
- For more information click [here](http://wolfpaulus.com/journal/embedded/raspberrypi_webcam).  
- For Raspi Camera Module click [here](https://github.com/jacksonliam/mjpg-streamer).  
```bash
sudo apt-get install cmake
sudo cp ./RaspberryPi/init.d/webcam /etc/init.d/
sudo update-rc.d webcam start 
cd RaspberryPi/mjpg-streamer-code-181/mjpg-streamer-experimental-pi/
make && sudo make install

```

### HTTP Server
- Run the car's homepage on lighttpd which is a light http server.
- The code of homepage is written in HTML5. 
- The control device must support __gravity sensing__ .  The car is controlled by the sensing.

```bash
sudo apt-get install lighttpd python-flup
sudo lighttpd-enable-mod fastcgi
sudo cp ./RaspberryPi/10-fastcgi.conf /etc/lighttpd/conf-enabled/
sudo cp -r ./RaspberryPi/www/* /var/www
sudo /etc/init.d/lighttpd force-reload
```

### Quick Summary
- #### Used Software
    hostapd  
    isc-dhcp-server  
    lighttpd  
    mjpg-streamer  
    arduinoserver.py  
    carserver.py  
- #### Breif Diagram
    ![summary](/img/summary.jpeg)
    
    









