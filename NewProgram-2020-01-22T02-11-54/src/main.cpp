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
// Controller1          controller                    
// Controller2          controller                    
// FlapMotor1           motor         1               
// RampMotor            motor         2               
// LeftMotor            motor         3               
// RightMotor           motor         10              
// ArmMotorLeft         motor         4               
// FlapMotor2           motor         5               
// ArmMotorRight        motor         6               
// CenterMotor          motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Competition;
//motor_group ArmMotors = motor_group (ArmMotorLeft,ArmMotorRight);
/*---------------------------------------------------------------------------*/
/*                          Lauren's Functions                               */
/*                                                                           */
/*  setButton sets the description (desc) and color (c) to be used for a     */
/*  button on the brain screen. The position (pos) of the botton is given.   */
/*  Buttons 1-3 appear on the first row and buttons 4-6 appear on the        */
/*  second row. The description is also printed to the controller screen.    */
/*  Make sure to specify what controller button is used in the description.  */
/*                                                                           */
/*  clearScreens clears the brain and controller screens.                    */
/*                                                                           */
/*  pointInRectangle checks if the point (x,y) falls within the rectangle    */
/*  with corners (x1,y1) and (x2,y2), where x1 < x2 and y1 < y2. It returns  */
/*  a boolean (true or false). It is useful for checking to see if a point   */
/*  pressed on the screen corresponds to a button.                           */
/*                                                                           */
/*  whichButtonPressed determines out what button on the screen was pressed  */
/*  by the (x,y) point. It returns an integer corresponding to the button,   */
/*  between 1 and 6. It return 0 if the point is not on any button.          */
/*---------------------------------------------------------------------------*/

void setButton(int pos, const char* desc) { // , color c = black
  // These should be the same as in whichButtonPressed
  int size = 80;
  int xs[8] = {10, 120, 230, 10, 120, 230};
  int ys[8] = {25, 25, 25, 145, 145, 145};
  int brows[8] = {1, 1, 1, 7, 7, 7};
  int bcols[8] = {2, 13, 24, 2, 13, 24};
  int crows[8] = {1, 2, 3, 1, 2, 3};
  int ccols[8] = {1, 1, 1, 12, 12, 12};

  // Draw the button on brain screen
  Brain.Screen.drawRectangle(xs[pos-1], ys[pos-1], size, size);
  Brain.Screen.setCursor(brows[pos-1], bcols[pos-1]);
  Brain.Screen.print(desc);

  // Print options to controller screen
  Controller1.Screen.setCursor(crows[pos-1], ccols[pos-1]);
  Controller1.Screen.print(desc);
}

void clearScreens() {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();
  task::sleep(500);
}

bool pointInRectangle(int x, int y, int x1, int y1, int x2, int y2) {
  if ((x >= x1 && x <= x2) && (y >= y1 && y <= y2)) {
    return true;
  } else {
    return false;
  }
}

int whichButtonPressed(int x, int y) {
  // These should be the same as in setButton
  int size = 100;
  int xs[8] = {10, 120, 230, 10, 120, 230};
  int ys[8] = {25, 25, 25, 145, 145, 145};

  // Return which button if point is in defined regions
  for (int i=1; i <= 8; i++) {
    if (pointInRectangle(x, y, xs[i-1], ys[i-1], xs[i-1]+size, ys[i-1]+size)) {
      return i;
    }
  }

  // Return 0 if not in defined button regions
  return 0;
}
/* *******************************************************|
|   robot Functions
|   specifically for different actions for autonomous
|******************************************************* */
void driveChassis(double distance, double sideways) { //moves the chassis motors a certain number of turns so the chassis can move linearlly
  LeftMotor.startRotateFor(distance, turns);
  RightMotor.rotateFor(distance, turns);
  CenterMotor.rotateFor(sideways, turns);//only needed for moving sideways or used in conjunction with the other motors to move diagonally
}
void turnChassis(double distance, double sideways) { //moves the chassis motors a certain number of turns so the chassis can turn
  LeftMotor.startRotateFor(distance, turns);
  RightMotor.rotateFor(-distance, turns);
  CenterMotor.rotateFor(sideways, turns); //might aide in turning??? not sure if we need this for this function
}
void moveRamp(double angle) { //moves the ramp motor to a certain angle
  RampMotor.spinToPosition(angle, degrees);
}
void moveArms(double angle) { //moves the arms to a certain angle
  ArmMotorLeft.spinToPosition(angle, degrees);  
  ArmMotorRight.spinToPosition(angle, degrees);
}
void spinIntake (double rotations){
  FlapMotor1.startRotateFor(rotations, turns);
  FlapMotor2.rotateFor(rotations,turns);
}

/* ******************************
|                                |
|    Different Autonomous Codes  |
|                                |
******************************* */

void simpleAuton(void) { // scores the preload and releases the intake rollers
  driveChassis(-4, 0);  // moves backward 4 rotations
  driveChassis(0, 0); // stops the chassis
  driveChassis(5, 0); // moves forward 5 rotations
  driveChassis(0, 0); // stops the chassis
  moveRamp(10); // moves the ramp up 10 rotations to release the intake rollers
  moveRamp(-10);  // moves the ramp back down to the original position, ready for the start of the match
}
void redSquareLeftauton(void) { //scores in the larger goal
  moveRamp(10); // moves the ramp up 10 rotations to release the intake rollers
  moveRamp(-10);  // moves the ramp back down to the original position, ready for the start of the match
  spinIntake (30); //run the intake rollers for 30 rotations to intake the preload
  turnChassis(-15,0); //turns the robot left to face the cube to the right of the red square
  driveChassis(30,0); //drives the robot to the cube
  spinIntake (30); //runs the intake rollers for 30 rotations to intake the cube
  turnChassis(-15,0); //turns the robot left to face the cube in the other red square
  driveChassis(20,0); //drive the robot towards the cube 
  spinIntake (30); //runs the intake rollers for 30 rotations to intake the cube
  turnChassis (-15,0); //turns the robot left to face the goal
  driveChassis (5,0); //drives forward to position the cubes right up against the goal
  spinIntake (-3); //runs the intake to outake the motors just a little to make sure they go into the goal
  moveRamp(10); //moves the ramp up to positition it agaisnt the goal
  moveRamp(-10); //moves the ramp back away from the stack
  driveChassis(-20,0); //drives chassis away from the goal so the score is legal
} 
void redRightSideAuton(void){ //scores in the smaller goal 
  moveRamp(10); // moves the ramp up 10 rotations to release the intake rollers
  moveRamp(-10);  // moves the ramp back down to the original position, ready for the start of the match
  driveChassis(30,0); //drives the robot to the cubes
  spinIntake (200); //runs the intake rollers for 200 rotations to intake the cube
  driveChassis(-25,0); //drives back towards the goal with the cubes
  turnChassis (15,0); //turns the robot right to face the goal
  driveChassis (5,0); //drives forward to position the cubes right up against the goal
  spinIntake (-3); //runs the intake to outake the motors just a little to make sure they go into the goal
  moveRamp(10); //moves the ramp up to position it against the goal
  moveRamp(-10); //moves the ramp back away from the stack
  driveChassis(-20,0); //drives chassis away from the goal so the score is legal
} 
void blueSquareRightauton(void) { //scores in the larger goal
  moveRamp(10); // moves the ramp up 10 rotations to release the intake rollers
  moveRamp(-10);  // moves the ramp back down to the original position, ready for the start of the match
  spinIntake (30); //run the intake rollers for 30 rotations to intake the preload
  turnChassis(15,0); //turns the robot right to face the cube to the right of the red square
  driveChassis(30,0); //drives the robot to the cube
  spinIntake (30); //runs the intake rollers for 30 rotations to intake the cube
  turnChassis(15,0); //turns the robot right to face the cube in the other red square
  driveChassis(20,0); //drive the robot towards the cube 
  spinIntake (30); //runs the intake rollers for 30 rotations to intake the cube
  turnChassis (15,0); //turns the robot right to face the goal
  driveChassis (5,0); //drives forward to position the cubes right up against the goal
  spinIntake (-3); //runs the intake to outake the motors just a little to make sure they go into the goal
  moveRamp(10); //moves the ramp up to position it against the goal
  moveRamp(-10); //moves the ramp back away from the stack
  driveChassis(-20,0); //drives chassis away from the goal so the score is legal
} 
 void blueLeftSideAuton (void){ //scores in the smaller goal
  moveRamp(10); // moves the ramp up 10 rotations to release the intake rollers
  moveRamp(-10);  // moves the ramp back down to the original position, ready for the start of the match
  driveChassis(30,0); //drives the robot to the cubes
  spinIntake (200); //runs the intake rollers for 200 rotations to intake the cube
  driveChassis(-25,0); //drives back towards the goal with the cubes
  turnChassis (-15,0); //turns the robot left to face the goal
  driveChassis (5,0); //drives forward to position the cubes right up against the goal
  spinIntake (-3); //runs the intake to outake the motors just a little to make sure they go into the goal
  moveRamp(10); //moves the ramp up to position it against the goal
  moveRamp(-10); //moves the ramp back away from the stack
  driveChassis(-20,0); //drives chassis away from the goal so the score is legal
 }
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*                                                                           */
/*  Note from Lauren:                                                        */
/*  Autonomous selection can be done here. An example is provided to         */
/*  demonstrate how it works. Please modify to suit your needs.              */
/*---------------------------------------------------------------------------*/

void preAuton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  //labeling the controllers during matches
  Controller1.Screen.print("MAIN");
  Controller2.Screen.print("PARTNER");
  //displays the percentage of batter level left for the robot when the code is turned on
  Brain.Screen.print(Brain.Battery.capacity());
  //displays which auton code is running <-- currently not necessarily needed 
  // Brain.Screen.printAt (20, 40, "Red Alliance, Right Square");
  
  //resets the encoder values for the ramp control & arms 
  //useful for autonomous codes
  RampMotor.resetRotation();
  ArmMotorLeft.resetRotation();
  ArmMotorRight.resetRotation();
  // Selection of autonomous tasks using brain screen or controller
  // First task: Define buttons
  clearScreens();
  setButton(1, "Y:");
  setButton(2, "X:");
  setButton(3, "A:");
  setButton(4, "Left:");
  setButton(5, "Up:");
  setButton(6, "Right:");

  // Second task: Save button selection
  int x, y;
  int button = 0;
  while(button == 0) {
    // If brain screen is touched
    if (Brain.Screen.pressing()) {
      x = Brain.Screen.xPosition();
      y = Brain.Screen.yPosition();

      button = whichButtonPressed(x, y);
    }

    // If controller button is pressed
    else if (Controller1.ButtonY.pressing()) {
      button = 1;
    } else if (Controller1.ButtonX.pressing()) {
      button = 2;
    } else if (Controller1.ButtonA.pressing()) {
      button = 3;
    } else if (Controller1.ButtonLeft.pressing()) {
      button = 4;
    } else if (Controller1.ButtonUp.pressing()) {
      button = 5;
    } else if (Controller1.ButtonRight.pressing()) {
      button = 6;
    }
  }

  clearScreens();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("You selected button %d", button);
}

void autonomous(void) {
  simpleAuton();//scores the preload and flips out the intake rollers

}

void driverControl(void) {
  //defines the different variables for chassis code
  double leftSpeed, rightSpeed, centerSpeed;
  // double x, y, z;

  while (1) {
    // chassis drive
    leftSpeed = Controller1.Axis3.value(); //defines the axis for the left side of the chassis
    rightSpeed = Controller1.Axis2.value(); //defines the axis for the right side of the chasssis
    //centerSpeed = Controller1.Axis1.value(); //defines the axis for the 5th wheel
    
    //tank drive with the 5th wheel
    LeftMotor.spin(forward, leftSpeed, pct); //left side
    RightMotor.spin(forward, rightSpeed, pct); //right side
   /*
    if(Controller1.ButtonL1.pressing()){
      CenterMotor.spin(forward, 50, pct); //5th wheel
    }
    else if(Controller1.ButtonR1.pressing()){
      CenterMotor.spin(reverse, 50, pct); //5th wheel
    }
    else{
      CenterMotor.stop(); //5th wheel
    }*/

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
    RampMotor.spin(forward, Controller2.Axis4.value(), pct); //moves the cube ramp up and down

    wait(20, msec); // Sleep the task for a short amount of time
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(driverControl);

  // Run the pre-autonomous function.
  preAuton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
