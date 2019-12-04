/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Space Cookies                                    */
/*    Created:      Tue Oct 08 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightMotor           motor         10              
// LeftMotor            motor         3               
// RCMotor              motor         2               
// ArmMotorRight        motor         18              
// ArmMotorLeft         motor         11              
// FlapMotor2           motor         1               
// FlapMotor1           motor         17              
// CenterMotor          motor         21              
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
competition Competition;
using namespace vex;
void driveChassis(double distance, double sideways) {
  LeftMotor.spinFor(distance, turns);
  RightMotor.spinFor(distance, turns);
  CenterMotor.spinFor(sideways, turns);
}
void turnChassis(double distance, double sideways) {
  LeftMotor.spinFor(distance, turns);
  RightMotor.spinFor(distance, turns);
  CenterMotor.spinFor(sideways, turns); // only for moving diagonally
}
void moveRamp(double angle) { 
  RCMotor.spinToPosition(angle, degrees); 
}
void moveArms(double angle) {
  ArmMotorLeft.spinToPosition(angle, degrees);
  ArmMotorRight.spinToPosition(angle, degrees);
}

void simpleAuton(void) { //scores the preload and releases the intake rollers
  driveChassis(-50, 0); //moves forward 50 rotations
  driveChassis(50, 0); //moves back 50 rotations
  driveChassis(0, 0); //stops the chassis
  moveArms(45); //moves the arms up to the position 45 degrees to releace the intake rollers
  moveArms(0); //moves the arms back down to the original position, ready for the start of the match
}
void redSquareLeftauton(void){

}

void pre_auton() {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Controller1.Screen.print("MAIN");
  Controller2.Screen.print("PARTNER");
  Brain.Screen.print(Brain.Battery.capacity());
  // Brain.Screen.printAt (20, 40, "Red Alliance, Right Square");
  RCMotor.resetRotation();
  ArmMotorLeft.resetRotation();
  ArmMotorRight.resetRotation();
}
void autonomous() {

}
void drivercontrol() {
  double leftSpeed, rightSpeed, centerSpeed;
  // double x, y, z;

  while (1) {
    // chassis drive

    leftSpeed = Controller1.Axis3.value();
    rightSpeed = Controller1.Axis2.value();
    centerSpeed = Controller1.Axis1.value();
    LeftMotor.spin(forward, leftSpeed, pct);
    RightMotor.spin(forward, rightSpeed, pct);
    CenterMotor.spin(forward, centerSpeed, pct);

    /*
    x = Controller1.Axis1.value();
    y = Controller1.Axis2.value();
    z = Controller1.Axis4.value();
    LeftMotor.spin( forward, y+x,  pct);
    RightMotor.spin( forward, y-x,  pct);
    CenterMotor.spin( forward, -z*0.5 ,  pct);
    */
    // arms control
    ArmMotorLeft.spin(forward, Controller2.Axis3.value(),  pct);
    ArmMotorRight.spin(forward, Controller2.Axis3.value(),  pct);

  if (Controller2.ButtonX.pressed(void)){
    ArmMotorLeft.spinToPosition(45, degrees);
    ArmMotorRight.spinToPosition(45, degrees);
  }


    // flaps -- goes around in circles to pick up the cube
    if (Controller2.ButtonUp.pressing()) {
      FlapMotor1.spin(forward, 100,  pct);
      FlapMotor2.spin(forward, 100,  pct);
    } else if (Controller2.ButtonDown.pressing()) {
      FlapMotor1.spin(reverse, 100,  pct);
      FlapMotor2.spin(reverse, 100,  pct);
    } else {
      FlapMotor2.stop();
      FlapMotor1.stop();
    }

    // Ramp control
    RCMotor.spin( forward, Controller2.Axis4.value(), pct);

    vex::task::sleep(20); // leave this at end of the while loop
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);
}
