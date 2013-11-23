#include <Servo.h>
#include <NewPing.h>
#define DELAYTIME 10000 
#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define morPin 11
#define morGnd 12
#define servoPin 9
#define LED_Low 7
#define LED_Mid 8
#define LED_High 13
#define waittime 2
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int shut_Low = 120, shut_High = 30;

int motor,servo,cmd;
int mod = 0; 
Servo myservo;
int dtime;

void setup(){
  
  //init Serial
  Serial.begin(115200);
  
  //init servo
  myservo.attach(servoPin);
  myservo.write(90);
  
  //init motor
  
  pinMode(morPin,OUTPUT);
  pinMode(morGnd,OUTPUT);
  setPwmFrequency(morPin,1);
  analogWrite(morPin,0);
  digitalWrite(morGnd,0);
  
  pinMode(LED_Low,OUTPUT);
  pinMode(LED_Mid,OUTPUT);
  pinMode(LED_High,OUTPUT);
  digitalWrite(LED_Low,1);
  digitalWrite(LED_Mid,1);
  digitalWrite(LED_High,1);
  
  dtime = 0;
}

void loop(){

  dtime++;
  if (dtime>=DELAYTIME){
    dtime = 0;
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping: ");
    //Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    //Serial.println("cm");
    unsigned int dis = uS / US_ROUNDTRIP_CM;
    if (dis > shut_Low){
      digitalWrite(LED_Low,0);
      digitalWrite(LED_Mid,1);
      digitalWrite(LED_High,1);
    }else if (dis > shut_High){
      digitalWrite(LED_Low,1);
      digitalWrite(LED_Mid,0);
      digitalWrite(LED_High,1);
    }else {
      digitalWrite(LED_Low,1);
      digitalWrite(LED_Mid,1);
      digitalWrite(LED_High,0);
    }
  }

  if (Serial.available() > 0){
    
    //rev cmd
    cmd = Serial.read();
    delay(waittime);
    //analogWrite(morPin,cmd);
    
    if (cmd == 0 || cmd == 1){  
      //0 Forward 1 Backward 
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
    }else if (cmd == 2){ 
      //set shutdown
      shut_Low = Serial.read();
      delay(waittime);
      shut_High = Serial.read();
      delay(waittime);
    }else if (cmd == 4){
      //shutdown!
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
