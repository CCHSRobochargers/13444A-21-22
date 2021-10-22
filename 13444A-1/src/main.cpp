/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// liftMotors           motor_group   2, 9            
// MotorGroup1          motor_group   1, 11           
// MotorGroup10         motor_group   10, 20          
// Drivetrain           drivetrain    3, 4            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
void  vexcodeInit( void ) {}
// define your global instances of motors and other devices here
// VEXcode device constructors
brain Brain = brain();
controller Controller1 = controller(primary);
motor liftMotorsMotorA = motor(PORT2, ratio36_1, true);
motor liftMotorsMotorB = motor(PORT9, ratio36_1, false);
motor_group liftMotors = motor_group(liftMotorsMotorA, liftMotorsMotorB);
motor MotorGroup1MotorA = motor(PORT1, ratio18_1, false);
motor MotorGroup1MotorB = motor(PORT11, ratio18_1, true);
motor_group MotorGroup1 = motor_group(MotorGroup1MotorA, MotorGroup1MotorB);
motor MotorGroup10MotorA = motor(PORT10, ratio18_1, false);
motor MotorGroup10MotorB = motor(PORT20, ratio18_1, true);
motor_group MotorGroup10 = motor_group(MotorGroup10MotorA, MotorGroup10MotorB);
drivetrain Drivetrain = drivetrain(MotorGroup1, MotorGroup10, 319.19, 406.4, 266.7, mm, 1);

/*
controller Controller1 = controller();
motor leftDrive = motor(PORT1, false);
motor rightDrive = motor(PORT10, true);
motor leftDrive2 = motor(PORT11, true);
motor rightDrive2 = motor(PORT20, false);
motor liftMotorLeft = motor(PORT2, true);
motor liftMotorRight = motor(PORT9, false);
motor_group liftMotors = motor_group(liftMotorLeft, liftMotorRight);
*/
int a = 50;
bool ready = false;
int autonType = 0;

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

/*
void driveInches(double inches) {
  leftDrive.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, false);
  rightDrive.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, false);
  leftDrive2.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, false);
  rightDrive2.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, true);
}

void turnDegrees(double degrees) {
  leftDrive.spinFor(directionType::fwd, 360 * (3.14 * 18 / degrees), rotationUnits::deg, false);
  rightDrive.spinFor(directionType::rev, 360 * (3.14 * 18 / degrees), rotationUnits::deg, false);
  leftDrive2.spinFor(directionType::fwd, 360 * (3.14 * 18 / degrees), rotationUnits::deg, false);
  rightDrive2.spinFor(directionType::rev, 360 * (3.14 * 18 / degrees), rotationUnits::deg, true);
}
*/
void leftAuton() {
  Drivetrain.turnFor(-15 / 4, degrees);
  Drivetrain.driveFor(220, inches);
  liftMotors.rotateFor(-40 * 5, degrees);
  Drivetrain.driveFor(-22, inches);
  Drivetrain.turnFor(15, degrees);
  liftMotors.rotateFor(-30 * 5, rotationUnits::deg);
  Drivetrain.driveFor(22, inches);
  liftMotors.rotateFor(70 * 5, rotationUnits::deg);
  Drivetrain.driveFor(8, inches);
  liftMotors.rotateFor(-30 * 5, rotationUnits::deg);
  Drivetrain.driveFor(2, inches);
  liftMotors.rotateFor(-30 * 5, rotationUnits::deg);
  Drivetrain.driveFor(24, inches);
}

void rightAuton() {
  drivetrain.turnFor(360, degrees);
  Drivetrain.driveFor(12, inches);
  Drivetrain.turnFor(45, degrees);
  Drivetrain.driveFor(9, inches);
  liftMotors.rotateFor(-40 * 15, rotationUnits::deg);
  Drivetrain.driveFor(-9, inches);
  liftMotors.rotateFor(-30 * 15, rotationUnits::deg);
  Drivetrain.turnFor(20, degrees);
  Drivetrain.driveFor(12, inches);
  liftMotors.rotateFor(15 * 15, rotationUnits::deg);
  Drivetrain.driveFor(-6, inches);
  Drivetrain.turnFor(-65, degrees);
  Drivetrain.driveFor(-4, inches);
  liftMotors.rotateFor(-1 * 15, rotationUnits::deg);
  Drivetrain.driveFor(-10, inches);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.ButtonA.pressed(lowPower);
  Controller1.ButtonB.pressed(highPower);

  Brain.Screen.drawCircle(120, 136, 120);
  Brain.Screen.drawCircle(360, 136, 120);

  while (autonType == 0) {
    
    int touchX = Brain.Screen.xPosition();
    int touchY = Brain.Screen.yPosition();

    if (touchX < 240 && touchX > 0) {
      autonType = 1;
      Controller1.Screen.print("Left Autonomous");
      Brain.Screen.clearScreen();
      Brain.Screen.print("Go!");
    }

    if (touchX >= 240) {
      autonType = 2;
      Controller1.Screen.print("Right Autonomous");
      Brain.Screen.clearScreen();
      Brain.Screen.print("Go!");
    }

  Controller1.Screen.newLine();
  Controller1.Screen.print("Go, Go, Go!!!");
  Controller1.Screen.newLine();
  Controller1.Screen.print("On an adventure!");

  }
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
  if (autonType == 1) {
    leftAuton();
  }
  if (autonType == 2) {
    rightAuton();
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
    MotorGroup1.spin(directionType::fwd, Controller1.Axis3.value() * a / 100, velocityUnits::pct);
    MotorGroup10.spin(directionType::rev, Controller1.Axis2.value() * a / 100, velocityUnits::pct);
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
