========================================================================
                      MINI ROBOT LIBRARY V1.0
========================================================================
Welcome to the MiniRobot Library! This library hides the messy background
math so you can focus on building awesome autonomous robot behaviors.

Written by Matthew Fadul. August 19, 2026

------------------------------------------------------------------------
1. HOW TO INSTALL THE LIBRARY
------------------------------------------------------------------------
Method A (Automated Zip):
  1. Zip your main "MiniRobot" folder.
  2. Open the Arduino IDE.
  3. Click: Sketch -> Include Library -> Add .ZIP Library...
  4. Select your zip file.

Method B (Manual Drag & Drop):
  1. Copy the "MiniRobot" folder.
  2. Paste it directly into your computer's Arduino directory:
     Documents/Arduino/libraries/

  *Note: Restart your Arduino IDE completely after installing!

------------------------------------------------------------------------
2. GETTING STARTED (YOUR CODE SKETCH TEMPLATE)
------------------------------------------------------------------------
Every program you write should start with this clean setup:

#include <MiniRobot.h>

void setup() {
  MiniR4.begin();
  initRobot(); // Automatically configures the screen, motors, and sensors!
}

void loop() {
  // Put your logic commands here!
  if (MiniR4.BTN_UP.getState()) {
    FSL(50); // Example: Drive straight for 50 cm
  }
}

------------------------------------------------------------------------
3. MOVEMENT COMMANDS (THE MAIN MACROS)
------------------------------------------------------------------------
Use these simple commands inside your loop() function to navigate:

* FSL(distance_in_cm);
  -> Means: "Follow Straight Line".
  -> Example: FSL(100); drives forward 100 cm following the line at 
     speed 70.

* FCL(distance_in_cm);
  -> Means: "Follow Curve Line".
  -> Example: FCL(45); automatically slows the robot down to 
     curveSpeed 40 to safely trace a tight bend for 45 cm.

------------------------------------------------------------------------
4. MECHANISM COMMANDS (THE SERVO ARMS)
------------------------------------------------------------------------
Control your robot's arms using simple English commands. The dot (.) 
tells the computer to look inside the "arms" object:

* arms.open();  -> Opens the gripper claw (RC3 channel).
* arms.close(); -> Closes the gripper claw to grab items (RC3 channel).
* arms.up();    -> Lifts the arm assembly upward (RC4 channel).
* arms.down();  -> Lowers the arm assembly down to the floor (RC4 channel).
------------------------------------------------------------------------
4.5 ADVANCED MATH HELPERS (CONVERTING CENTIMETERS & DEGREES)
------------------------------------------------------------------------
Behind the scenes, your robot's motor encoders only count in "degrees of 
wheel rotation." To make programming easy, the library automatically 
converts these numbers into centimeters using your robot's wheel size! 

If you are writing custom loops, you can use these two math helpers:

* cm2d(distance_in_cm);
  -> Converts Centimeters into Motor Degrees.
  -> Use this when you want to know how many degrees your wheels must 
     spin to travel a specific physical distance.
  -> Example: float target_degrees = cm2d(20.1); 
     (Since the wheel circumference is 20.1 cm, this returns 360.0 degrees)

* d2cm(motor_degrees);
  -> Converts Motor Degrees into Centimeters.
  -> Use this when you read raw data from your motor encoders and want 
     to print or display it as a real-world distance.
  -> Example: float physical_distance = d2cm(180.0);
     (This converts 180 degrees of wheel rotation and returns roughly 10.05 cm)

* odom();
  -> Returns the total distance the robot has traveled in centimeters 
     since the current movement block started.
  -> Example: OLED(odom()); 
     (Displays your exact traveled distance live on the robot screen!)
------------------------------------------------------------------------
5. ADVANCED SPEED & PID TUNING (FOR EXPERTS)
------------------------------------------------------------------------
If your robot is moving too slow or driving off the line, you can change 
the core speeds and PID configurations inside your setup() function!

Add these configurations right after calling initRobot():

  speed = 80;        // Changes base straight line speed (Default: 70)
  curveSpeed = 50;   // Changes base curve tracing speed (Default: 40)

  str.kp = 6.0;      // Makes straight-line steering more aggressive
  curve.kd = 10.0;   // Increases braking to stop curves from fishtailing

========================================================================
                    HAPPY CODING, ROBOT ENGINEERS!
========================================================================
