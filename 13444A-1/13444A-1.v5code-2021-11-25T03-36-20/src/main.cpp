// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "cmath"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

controller Controller1 = controller();
motor leftDrive = motor(PORT1, true);
motor leftDrive2 = motor(PORT11, false);
motor rightDrive = motor(PORT10, false); 
motor rightDrive2 = motor(PORT20, true);
motor liftMotorLeft = motor(PORT2, true);
motor liftMotorRight = motor(PORT9, false);
motor grabMotor = motor(PORT19, true);
motor_group liftMotors = motor_group(liftMotorLeft, liftMotorRight);
motor_group leftMotors = motor_group(leftDrive, leftDrive2);
motor_group rightMotors = motor_group(rightDrive, rightDrive2);
inertial Sensor = inertial(PORT8);

int a = 100;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void lowPower() {
  a = 50;
}

void highPower() {
  a = 100;
}

void grab() {
  // grabMotor.spinFor(1, timeUnits::sec, -50, velocityUnits::pct);
  //grabMotor.rotateTo(-55, degrees);
  //wait(250, msec);
  while(grabMotor.torque() < 1) {
    grabMotor.spin(directionType::rev);
  }
  grabMotor.stop();
}

void resetGrab() {
  grabMotor.rotateTo(0, degrees);
  wait(200, msec);
}

void driveInches(double inches, int percent) {
  leftMotors.setVelocity(percent, velocityUnits::pct);
  rightMotors.setVelocity(percent, velocityUnits::pct);
  leftMotors.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, false);
  rightMotors.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg);
}

void turnDegrees(double degrees) {
  /*
  leftMotors.spinFor(directionType::fwd, (9 * degrees) / 720 - 0.125, rotationUnits::rev, false);
  rightMotors.spinFor(directionType::rev, (9 * degrees) / 720 - 0.125, rotationUnits::rev);
  */;
  if (degrees > 0) {
    while (Sensor.angle() <= degrees - 3.5) {
      leftMotors.spin(directionType::fwd);
      rightMotors.spin(directionType::rev);
    }
  } else if (degrees < 0) {
    leftMotors.spinFor(5, rotationUnits::deg, false);
    rightMotors.spinFor(5, rotationUnits::deg);
    while (Sensor.angle() >= degrees + 363.5) {
      leftMotors.spin(directionType::rev);
      rightMotors.spin(directionType::fwd);
    }
  }
}

int autonType = 0;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Sensor.calibrate();
  grabMotor.setPosition(0, rotationUnits::deg);
  grabMotor.setRotation(0, rotationUnits::deg);
  grabMotor.setTimeout(300, timeUnits::msec);
  grabMotor.setStopping(brakeType::hold);
  Controller1.ButtonDown.pressed(lowPower);
  Controller1.ButtonRight.pressed(highPower);
  Controller1.ButtonY.pressed(resetGrab);
  Controller1.ButtonY.released(grab);
  Brain.Screen.drawRectangle(0, 0, 240, 90, blue);
  Brain.Screen.drawRectangle(240, 0, 240, 90, red);
  Brain.Screen.drawRectangle(0, 180, 480, 60, green);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  while (autonType == 0) {
    int touchX = Brain.Screen.xPosition();
    int touchY = Brain.Screen.yPosition();
    if (touchX < 240 && touchX > 0 && touchY <= 90) {
      autonType = 1;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Left Auton");
    } else if (touchX > 240 && touchY <= 90) {
      autonType = 2;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Right Auton");
    } else if (touchY >= 180) {
      autonType = 3;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Skills Auton");
    } else if (touchX < 240 && touchX > 0) {
      autonType = 4;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Playoffs Left");
    } else if (touchX > 240) {
      autonType = 5;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Playoffs Right");
    }
    wait(50, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  if (autonType == 1) {
    /*
    driveInches(18, 75);
    liftMotors.spinFor(-40 * 5, rotationUnits::deg);     
    driveInches(-10, 100);
    liftMotors.spinFor(-20 * 5, rotationUnits::deg);
    turnDegrees(-72);
    driveInches(48, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    driveInches(-40, 100);
    liftMotors.spinFor(-25 * 5, rotationUnits::deg);
    */
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    driveInches(-40, 75);
    resetGrab();
    leftMotors.spinFor(directionType::rev, 1.25, rotationUnits::rev);
    grab();
  }
  if (autonType == 2) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    driveInches(-24, 75);
    resetGrab();
    leftMotors.spinFor(directionType::rev, 2.125, rotationUnits::rev);
    driveInches(-2, 50);
    grab();
    //grabMotor.spinFor(-55, rotationUnits::deg);
    //wait(500, msec);
    driveInches(16, 100);
  }
  if (autonType == 3) {
    driveInches(-16, 25);
    grab();
    leftMotors.setVelocity(75, velocityUnits::pct);
    leftMotors.spinFor(directionType::fwd, 3.975, rotationUnits::rev);
    liftMotors.spinFor(-60 * 5, rotationUnits::deg);
    driveInches(40, 100);
    turnDegrees(55);
    driveInches(50, 100);
    resetGrab();
    driveInches(-5, 100);
    driveInches(10, 100);
    driveInches(-4, 100);
    resetGrab();
    turnDegrees(110);
    driveInches(-6, 25);
    grab();
    driveInches(6, 100);
    /*
    turnDegrees(-45);
    driveInches(-6, 100);
    driveInches(6, 100);
    turnDegrees(45);
    driveInches(4, 100);
    turnDegrees(90);
    driveInches(50, 100);
    turnDegrees(-90);
    driveInches(50, 100);
    liftMotors.spinFor(-25 * 5, rotationUnits::deg);
    turnDegrees(90);
    driveInches(12, 100);
    turnDegrees(-90);
    driveInches(12, 100);
    turnDegrees(-90);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    driveInches(36, 50);
    */
  }
  if (autonType == 4) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    wait(2, seconds);
    driveInches(5, 50);
    turnDegrees(90);
    driveInches(6, 50);
    turnDegrees(180);
    driveInches(-4, 25);
    grab();
    turnDegrees(45);
    driveInches(50, 100);
  }
  if (autonType == 5) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    wait(2, seconds);
    driveInches(5, 50);
    turnDegrees(-90);
    driveInches(6, 50);
    turnDegrees(180);
    driveInches(-4, 25);
    grab();
    turnDegrees(45);
    driveInches(50, 100);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    liftMotors.setStopping(brakeType::hold);
    grabMotor.setStopping(brakeType::hold);
    grabMotor.setTimeout(300, timeUnits::msec);
    leftMotors.spin(directionType::fwd, Controller1.Axis3.value() * a / 100, velocityUnits::pct);
    rightMotors.spin(directionType::fwd, Controller1.Axis2.value() * a / 100, velocityUnits::pct);
    if (Controller1.ButtonL1.pressing()) {
      liftMotors.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      liftMotors.spin(directionType::rev, 50, velocityUnits::pct);
    } else {
      liftMotors.stop();
    }
    /* testing inertial sensor
    if (Controller1.ButtonLeft.pressing() && Sensor.angle() <= 86.5) {
      leftMotors.spin(directionType::fwd);
      rightMotors.spin(directionType::rev);
    }
    */
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
