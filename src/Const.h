// const.h


#ifndef SRC_CONST_H_
#define SRC_CONST_H_


// autonomous modes
enum Auto { kAutoLeftGear, kAutoRightGear, kAutoRedShoot, kAutoBlueShoot, kAutoStraight };


//OperatorInputs
//	Controllers
#define JOYSTICK_NUMBER 0
#define XBOX_NUMBER 1
//	Set to 1.0 or -1.0
#define INVERT_Y_AXIS 1.0
#define INVERT_X_AXIS -1.0
//	XBox Controller
//		Buttons
#define A_BUTTON  1
#define B_BUTTON  2
#define X_BUTTON  3
#define Y_BUTTON  4
#define RIGHT_BUMPER  6
#define LEFT_BUMPER  5
#define BACK_BUTTON  7
#define START_BUTTON  8
//		XBox Triggers -- Changed for 2016, previously XBOX triggers were both on a single axis
#define XBOX_RIGHT_TRIGGER_AXIS  3
#define XBOX_LEFT_TRIGGER_AXIS  2
#define RIGHT_TRIGGER_MIN  0.5
#define RIGHT_TRIGGER_MAX  1.0
#define LEFT_TRIGGER_MIN  0.5
#define LEFT_TRIGGER_MAX  1.0
#define JOYSTICK_X_AXIS  0
#define JOYSTICK_Y_AXIS  1
#define AXIS0_LEFT_MIN -1.0
#define AXIS0_LEFT_MAX -0.75
#define AXIS0_RIGHT_MIN 0.75
#define AXIS0_RIGHT_MAX 1.0
#define AXIS1_BACK_MIN -1.0
#define AXIS1_BACK_MAX -0.75
#define AXIS1_FORWARD_MIN 0.75
#define AXIS1_FORWARD_MAX 1.0
//	Controller Dead Zones
#define DEADZONE_Y  0.17
#define DEADZONE_X  0.17
#define DEADZONE_Z  0.17


// Drivetrain
#define DT_DEFAULT_DIRECTION 1.0
// Inverts
#define INVERT_LEFT -1.0
#define INVERT_RIGHT 1.0
// Talons ports
#define CAN_LEFT_PORT 0
#define CAN_SECOND_LEFT_PORT 2
#define CAN_RIGHT_PORT 1
#define CAN_SECOND_RIGHT_PORT 3
// Shifter
#define PCM_SHIFT_PORT_LOW 0
#define PCM_SHIFT_MODULE 0
#define CHILD_PROOF_SPEED 0.75
#define FLIP_HIGH_GEAR true
// Ramping
#define RAMPING_RATE_PERIOD 0.10
#define RAMPING_RATE_MIN 0.6
#define RAMPING_RATE_MAX 1.5
#define X_SCALING 0.5
#define Y_SCALING 1.0
#define LEFT_MOTOR_SCALING .97
#define RIGHT_MOTOR_SCALING 1
#define LOWSPEED_MODIFIER_X 0.75
#define LOWSPEED_MODIFIER_Y 0.25
// Encoders
#define ENCODER_TOP_SPEED 0.6
#define ENCODER_WAIT_TIME 168
#define CAN_DISTANCE_PER_PULSE 0.0006708
// Compressor
#define PCM_COMPRESSOR_SOLENOID 0


// Camera
#define USB_CAMERA_FRONT "cam1"
#define USB_CAMERA_REAR "cam0"
#define RLY_CAMERA_LED 0


// Range Finder
#define DIO_RANGEFINDER_ECHO_OUT 1
#define DIO_RANGEFINDER_TRIGGER_IN 2


// Picker
#define PCM_PICKER_SOLENOID_A 5
#define PCM_PICKER_SOLENOID_B 1
#define PCM_PICKER_VENT 4
#define PWM_PICKER_MOTOR 4

// Shooter
//#define PCM_SHOOTER_SOLENOID 2
#define CAN_SHOOTER_MOTOR 4
/*#define DIO_SHOOTER_LIMIT_DOWN 2
#define DIO_SHOOTER_MOTOR_A 3
#define DIO_SHOOTER_MOTOR_B 4*/
#define CAN_SHOOTER_P 0.02
#define CAN_SHOOTER_I 0.0001
#define CAN_SHOOTER_D 0
#define CAN_SHOOTER_F 0.0254
#define CAN_SHOOTER_ENCODER_TICKS 4096
#define SD_SHOOTER_SLIDER_DEFAULT 2.5
#define SHOOTER_SLIDER_TO_RPM -600.0
#define SHOOTER_RADIUS 0.0508


// Climber
#define PCM_CLIMBER_SOLENOID 3
#define PWM_CLIMBER_MOTOR 2


// Portcullis
//#define PWM_PORTCULLIS_MOTOR 3
//#define DIO_PORTCULLIS_LIMIT 0


// Autonomous
#define ALG_AUTONOMOUS_GYRO 0


#endif /* SRC_CONST_H_ */
