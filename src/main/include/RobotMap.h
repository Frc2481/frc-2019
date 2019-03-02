#ifndef ROBOT_MAP_H
#define ROBOT_MAP_H

#define DRIVER_XBOX_CONTROLLER_ID 0
#define OPERATOR_XBOX_CONTROLLER_ID 1
#define TEST_XBOX_CONTROLLER_ID 2

/*
RoboRio -> CargoIntake -> BL Drive -> BR Drive -> Ball intake in/out -> PCM bottom -> FL Steer -> FR Drive -> FL Drive -> FL Steer ->
    right elevator motor -> BL Steer -> BR Steer -> PDP -> left elevator up/down -> PCM (top of elevator)

PDP Layout:
    Left Elevator Motor 0
    Right Elevator Motor 1
    FL Drive 2
    FR Drive 3
    BR Steer 4
    BL Steer 5
    FR Steer 6
    FL Steer 7
    BLANK 8
    Intake Slide Motor 9
    Hatch Slide Motor 10
    Upper PCM 11
    BL Drive 12
    BR Drive 13
    Climber 14
    Cargo Intake 15
*/


// talonSRX
#define FR_STEER_MOTOR_ID 4 //1
#define BR_STEER_MOTOR_ID 8 //2
#define BL_STEER_MOTOR_ID 6 //3
#define FL_STEER_MOTOR_ID 2 //4

#define HATCH_SLIDE_MOTOR_ID 66 //5
#define MASTER_ELEVATOR_MOTOR_ID 63 //6
#define CARGO_INTAKE_EXTEND_MOTOR_ID 54 //7

// victorSPX
#define FR_DRIVE_MOTOR_ID 3 //1
#define BR_DRIVE_MOTOR_ID 7 //2
#define BL_DRIVE_MOTOR_ID 5 //3
#define FL_DRIVE_MOTOR_ID 1 //4

#define SLAVE_ELEVATOR_MOTOR_ID 5
#define CARGO_INTAKE_MOTOR_ID 6

// sparkMAX
#define CLIMBER_MOTOR_ID 1

// solenoid
#define CARGO_TOOL_SOLENOID 0, 0, 1
#define HATCH_EXTENDER_SOLENOID 0, 2, 3
#define HATCH_TOOL_SOLENOID 0, 4, 5

#define CLIMBER_SOLENOID 1, 0, 1

// limit switch
// #define TOOL_CHANGER_LIMIT_SWITCH 0
#define IR_SENSOR_BRIGHT 0
#define IR_SENSOR_DIM 1
#define CARGO_BEAM_BREAK_SENSOR 2

#endif // ROBOT_MAP_H
