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
  pinMode(11,OUTPUT);
  setPwmFrequency(11,1);
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
      analogWrite(11,motor);
      digitalWrite(morGnd,cmd);
    }
    
  }
}
/**
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4
 */
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
