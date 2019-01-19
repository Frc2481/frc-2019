#ifndef ROBOT_PARAMETERS_H
#define ROBOT_PARAMETERS_H

namespace RobotParameters {
    // robot main
	static constexpr unsigned k_updateRate = 50; // Hz

    // drivetrain
    static constexpr bool k_isDriveShiftInverted = true;
    static constexpr double k_openLoopSteerLimitPercent = 0.5; // limit open loop steer for controllability
    static constexpr double k_wheelRad = 0; // in
    static constexpr double k_wheelTrack = 22.375; // in
    static constexpr double k_wheelBase = 27; // in
    static constexpr double k_maxSpeed = 0; // in/s
    static constexpr double k_maxAccel = 0; // in/s^2
    static constexpr double k_maxDeccel = 0; // in/s^2
    static constexpr double k_maxCentripAccel = 0; // in/s^2
    static constexpr double k_cornerStiffCoeff = 0;
    static constexpr double k_driveMotorToEncoderGearRatioLow = 1; // gear ratio from drive motor to encoder in low gear
    static constexpr double k_driveMotorToEncoderGearRatioHigh = 1; // gear ratio from drive motor to encoder in high gear
    static constexpr double k_driveEncoderToWheelGearRatio = 1; // gear ratio from drive encoder to wheel
    static constexpr double k_steerEncoderToWheelGearRatio = 1; // gear ratio from steer encoder to wheel
    static constexpr double k_wheelSlipNoiseRatio = 1000; // wheel encoder noise ratio used to detect wheel slip

    // drive motors
    static constexpr double k_driveMotorControllerKp = 0;
    static constexpr double k_driveMotorControllerKi = 0;
    static constexpr double k_driveMotorControllerKd = 0;
    static constexpr double k_driveMotorControllerKsf = 0;
    static constexpr double k_driveMotorControllerKv = 0;
    static constexpr double k_driveMotorControllerKap = 0;
    static constexpr double k_driveMotorControllerKan = 0;

    // steer motors
    static constexpr double k_steerMotorControllerKp = 3;
    static constexpr double k_steerMotorControllerKi = 0;
    static constexpr double k_steerMotorControllerKd = 40;
    static constexpr double k_steerMotorControllerKsf = 0;
    static constexpr double k_steerMotorControllerKv = 0;
    static constexpr double k_steerMotorControllerKap = 0;
    static constexpr double k_steerMotorControllerKan = 0;

    // encoders
    static constexpr unsigned k_ctreMagEncoderTicksPerRev = 4096;
    static constexpr unsigned k_grayhillEncoderTicksPerRev = 512;

    // limelight
    static constexpr double k_limeLightHeight = 23.75;

    // line follower
    static constexpr double k_lineFollowerPulleyRadius = 1.675 / 2.0;
    static constexpr double k_lineFollowerEncoderToPulleyGearRatio = 1;
    static constexpr double k_lineFollowerMotorControllerKp = 0;
	static constexpr double k_lineFollowerMotorControllerKi = 0;
	static constexpr double k_lineFollowerMotorControllerKd = 0;
	static constexpr double k_lineFollowerMotorControllerKv = 0;
	static constexpr double k_lineFollowerMotorControllerKap = 0;
	static constexpr double k_lineFollowerMotorControllerKan = 0;
	static constexpr double k_lineFollowerMotorControllerKsf = 0;
    static constexpr double k_lineFollowerMaxVel = 6900;
    static constexpr double k_lineFollowerMaxAccel = 50000;
    static constexpr double k_lineFollowerKf = 1024.0 / 6900.0;
}

#endif // ROBOT_PARAMETERS_H
