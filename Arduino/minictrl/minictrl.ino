#include <Servo.h>
#include <NewPing.h>
#define DELAYTIME 10000 
#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define morPin 11
#define morGnd 12
#define servoPin 9
/*
#define LED_Low 7
#define LED_Mid 8  
#define LED_High 13
*/
#define waittime 2
#define ALARM_PIN 8

#define mod_tout 2
#define mod_sonar 4
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int shut_Low = 120, shut_High = 30, sonar_status = 0;
unsigned long timeout = 0, now = 0,dtime;
int motor,servo,cmd,p1,p2;
int mod = 0; 
Servo myservo;


void setup(){
  
  //init Serial
  Serial.begin(115200);
  
  //init servo
  myservo.attach(servoPin);
  myservo.write(90);
  
  //init motor
  
 // setPwmFrequency(morPin,128);
  
  pinMode(morPin,OUTPUT);
  pinMode(morGnd,OUTPUT);
  analogWrite(morPin,0);
  digitalWrite(morGnd,0);
  /*
  pinMode(LED_Low,OUTPUT);
  pinMode(LED_Mid,OUTPUT);
  pinMode(LED_High,OUTPUT);
  digitalWrite(LED_Low,1);
  digitalWrite(LED_Mid,1);
  digitalWrite(LED_High,1);
  */
  pinMode(ALARM_PIN,INPUT);
  digitalWrite(ALARM_PIN,HIGH);
  if (digitalRead(ALARM_PIN)==0) mod |= mod_sonar;
  dtime = millis();
}

void loop(){
  now = millis();
  if (now - dtime >=50){
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    unsigned int dis = uS / US_ROUNDTRIP_CM;
    if (dis > shut_Low)
      sonar_status = 1;  //Green
    else if (dis > shut_High)
      sonar_status = 2;  //Yellow
    else 
      sonar_status = 3;  //Red
     dtime=millis();
  }

  if (Serial.available() > 0){
    
    
    //rev cmd
    cmd = Serial.read();
    delay(waittime);
    p1 = Serial.read();
    delay(waittime);
    p2 = Serial.read();
    delay(waittime);
   
    if (cmd == 0 || cmd == 1){  
        //0 Forward 1 Backward 
        servo = 180-p2;
        myservo.write(servo);
        if (cmd == 1) motor = 255-p1;
        else motor = p1;
        analogWrite(morPin,motor);
        digitalWrite(morGnd,cmd);
    }else if (cmd == 2){ 
        //set sonar
        shut_Low = Serial.read();
        delay(waittime);
        shut_High = Serial.read();
        delay(waittime);
    }else if (cmd == 3){
        //change mod!
        mod = p1;
    }
  
    
    timeout = millis();
  }
  // Cmd timeout
  now = millis();
  if (((mod & mod_tout) && now-timeout>1000)||
      ((mod & mod_sonar) &&  sonar_status>2)){
      alarm_stop();
  }
  
}
void alarm_stop(){
    analogWrite(morPin,0);
    digitalWrite(morGnd,0);
    myservo.write(90);
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
