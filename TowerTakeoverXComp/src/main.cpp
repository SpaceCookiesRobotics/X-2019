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
// FlapMotor1           motor         20              
// CenterMotor          motor         21              
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
competition Competition;
using namespace vex;
void driveChassis (double distance, double sideways){
  LeftMotor.spinFor(distance, turns);
  RightMotor.spinFor(distance, turns);
  CenterMotor.spinFor(sideways, turns); 
}
void turnChassis (double distance, double sideways){
  LeftMotor.spinFor(distance,turns);
  RightMotor.spinFor(distance,turns);
  CenterMotor.spinFor(sideways,turns); //only for moving diagonally 
}
void moveRamp (double angle){
  RCMotor.spinToPosition(angle, degrees);
}
void moveArms (double angle){
  ArmMotorLeft.spinToPosition(angle, degrees);
  ArmMotorRight.spinToPosition(angle, degrees);
}

void pre_auton (){
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Controller1.Screen.print("MAIN");
  Controller2.Screen.print("PARTNER");
  Brain.Screen.print (Brain.Battery.capacity());
  //Brain.Screen.printAt (20, 40, "Red Alliance, Right Square");
  RCMotor.resetRotation();
  ArmMotorLeft.resetRotation();
  ArmMotorRight.resetRotation();
}
void autonomous(){

}
void drivercontrol (){
//double leftSpeed, rightSpeed;
double x, y, z;
  
  while(1) {
      /* 
      leftSpeed = Controller1.Axis3.value();
      rightSpeed = Controller1.Axis2.value ();
      LeftMotor.spin(vex::directionType::fwd, leftSpeed, vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd, rightSpeed, vex::velocityUnits::pct);
      */
      //chassis drive
      x = Controller1.Axis4.value();
      y = Controller1.Axis3.value();
      z = Controller1.Axis1.value();
      LeftMotor.spin(vex::directionType::fwd, y+x, vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd, y-x, vex::velocityUnits::pct);
      CenterMotor.spin(vex::directionType::fwd, -z*0.5 , vex::velocityUnits::pct);
      //arm control -- moves the arm up and down
      ArmMotorLeft.spin(vex::directionType::fwd,Controller2.Axis3.value(),vex::velocityUnits::pct);
      ArmMotorRight.spin(vex::directionType::rev,Controller2.Axis2.value(),vex::velocityUnits::pct);
      
      //flaps -- goes around in circles to pick up the cube
      if(Controller2.ButtonUp.pressing()) {
          FlapMotor1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
          FlapMotor2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      } 
      else if (Controller2.ButtonDown.pressing()){
          FlapMotor1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
          FlapMotor2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      }
      else {
          FlapMotor2.stop();
          FlapMotor1.stop();
      }
      
      
      //Ramp control
      RCMotor.spin(vex::directionType::fwd,Controller2.Axis1.value(),vex::velocityUnits::pct);
      
      vex::task::sleep(20); //leave this at end of the while loop
  }

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Run the pre-autonomous function. 
  pre_auton();

  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(drivercontrol);

}
