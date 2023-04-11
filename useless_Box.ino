#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include "Servo.h"

Servo servoArm; //servo that will turn off the switch
Servo servoLift; //servo that will lift the lid of the box

int swhPin = 3; //digital pin for toggle switch
int armPin = 4; //digital pin for the Servo motor that turns off the switch
int liftPin = 5; //digital pin for the Servo motor that lifts the lid

int pos_arm_start = 0; // resting position of arm servo
int pos_lift_start = 0; // resting position of lift servo
int pos_arm; // current position of arm servo
int pos_lift; // current position of lift servo
int pos_arm_switch = 180; // position of arm servo to turn off switch
int pos_lift_open = 180; // position of lift servo to open box

unsigned long timerStart = 0;
unsigned long currentTime = 0;
int counter = 1;
int timeCount = 0;
int switch_state = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void open() {
  servoLift.write(pos_lift_open);
  delay(2000);
  hitSwitch();
}

void close() {
  servoLift.write(pos_lift_start);
}

void hitSwitch() {
  servoArm.write(pos_arm_switch);
  delay(1000);
  servoArm.write(pos_arm);
  delay(1000);
  close();
}

void lcdEmotion(int count) {
  switch(count) {
    case 1: //resting case
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(4,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(5,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(6,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(7,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(8,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(9,0);
      lcd.print("Z");
      delay(500);
      lcd.setCursor(10,0);
      lcd.print("Z");
      delay(100);
      break;
    case 2: //first switch
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Who did that");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(0,0);   
      lcd.print("Please don't");
      lcd.setCursor(0,1);
      lcd.print("do that again");
      delay(4000);
      break;
    case 3: //second switch
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Why would you");
      lcd.setCursor(0,1);
      lcd.print("do that again?");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(0,0);     
      lcd.print("I am pleading");
      lcd.setCursor(0,1);
      lcd.print("to not do that");
      delay(4000);
      break;
    case 4: // first warning
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("I asked politely");
      lcd.setCursor(0,1);
      lcd.print("but you did it");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(0,0);    
      lcd.print("I am warning");
      lcd.setCursor(0,1);
      lcd.print("you this time");
      delay(4000);
      break;
    case 5: //second warning
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("I swear I warned");
      lcd.setCursor(0,1);
      lcd.print("you once already");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(0,0);      
      lcd.print("This will be");
      lcd.setCursor(0,1);
      lcd.print("your 2nd warning");
      delay(4000);
      break;
    case 6: //final warning
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("I already warned");
      lcd.setCursor(0,1);
      lcd.print("you 2 times!");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(0,0);     
      lcd.print("This is your");
      lcd.setCursor(0,1);
      lcd.print("final warning!!");
      delay(4000);
      break;
    case 7: //final straw
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Gone on a");
      lcd.setCursor(4,1);
      lcd.print("Vacation"); 
      delay(50);           
      break;
    default: 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Something is");
      lcd.setCursor(0,1);  
      lcd.print("wrong");
      delay(50);
      break;
  }

}

void setup() {
  Serial.begin(9600);
  pinMode(swhPin, INPUT); // Setting up the toggle switch
  lcd.init();
  lcd.backlight();
  servoArm.attach(armPin); //setting pin for the arm servo
  servoLift.attach(liftPin); //setting pin for the lift servo
  servoArm.write(pos_arm_start);
  servoLift.write(pos_lift_start);
}

void loop() {
  switch_state = digitalRead(swhPin);
  Serial.println(switch_state);
  if (switch_state == HIGH) {
    timeCount = currentTime - timerStart;
    if (counter == 1)  {
      counter = 2;    
    } else if (timeCount <= 10000 && counter == 2) {
      counter = 3;
    } else if (timeCount <= 10000 && counter == 3) {
      counter = 4;
    } else if (timeCount <= 10000 && counter == 4) {
      counter = 5;
    } else if (timeCount <= 10000 && counter == 5) {
      counter = 6;
    } else if (timeCount <= 10000 && counter == 6) {
      counter = 7;
    } else if (timeCount > 10000 && counter < 7) {
      counter = 1;
    } else if (timeCount >= 120000 && counter == 7) {
      counter = 1;
    } else {
      currentTime = millis();      
    }
    lcdEmotion(counter);
    timerStart = millis();
  } else {
    currentTime = millis();
    if (timeCount < 120000 && counter == 7) {
      lcdEmotion(7);
      timeCount = currentTime - timerStart;
    } else {
      lcdEmotion(1);   
    }
  }
}
