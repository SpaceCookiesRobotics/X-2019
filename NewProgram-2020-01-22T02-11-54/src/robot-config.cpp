#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor FlapMotor1 = motor(PORT1, ratio36_1, false);
motor RampMotor = motor(PORT2, ratio18_1, false);
motor LeftMotor = motor(PORT3, ratio18_1, true);
motor RightMotor = motor(PORT10, ratio18_1, false);
motor ArmMotorLeft = motor(PORT4, ratio18_1, true);
motor FlapMotor2 = motor(PORT5, ratio36_1, true);
motor ArmMotorRight = motor(PORT6, ratio18_1, false);
motor CenterMotor = motor(PORT21, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}