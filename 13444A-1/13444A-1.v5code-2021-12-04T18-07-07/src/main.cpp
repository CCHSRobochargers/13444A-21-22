
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
int b = 1;
int n = 1;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void brakeField() {
  leftMotors.setStopping(brakeType::coast);
  rightMotors.setStopping(brakeType::coast);
  b = 1;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Coast");
}

void holdBrake() {
  leftMotors.setStopping(brakeType::hold);
  rightMotors.setStopping(brakeType::hold);
  b = 2;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Coast");
}

void autoBalance() {
  leftMotors.setStopping(brakeType::hold);
  rightMotors.setStopping(brakeType::hold);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Auto Balance");
  while(true) {
    if (Sensor.pitch() < -13) {
      while (Sensor.pitch() < -8) {
        leftMotors.spin(directionType::rev, 50/n, percentUnits::pct);
        rightMotors.spin(directionType::rev, 50/n, percentUnits::pct);
        if (Controller1.ButtonRight.pressing() == true) {
          break;
        }
      }
    }
    if (Sensor.pitch() > 13) {
      while (Sensor.pitch() > 8) {
        leftMotors.spin(directionType::fwd, 50/n, percentUnits::pct);
        rightMotors.spin(directionType::fwd, 50/n, percentUnits::pct);
        if (Controller1.ButtonRight.pressing() == true) {
          goto leave;
        }
      }
    }
    n = n + 1;
    if (Sensor.pitch() < 1 && Sensor.pitch() > -1) {
      wait(0.5, timeUnits::sec);
      if (Sensor.pitch() < 1 && Sensor.pitch() > -1) {
        n = 1;
      }
    }
    leave:
    if (Controller1.ButtonRight.pressing()) {
      break;
    }
  }
}
void resetBrake() {
  if (b == 1) {
    brakeField();
  }
  if (b == 2) {
    holdBrake();
  }
}

void grab() {
  // grabMotor.spinFor(1, timeUnits::sec, -50, velocityUnits::pct);
  //grabMotor.rotateTo(-55, degrees);
  //wait(250, msec);
  while(grabMotor.torque() < 0.75) {
    grabMotor.spin(directionType::rev);
  }
  grabMotor.stop();
}

void resetGrab() {
  grabMotor.rotateTo(0, rotationUnits::deg, false);
  // wait(600, msec);
}

void driveInches(double inches, int percent) {
  leftMotors.setVelocity(percent, velocityUnits::pct);
  rightMotors.setVelocity(percent, velocityUnits::pct);
  leftMotors.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg, false);
  rightMotors.spinFor(directionType::fwd, (inches / (3.14 * 4)) * 360, rotationUnits::deg);
}

void turnDegrees(double degrees) {
  leftMotors.setStopping(brakeType::brake);
  rightMotors.setStopping(brakeType::brake);
  leftMotors.spinFor(directionType::fwd, (9 * degrees) / 720 + 0.125, rotationUnits::rev, false);
  rightMotors.spinFor(directionType::rev, (9 * degrees) / 720 + 0.125, rotationUnits::rev);
  resetBrake();
  /*
  leftMotors.setVelocity(50, velocityUnits::pct);
  rightMotors.setVelocity(50, velocityUnits::pct);
  Sensor.setHeading(180, rotationUnits::deg);
  if (degrees > 0) {
    while (Sensor.heading() <= degrees + 176.5) {
      leftMotors.spin(directionType::fwd);
      rightMotors.spin(directionType::rev);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(Sensor.heading());
    }
  } else if (degrees < 0) {
    while (Sensor.heading() >= degrees + 183.5) {
      leftMotors.spin(directionType::rev);
      rightMotors.spin(directionType::fwd);
    }
  }
  */
}

int autonType = 0;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.Screen.clearScreen();
  grabMotor.resetRotation();
  grabMotor.setTimeout(300, timeUnits::msec);
  grabMotor.setStopping(brakeType::hold);
  Sensor.calibrate(2000);
  wait(2, sec);
  Controller1.ButtonX.pressed(autoBalance);
  Controller1.ButtonRight.pressed(brakeField);
  Controller1.ButtonB.released(resetBrake);
  Controller1.ButtonDown.pressed(holdBrake);
  Controller1.ButtonY.pressed(resetGrab);
  Controller1.ButtonY.released(grab);
  Brain.Screen.drawRectangle(0, 0, 240, 90, red);
  Brain.Screen.drawRectangle(240, 0, 240, 90, orange);
  Brain.Screen.drawRectangle(0, 90, 240, 90, yellow);
  Brain.Screen.drawRectangle(240, 90, 240, 90, green);
  Brain.Screen.drawRectangle(0, 180, 480, 60, blue);
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
    leftMotors.spinFor(directionType::rev, 1.2, rotationUnits::rev);
    grab();
  }
  if (autonType == 2) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    driveInches(-22, 75);
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
    driveInches(4, 50);
    turnDegrees(45);
    driveInches(6, 50);
    turnDegrees(45);
    driveInches(14, 50);
    turnDegrees(90);
    liftMotors.spinFor(-60 * 5, rotationUnits::deg);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    turnDegrees(90);
    driveInches(6, 50);
    turnDegrees(-90);
    driveInches(12, 100);
    turnDegrees(-90);
    liftMotors.spinFor(-25 * 5, rotationUnits::deg);
    driveInches(16, 50);
    holdBrake();
  }
  if (autonType == 4) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(35 * 5, rotationUnits::deg);
    wait(2, seconds);
    driveInches(4, 50);
    turnDegrees(70);
    driveInches(14, 50);
    turnDegrees(-175);
    driveInches(-8, 25);
    grab();
    turnDegrees(-80);
    driveInches(50, 100);
  }
  if (autonType == 5) {
    liftMotors.spinFor(-60 * 5, rotationUnits::deg, false);
    driveInches(52, 100);
    liftMotors.spinFor(25 * 5, rotationUnits::deg);
    wait(2, seconds);
    driveInches(5, 50);
    turnDegrees(-90);
    driveInches(14, 50);
    turnDegrees(180);
    driveInches(-4, 25);
    grab();
    turnDegrees(-90);
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
    leftMotors.spin(directionType::fwd, Controller1.Axis3.value() * a / 100, velocityUnits::pct);
    rightMotors.spin(directionType::fwd, Controller1.Axis2.value() * a / 100, velocityUnits::pct);
    if (Controller1.ButtonL1.pressing()) {
      liftMotors.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if (Controller1.ButtonL2.pressing()) {
      liftMotors.spin(directionType::rev, 50, velocityUnits::pct);
    } else {
      liftMotors.stop();
    }
    if (Controller1.ButtonB.pressing()) {
      leftMotors.stop(brakeType::brake);
      rightMotors.stop(brakeType::brake);
    } else {
      if (b == 1) {
        leftMotors.setStopping(brakeType::coast);
        rightMotors.setStopping(brakeType::coast);
      } else if (b == 2) {
        leftMotors.setStopping(brakeType::hold);
        rightMotors.setStopping(brakeType::hold);
      }
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
/*gay*/
