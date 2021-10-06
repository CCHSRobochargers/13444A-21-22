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

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

controller Controller1 = controller();
motor leftDrive = motor(PORT1, false);
motor rightDrive = motor(PORT10, true);
motor liftMotorLeft = motor(PORT11, true);
motor liftMotorRight = motor(PORT19, false);
motor_group liftMotors = motor_group(liftMotorLeft, liftMotorRight);

int a = 50;

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
  a = 25;
}

void highPower() {
  a = 50;
}

void driveInches(double inches) {
  leftDrive.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg);
  rightDrive.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg);
}

void turnDegrees(double degrees) {
  leftDrive.spinFor(directionType::fwd, 360 * (3.14 * 18 / degrees), rotationUnits::deg);
  rightDrive.spinFor(directionType::rev, 360 * (3.14 * 18 / degrees), rotationUnits::deg);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.ButtonA.pressed(lowPower);
  Controller1.ButtonB.pressed(highPower);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  liftMotors.spinFor(3, timeUnits::sec);
  turnDegrees(-15);
  driveInches(13);
  liftMotors.spinFor(1, timeUnits::sec);
  driveInches(-13);
  turnDegrees(15);
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
    leftDrive.spin(directionType::fwd, Controller1.Axis3.value() * a / 100, velocityUnits::pct);
    rightDrive.spin(directionType::fwd, Controller1.Axis2.value() * a / 100, velocityUnits::pct);
    if (Controller1.ButtonL1.pressing()) {
      liftMotors.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      liftMotors.spin(directionType::rev, 50, velocityUnits::pct);
    } else {
      liftMotors.stop();
    }
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
