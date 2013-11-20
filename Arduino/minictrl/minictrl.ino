#include <Servo.h>
#include <NewPing.h>
#define DELAYTIME 10000; 
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int motor,servo,cmd;
int waittime = 2;
int dtime = 0;
Servo myservo;

int morPin = 5;
int morGnd = 4;

void setup(){
  
  //init Serial
  Serial1.begin(115200);
  
  //init servo
  myservo.attach(9);
  myservo.write(90);
  
  //init motor
  pinMode(morPin,OUTPUT);
  pinMode(morGnd,OUTPUT);
  analogWrite(morPin,0);
  digitalWrite(morGnd,0);
  //init 
  //pinMode(11,OUTPUT);
}

void loop(){
  dtime++;
  if (dtime==DELAYTIME){
    dtime = 0;
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial1.print("Ping: ");
    Serial1.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial1.println("cm");
  }
  if (Serial1.available() > 0){
    
    //rev cmd
    cmd = Serial1.read();
    delay(waittime);
    //analogWrite(morPin,cmd);
    
    if (cmd == 0 || cmd == 1){  //0 Forward 1 Backward 
      motor = Serial1.read();
      delay(waittime);
      servo = Serial1.read();
      delay(waittime);
      
      //set servo
      servo = 180-servo;
      myservo.write(servo);
      
      //set motor
      if (cmd == 1) motor = 255-motor;
      analogWrite(morPin,motor);
      //analogWrite(11,motor);
      digitalWrite(morGnd,cmd);
    }
    
  }
  
}
