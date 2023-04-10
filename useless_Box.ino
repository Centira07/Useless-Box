#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
#include "Servo.h"
#include "Button.h"

Servo servoArm; //servo that will turn off the switch
Servo servoLift; //servo that will lift the lid of the box

int swhPin = 5; //digital pin for toggle switch
int armPin = 7; //digital pin for the Servo motor that turns off the switch
int liftPin = 8; //digital pin for the Servo motor that lifts the lid

int pos_arm_start = 0; // resting position of arm servo
int pos_lift_start = 30; // resting position of lift servo
int pos_arm; // current position of arm servo
int pos_lift; // current position of lift servo
int pos_arm_switch = 135; // position of arm servo to turn off switch
int pos_lift_open = 60; // position of lift servo to open box

unsigned long timerStart = 0;
unsigned long currentTime = 0;
int counter = 2;
int timeCount = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

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
  if (digitalRead(swhPin) == HIGH) {
    Serial.Println("Switch is on");
    timeCount = currentTime - timerStart;
    if (timeCount <= 10000 && counter == 2) {
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
      counter = 2;
    } else if (timeCount >= 120000 && counter == 7) {
      counter = 2;
    }
    lcdEmotion(counter);
    timerStart = millis();
  } else {
    currentTime = millis();
    lcdEmotion(1);
  }
}

void open() {
   servoLift.write(pos_lift_open);
  hitSwitch();
}

void close() {
  servoLift.write(pos_lift_start);
}

void hitSwitch() {
  servoArm.write(pos_arm_switch);
  delay(200);
  servoArm.write(pos_arm);
  close();
}

void lcdEmotions(int count) {
  switch(count) {
    case 1: //resting case
      lcd.clear();
      lcd.setCursor(3,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(4,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(5,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(6,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(7,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(8,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(9,0)
      lcd.print("Z");
      delay(500);
      lcd.setCursor(10,0)
      lcd.print("Z");
      delay(100);
      break;
    case 2: //first switch
      lcd.clear();
      lcd.setCursor(3,0)
      lcd.print("Who did that");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(1,0)      
      lcd.print("Please don't");
      lcd.setCursor(1,1);
      lcd.print("do that again");
      break;
    case 3: //second switch
      lcd.clear();
      lcd.setCursor(1,0)
      lcd.print("Why would you");
      lcd.setCursor(1,0)
      lcd.print("do that again?");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(1,0)      
      lcd.print("I am pleading");
      lcd.setCursor(1,1);
      lcd.print("to not do that");
      break;
    case 4: // first warning
      lcd.clear();
      lcd.setCursor(1,0)
      lcd.print("I asked politely");
      lcd.setCursor(1,0)
      lcd.print("but you did it");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(1,0)      
      lcd.print("I am warning");
      lcd.setCursor(1,1);
      lcd.print("you this time");
      break;
    case 5: //second warning
      lcd.clear();
      lcd.setCursor(1,0)
      lcd.print("I swear I warned");
      lcd.setCursor(1,0)
      lcd.print("you once already");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(1,0)      
      lcd.print("This will be");
      lcd.setCursor(1,1);
      lcd.print("your 2nd warning");
      break;
    case 6: //final warning
      lcd.clear();
      lcd.setCursor(1,0)
      lcd.print("I already warned");
      lcd.setCursor(1,0)
      lcd.print("you 2 times!");
      delay(1000);
      open();
      lcd.clear();
      lcd.setCursor(1,0)      
      lcd.print("This is your");
      lcd.setCursor(1,1);
      lcd.print("final warning!!");
      break;
    case 7: //final straw
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Gone on a");
      lcd.setCursor(5,1);
      lcd.print("Vacation");      
      break;
    default: 
      break;
  }

}
