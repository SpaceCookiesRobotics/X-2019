using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern controller Controller2;
extern motor FlapMotor1;
extern motor RampMotor;
extern motor LeftMotor;
extern motor RightMotor;
extern motor ArmMotorLeft;
extern motor FlapMotor2;
extern motor ArmMotorRight;
extern motor CenterMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );