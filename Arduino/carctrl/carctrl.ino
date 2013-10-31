#include <Servo.h>
int motor,servo,cmd;
int waittime = 2;
Servo myservo;

int morPin = 5;
int morGnd = 4;

void setup(){
  
  //init Serial
  Serial.begin(115200);
  
  //init servo
  myservo.attach(9);
  myservo.write(90);
  
  //init motor
  pinMode(morPin,OUTPUT);
  pinMode(morGnd,OUTPUT);
  analogWrite(morPin,0);
  digitalWrite(morGnd,0);
  //init 
}

void loop(){

  if (Serial.available() > 0){
    
    //rev cmd
    cmd = Serial.read();
    delay(waittime);
    //analogWrite(morPin,cmd);
    
    if (cmd == 0 || cmd == 1){  //0 Forward 1 Backward 
      motor = Serial.read();
      delay(waittime);
      servo = Serial.read();
      delay(waittime);
      
      //set servo
      servo = 180-servo;
      myservo.write(servo);
      
      //set motor
      if (cmd == 1) motor = 255-motor;
      analogWrite(morPin,motor);
      digitalWrite(morGnd,cmd);
    }
    
  }
}
