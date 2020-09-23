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
int AutonType = 0;
int BrainScreenX = 480;
int BrainScreenY = 240; 

int whichPressed(int x, int y){
  if (y< BrainScreenY/2){
    if (x<BrainScreenX/2){
      return 1;
    }
    else{
      return 2;
    }
  }
  else {
    if(x< BrainScreenX/2){
      return 3;
    }
    else{
      return 4;
    }
  }
}

/*------------------------------------------------------------------*/
/*                          Robot Functions                         */
/*                  designed for specific parts of                  */
/*        robot actions to be used to symplify auton programing     */       
/*                          based on time                           */
/*------------------------------------------------------------------*/
void driveForward(double percent, double wait){
    LeftMotor.spin(directionType::fwd, percent, velocityUnits::pct);
    RightMotor.spin(directionType::fwd, percent, velocityUnits::pct);
    task::sleep(wait);
}
void driveBackward(double percent, double wait){
    LeftMotor.spin(directionType::rev, 100, velocityUnits::pct);
    RightMotor.spin(directionType::rev, 100, velocityUnits::pct);
    task::sleep(wait);
}
void turnRight(double wait){
    LeftMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    RightMotor.spin(directionType::rev, 100, velocityUnits::pct);
    task::sleep(wait);
}
void turnLeft(double wait){
    LeftMotor.spin(directionType::rev, 100, velocityUnits::pct);
    RightMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(wait);
}
void stopChassis(){
    LeftMotor.stop();
    RightMotor.stop();
}
void upRamp (double wait){
    RampMotor.spin(directionType::fwd, 100,velocityUnits::pct);
    task::sleep(wait);
}
void downRamp (double wait){
    RampMotor.spin(directionType::rev, 100,velocityUnits::pct);
    task::sleep(wait);
}
void stopRamp (){
    RampMotor.stop();
}
void upArms(double wait){
    ArmMotorLeft.spin(directionType::fwd, 100, velocityUnits::pct);
    ArmMotorRight.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(wait);
}
void downArms(double wait){
    ArmMotorLeft.spin(directionType::rev, 100, velocityUnits::pct);
    ArmMotorRight.spin(directionType::rev, 100, velocityUnits::pct);
    task::sleep(wait);
}
void stopArms(){
    ArmMotorLeft.stop(brakeType::hold);
    ArmMotorRight.stop(brakeType::hold);
}
void intake(double wait){
    FlapMotor1.spin(directionType::fwd,85,velocityUnits::pct);
    FlapMotor2.spin(directionType::fwd,85,velocityUnits::pct);
    task::sleep(wait);
}
void outtake(double wait){
    FlapMotor1.spin(directionType::rev,100,velocityUnits::pct);
    FlapMotor2.spin(directionType::rev,100,velocityUnits::pct);
    task::sleep(wait);
}
void stopRollers(){
    FlapMotor1.stop();
    FlapMotor2.stop();
}
void intakeForward(double percent, double wait){
    LeftMotor.spin(directionType::fwd,percent,velocityUnits::pct);
    RightMotor.spin(directionType::fwd,percent,velocityUnits::pct);
    FlapMotor1.spin(directionType::fwd,85,velocityUnits::pct);
    FlapMotor2.spin(directionType::fwd,85,velocityUnits::pct);
    task::sleep(wait);    
}
void intakeBackward(double wait){
    LeftMotor.spin(directionType::rev,100,velocityUnits::pct);
    RightMotor.spin(directionType::rev,100,velocityUnits::pct);
    FlapMotor1.spin(directionType::fwd,85,velocityUnits::pct);
    FlapMotor2.spin(directionType::fwd,85,velocityUnits::pct);
    task::sleep(wait);    
}
void intakeLeft(double wait){
    FlapMotor1.spin(directionType::fwd,85,velocityUnits::pct);
    FlapMotor2.spin(directionType::fwd,85,velocityUnits::pct);
    LeftMotor.spin(directionType::rev,100,velocityUnits::pct);
    RightMotor.spin(directionType::fwd,100,velocityUnits::pct);
    task::sleep(wait);
}
void intakeRight(double wait){
    FlapMotor1.spin(directionType::fwd,85,velocityUnits::pct);
    FlapMotor2.spin(directionType::fwd,85,velocityUnits::pct);
    LeftMotor.spin(directionType::fwd,100,velocityUnits::pct);
    RightMotor.spin(directionType::rev,100,velocityUnits::pct);
    task::sleep(wait);
}
void simplePreLoadAuton(){
    driveBackward(100, 1000); //drive back at full speed for 1000 millisec to score preload
    driveForward(100, 1000); //drive away at full speed for 1000 millisec to make sure it stays scored
    stopChassis(); //stop driving 
    //push out the rollers by having the ramp go up and back down
    upRamp(500); //up for 500 millisec
    downRamp(500); //down for 500 millisec
    stopRamp(); //stop moving the ramp
}
void RedSideAuton (){//Red Side, towards the smaller goal 
    //push out the rollers by having the ramp go up and back down
    upRamp(700); //up for 700 millisec
    downRamp(700); //down for 700 millisec
    stopRamp(); //stop moving the ramp 
    task::sleep(50); //waiting here 'cause trisha said so
    intakeForward(75,3500); //drive into the cube at 75% speed and intake the cubes for 3500 millisec
    stopRollers(); //stop moving the rollers
    driveBackward(100, 2000); //drive back at full speed for 2000 millisec to the goal
    turnRight(900); //turn right for 900 millisec to face the goal
    driveForward(100, 1000); //drive to the goal at full speed for 1000 millisecs
    stopChassis(); //stop driving
    upRamp(750);//stack cubes by moving ramp forwards for 750 millisec 
    outtake(800); //outtake cubes a little bit
    stopRollers(); //stop moving the rollers
    driveBackward(75, 750); //Back away from the cubes at 75% speed for 750 millisec 
    stopChassis(); //stop driving    
} 
 void BlueSideAuton (){ //Blue Side, towards the smaller goal
    //push out the rollers by having the ramp go up and back down
    upRamp(800); //up for 800 millisec
    downRamp(800); //down for 800 millisec
    stopRamp(); //stop moving the ramp 
    task::sleep(50); //waiting here 'cause trisha said so
    intakeForward(60,3800); //drive into the cube at 60% speed and intake the cubes for 3800 millisec
    intake(350);//intake to hold in cubes
    stopRollers(); //stop moving the rollers
    driveBackward(80, 1875); //drive back at 80% speed for 1875 millisec to the goal
    intakeLeft(940);//turn left at a certain angle to face the goal and intake to hold in the cubes for 940 millisec
    stopRollers(); //stop moving the rollers
    driveForward(100, 900); //drive to the goal at full speed for 900 millisecs
    stopChassis(); //stop driving
    upRamp(750);//stack cubes by moving ramp forwards for 750 millisec 
    outtake(800); //outtake cubes a little bit
    stopRollers(); //stop moving the ramp
    driveBackward(75, 750); //Back away from the cubes at 75% speed for 750 millisec 
    stopChassis(); //stop driving
}
/* *******************************************************|
|   robot Functions
|   specifically for different actions for autonomous
|******************************************************* */
void driveChassis(double distance, double sideways) { //moves the chassis motors a certain number of turns so the chassis can move linearly
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
 spinIntake (-3); //runs the intake to outtake the motors just a little to make sure they go into the goal
 moveRamp(10); //moves the ramp up to position it against the goal
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
 spinIntake (-3); //runs the intake to outtake the motors just a little to make sure they go into the goal
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
 spinIntake (-3); //runs the intake to outtake the motors just a little to make sure they go into the goal
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
 spinIntake (-3); //runs the intake to outtake the motors just a little to make sure they go into the goal
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
  Brain.Screen.print("%d percent battery left",Brain.Battery.capacity());
  //resets the encoder values for the ramp control & arms 
  //useful for autonomous codes
  RampMotor.resetRotation();
  ArmMotorLeft.resetRotation();
  ArmMotorRight.resetRotation();
//Auton Select
  int page = 1;
  int pageMax = 2;

  while (true){
  //list on controller (^X >A vB <Y)
  if (page == 1){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("X: Red, Left (1)");
    Controller1.Screen.newLine();
    Controller1.Screen.print("A: Blue, Right (2)");
    Controller1.Screen.newLine();
    Controller1.Screen.print("page 1 of 2");
  }
  else if (page == 2){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor( 1,1);
    Controller1.Screen.print("B: Red, Left (3)");
    Controller1.Screen.newLine();
    Controller1.Screen.print("Y: Blue, Right (4)");
    Controller1.Screen.newLine();
    Controller1.Screen.print("page 2 of 2");
  }
 //List on Brain 
  Brain.Screen.drawLine(0, BrainScreenY/2, BrainScreenX, BrainScreenY/2);
  Brain.Screen.drawLine(BrainScreenX/2, 0, BrainScreenX/2, BrainScreenY);
  Brain.Screen.setCursor(2,2);
  Brain.Screen.print("X: Red, Left (1)");
  Brain.Screen.newLine();
  Brain.Screen.print("[NOT TESTED]");
  Brain.Screen.setCursor(2,27);
  Brain.Screen.print("A: Blue, Right (2)");
  Brain.Screen.setCursor(3, 27);
  Brain.Screen.print("[NOT TESTED]");
  Brain.Screen.setCursor(8,2);
  Brain.Screen.print("B: Red, Right (3)");
  Brain.Screen.setCursor(8,27);
  Brain.Screen.print("Y: Blue, Left (4)");

  //Wait for selection 
  int x, y;
  while (AutonType ==0){
    if (Brain.Screen.pressing()) {
      x = Brain.Screen.xPosition();
      y = Brain.Screen.yPosition();
      AutonType = whichPressed(x, y);
    }
    else if (Controller1.ButtonRight.pressing() || Controller1.ButtonDown.pressing()){
      page+= 1;
      if (page > pageMax){
        page = 1;
      }
      break;
    } 
    else if (Controller1.ButtonLeft.pressing() || Controller1.ButtonUp.pressing()){
      page -= 1;
      if (page < 1){
        page = pageMax;
      }
      break;
    }
    else if (Controller1.ButtonX.pressing()){
      AutonType = 1;
    }
    else if (Controller1.ButtonA.pressing()){
      AutonType = 2;
    }
    else if (Controller1.ButtonB.pressing()){
      AutonType = 3;
    }
    else if (Controller1.ButtonY.pressing()){
      AutonType = 4;
    }    
  }//while (AutonType)

  //Keep Logging until Selection is made 
    if (AutonType >0){
      break;
    }
  }//while (true)
  
  //Display Selction on Controller
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Autonmous Routine");
  Controller1.Screen.newLine();
  Controller1.Screen.print("%d Selected", AutonType);

  //Display Selection on brain
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Autonmous Routine %d selected", AutonType);
  
  //must return for autonomous or driverControl to run
  return;
}

void autonomous(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);

  if (AutonType == 1){
    Brain.Screen.print("Running Red, Left Side Autonomous");
    redSquareLeftauton();
  } 
  else if (AutonType == 2){
    Brain.Screen.print("Running Blue, Right Side Autonomous");
    blueSquareRightauton();
  } 
  else if (AutonType == 3){
    Brain.Screen.print("Running Red, Right Side Autonomous");
    RedSideAuton();
    //redRightSideAuton();
  } 
  else if (AutonType == 4){
    Brain.Screen.print("Running Blue, Right Side Autonomous");
    BlueSideAuton();
    //blueLeftSideAuton();
  } 
  else if (AutonType == 0) {
    Brain.Screen.print("Running One Cube Autonomous");
    simplePreLoadAuton();
    //simpleAuton();//scores the preload and flips out the intake rollers
  }

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
    /*if (Controller2.ButtonX.pressing()) {
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
    }*/
    //the regular control for the arms
      // both are controlled by moving the left pot(joystick) on the 2nd controller up and down
      ArmMotorLeft.spin(forward, Controller2.Axis3.value(), pct);
      ArmMotorRight.spin(forward, Controller2.Axis3.value(), pct);
    // flaps -- goes around in circles to pick up the cube
    if (Controller2.ButtonUp.pressing()) {
      //moves the intake rollers so they intake cubes
      FlapMotor1.spin(forward, 80, pct);
      FlapMotor2.spin(forward, 80, pct);
    } else if (Controller2.ButtonDown.pressing()) {
      //moves the intake rollers so they outtake cubes
      FlapMotor1.spin(reverse, 80, pct);
      FlapMotor2.spin(reverse, 80, pct);
    } else {
      //keeps the motors from moving when the buttons are not pressed
      FlapMotor2.stop();
      FlapMotor1.stop();
    }

    // Ramp control
    RampMotor.spin(forward, Controller2.Axis1.value()/2, pct); //moves the cube ramp up and down

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
