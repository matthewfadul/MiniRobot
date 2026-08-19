#ifndef MINI_ROBOT_H
#define MINI_ROBOT_H

#define ENABLE_DRIVEDC_BRAKE_DELAY
#include <Arduino.h>
#include "MatrixMiniR4.h"

struct PID {
  double kp;
  double ki;
  double kd;
};

class ServoArms {
private:
  int openAngle;
  int closeAngle;
  int upAngle;
  int downAngle;
public:
  ServoArms(int openPos, int closePos, int upPos, int downPos);
  void open();
  void close();
  void up();
  void down();
};

extern int speed;
extern int curveSpeed;
extern PID str;
extern PID curve;
extern ServoArms arms;

void lineFollow(float Kp, float Ki, float Kd, float dist);
void FSL(float dist);
void FCL(float dist);
void OLED(float d);
void initRobot();
float cm2d(float cm);
float d2cm(float degrees);
float odom();

#endif
