using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RightMotor;
extern motor LeftMotor;
extern motor RCMotor;
extern motor ArmMotorRight;
extern motor ArmMotorLeft;
extern motor FlapMotor2;
extern motor FlapMotor1;
extern motor CenterMotor;
extern controller Controller1;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );