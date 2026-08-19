#include "MiniRobot.h"

int speed = 70;
int curveSpeed = 40;
float pi = 3.14159;

float P = 0;
float I = 0;
float D = 0;
float error = 0;
float lastError = 0;
float L_Motor = 0;
float R_Motor = 0;

PID str = { 5, 0.01, 4 };
PID curve = { 10, 0.01, 6 };
ServoArms arms(0, 180, 90, 180);

ServoArms::ServoArms(int openPos, int closePos, int upPos, int downPos) {
  openAngle = openPos;
  closeAngle = closePos;
  upAngle = upPos;
  downAngle = downPos;
}

void ServoArms::open() {
  MiniR4.RC3.setAngle(openAngle);
  delay(150);
}

void ServoArms::close() {
  MiniR4.RC3.setAngle(closeAngle);
  delay(150);
}

void ServoArms::up() {
  MiniR4.RC4.setAngle(upAngle);
  delay(200);
}

void ServoArms::down() {
  MiniR4.RC4.setAngle(downAngle);
  delay(200);
}

void FSL(float dist) {
  lineFollow(str.kp, str.ki, str.kd, dist);
}

void FCL(float dist) {
  int oldspeed = speed;
  speed = curveSpeed;
  lineFollow(curve.kp, curve.ki, curve.kd, dist);
  speed = oldspeed;
}

void lineFollow(float Kp, float Ki, float Kd, float dist) {
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();
  I = 0;
  lastError = 0;
  
  while (odom() < dist) {
    if (MiniR4.BTN_DOWN.getState()) return;
    error = MiniR4.I2C0.MXLineTracer.getError();
    Serial.print("Error: ");
    Serial.print(error);
    P = error;
    I += error;
    I = constrain(I, -100, 100);
    D = error - lastError;

    float correction = (P * Kp) + (I * Ki) + (D * Kd);
    Serial.print(" | Correction: ");
    Serial.print(correction);
    Serial.println();
    lastError = error;

    L_Motor = speed + correction;
    R_Motor = speed - correction;

    L_Motor = constrain(L_Motor, -100, 100);
    R_Motor = constrain(R_Motor, -100, 100);

    MiniR4.M1.setPower(L_Motor);
    MiniR4.M2.setPower(R_Motor * (-1));
    OLED(odom());
    delay(10);
  }
  MiniR4.M1.setBrake(true);
  MiniR4.M2.setBrake(true);
}

void OLED(float d) {
  MiniR4.OLED.clearDisplay();
  MiniR4.OLED.setTextSize(1);
  MiniR4.OLED.setCursor(5, 5);
  MiniR4.OLED.print(d);
  MiniR4.OLED.display();
}

float cm2d(float cm) {
  return (cm * (360.0 / 20.1));
}

float d2cm(float degrees) {
  return (degrees * (20.1 / 360.0));
}

float odom() {
  return d2cm((MiniR4.M1.getDegrees() - MiniR4.M2.getDegrees()) / 2.0);
}

void initRobot() {
  MiniR4.PWR.setBattCell(2);
  Serial.begin(9600);
  MiniR4.OLED.clearDisplay();
  MiniR4.OLED.setTextSize(1);
  MiniR4.OLED.setCursor(5, 5);
  MiniR4.OLED.print("Press Up to Start");
  MiniR4.OLED.display();
  MiniR4.M1.setBrake(false);
  MiniR4.M2.setBrake(false);
  MiniR4.M1.resetCounter();
  MiniR4.M2.resetCounter();
  MiniR4.I2C0.MXLineTracer.begin();
}
