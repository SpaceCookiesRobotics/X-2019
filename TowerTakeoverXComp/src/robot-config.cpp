#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RightMotor = motor(PORT10, ratio18_1, false);
motor LeftMotor = motor(PORT3, ratio18_1, true);
motor RCMotor = motor(PORT2, ratio18_1, false);
motor ArmMotorRight = motor(PORT18, ratio18_1, false);
motor ArmMotorLeft = motor(PORT11, ratio18_1, true);
motor FlapMotor2 = motor(PORT1, ratio18_1, false);
motor FlapMotor1 = motor(PORT17, ratio18_1, true);
motor CenterMotor = motor(PORT21, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}