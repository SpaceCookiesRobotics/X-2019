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
void driveChassis(double distance, double sideways) { //moves the chassis motors a certain number of turns so the chassis can move linearlly
  LeftMotor.spinFor(distance, turns, true);
  RightMotor.spinFor(distance, turns, true);
  CenterMotor.spinFor(sideways, turns);//only needed for moving sideways or used in conjunction with the other motors to move diagonally
}
void turnChassis(double distance, double sideways) { //moves the chassis motors a certain number of turns so the chassis can turn
  LeftMotor.spinFor(distance, turns);
  RightMotor.spinFor(-distance, turns);
  CenterMotor.spinFor(sideways, turns); //might aide in turning??? not sure if we need this for this function
}
void moveRamp(double angle) { //moves the ramp motor to a certain angle
  RCMotor.spinToPosition(angle, degrees);
 }

void moveArms(double angle) { //moves the arms to a certain angle
  ArmMotorLeft.spinToPosition(angle, degrees);
  ArmMotorRight.spinToPosition(angle, degrees);
}

void simpleAuton(void) { // scores the preload and releases the intake rollers
  driveChassis(-5, 0);  // moves forward 50 rotations
  driveChassis(5, 0);   // moves back 50 rotations
  driveChassis(0, 0);    // stops the chassis
  moveArms(45); // moves the arms up to the position 45 degrees to releace the intake rollers
  moveArms(0);  // moves the arms back down to the original position, ready for the start of the match
}
void redSquareLeftauton(void) {
  moveArms(45); // moves the arms up to the position 45 degrees to releace the intake rollers
  moveArms(0);  // moves the arms back down to the original position, ready for the start of the match
  turnChassis(15,0); //turns the robot to face the cube
  driveChassis(30,0); //drives the robot to the cube
  
  
}

void pre_auton() {
//labeling the controllers during matches
  Controller1.Screen.print("MAIN");
  Controller2.Screen.print("PARTNER");
  //displays the percentage of batter level left for the robot when the code is turned on
  Brain.Screen.print(Brain.Battery.capacity());
  //displays which auton code is running <-- currently not necessarily needed 
  // Brain.Screen.printAt (20, 40, "Red Alliance, Right Square");
  
  //resets the encoder values for the ramp control & arms 
  //useful for autonomous codes
  RCMotor.resetRotation();
  ArmMotorLeft.resetRotation();
  ArmMotorRight.resetRotation();
}
void autonomous() {
  simpleAuton();//scores the preload and flips out the intake rollers
}

void drivercontrol() {
  //defines the different variables for chassis code
  double leftSpeed, rightSpeed, centerSpeed;
  // double x, y, z;

  while (1) {
    // chassis drive
    leftSpeed = Controller1.Axis3.value(); //defines the axis for the left side of the chassis
    rightSpeed = Controller1.Axis2.value(); //defines the axis for the right side of the chasssis
    centerSpeed = Controller1.Axis1.value(); //defines the axis for the 5th wheel
    
    //tank drive with the 5th wheel
    LeftMotor.spin(forward, leftSpeed, pct); //left side
    RightMotor.spin(forward, rightSpeed, pct); //right side
    CenterMotor.spin(forward, centerSpeed, pct); //5th wheel

    /*
    x = Controller1.Axis1.value(); //defines the axis for left and right
    y = Controller1.Axis2.value(); //defines the axis for forwards and backwards
    z = Controller1.Axis4.value(); //defines the axis for sideways (aka the 5th wheel)
    //Holonomic drive
    LeftMotor.spin( forward, y+x,  pct); //left side
    RightMotor.spin( forward, y-x,  pct); //right side
    CenterMotor.spin( forward, -z*0.5 ,  pct); //5th wheel
    */
    // arms control
    if (Controller2.ButtonX.pressing()) {
      // move the motors up so they are parallel to the ground
      ArmMotorLeft.spinToPosition(45, degrees);
      ArmMotorRight.spinToPosition(45, degrees);
      //the motors hold the arms at that position
      ArmMotorLeft.setStopping(hold);
      ArmMotorRight.setStopping(hold);
    } else if (Controller2.ButtonR1.pressing()) {
      // move the motors up part of the way
      ArmMotorLeft.spinToPosition(22.5, degrees); 
      ArmMotorRight.spinToPosition(22.5, degrees);
      //the motors hold the arms at that position
      ArmMotorLeft.setStopping(hold);
      ArmMotorRight.setStopping(hold);
    } else {
      //the regular control for the arms
      // both are controlled by moving the left pot(joystick) on the 2nd controller up and down
      ArmMotorLeft.spin(forward, Controller2.Axis3.value(), pct);
      ArmMotorRight.spin(forward, Controller2.Axis3.value(), pct);
    }

    // flaps -- goes around in circles to pick up the cube
    if (Controller2.ButtonUp.pressing()) {
      //moves the intake rollers so they intake cubes
      FlapMotor1.spin(forward, 100, pct);
      FlapMotor2.spin(forward, 100, pct);
    } else if (Controller2.ButtonDown.pressing()) {
      //moves the intake rollers so they outtake cubes
      FlapMotor1.spin(reverse, 100, pct);
      FlapMotor2.spin(reverse, 100, pct);
    } else {
      //keeps the motors from moving when the buttons are not pressed
      FlapMotor2.stop();
      FlapMotor1.stop();
    }

    // Ramp control
    RCMotor.spin(forward, Controller2.Axis4.value(), pct); //moves the cube ramp up and down

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
