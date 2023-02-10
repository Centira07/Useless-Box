#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "Servo.h"
#include "Button.h"

Servo servoArm; //servo that will turn off the switch
Servo servoLift; //servo that will lift the lid of the box

int swhPin = 5;
int armPin = 7;
int liftPin = 8;

int pos_arm_start = 0; // resting position of arm servo
int pos_lift_start = 80; // resting position of lift servo
int pos_arm; // current position of arm servo
int pos_lift; // current position of lift servo
int pos_arm_switch; // position of arm servo to turn off switch
int pos_lift_open; // position of lift servo to open box

unsigned long timerStart = 0;
unsigned long currentTime = 0;
int counter = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(swhPin, INPUT);
  lcd.init();
  lcd.backlight();
  servoArm.attach(armPin); //setting pin for the arm servo
  servoLift.attach(liftPin); //setting pin for the lift servo
  servoArm.write(pos_arm);
  servoLift.write(pos_lift);
}

void loop() {
  if (digitalRead(swhPin) == HIGH) {
    timerStart = millis();
    Serial.Println("Switch is on");
    lcdEmotion();
    open();  
  } else {
    currentTime = millis();
  }
}

void open() {
  hitSwitch();
}

void close() {
}

void hitSwitch() {
  close();
}

void lcdEmotion() {
}

