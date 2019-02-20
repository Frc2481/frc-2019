#ifndef ROBOT_PARAMETERS_H
#define ROBOT_PARAMETERS_H

namespace RobotParameters {
    // robot main
	static constexpr unsigned k_updateRate = 50; // Hz

    // drivetrain
    static constexpr double k_wheelTrack = 26.3; // in
    static constexpr double k_wheelBase = 23.2; // in
    static constexpr double k_wheelRad = 1.5; // in
    static constexpr double k_maxSpeed = 1; // in/s
    static constexpr double k_maxAccel = 1; // in/s^2
    static constexpr double k_maxDeccel = -1; // in/s^2
    static constexpr double k_steerEncoderToWheelGearRatio = 1; // gear ratio from steer encoder to wheel

    // drive motors
    static constexpr double k_driveMotorControllerKp = 0;
    static constexpr double k_driveMotorControllerKi = 0;
    static constexpr double k_driveMotorControllerKd = 0;
    static constexpr double k_driveMotorControllerKsf = 0;
    static constexpr double k_driveMotorControllerKv = 0;
    static constexpr double k_driveMotorControllerKap = 0;
    static constexpr double k_driveMotorControllerKan = 0;

    // // steer motors
    static constexpr double k_steerMotorControllerKp = 3;
    static constexpr double k_steerMotorControllerKi = 0;
    static constexpr double k_steerMotorControllerKd = 40;
    static constexpr double k_steerMotorControllerKsf = 0;
    static constexpr double k_steerMotorControllerKv = 0;
    static constexpr double k_steerMotorControllerKap = 0;
    static constexpr double k_steerMotorControllerKan = 0;

    static constexpr double k_openLoopSteerLimitPercent = 0.5;

    // path follower
    static constexpr double k_pathFollowerTimeoutAllowance = 0.5; // timeout path if takes longer than total path time plus this allowance (s)
    static constexpr double k_pathFollowerLatDistKp = 0;
    static constexpr double k_pathFollowerLatDistKi = 0;
    static constexpr double k_pathFollowerLatDistKd = 0;
    static constexpr double k_pathFollowerYawRateKp = 0;
    static constexpr double k_pathFollowerYawRateKi = 0;
    static constexpr double k_pathFollowerYawRateKd = 0;

    // rotate to angle
    static constexpr double k_rotateToAngleTimeoutAllowance = 0.5; // timeout path if takes longer than total path time plus this allowance (s)
    static constexpr double k_rotateToAngleMaxYawRate = 350;
    static constexpr double k_rotateToAngleMaxYawAccel = 100;
    static constexpr double k_rotateToAngleMaxYawDeccel = -100;
    static constexpr double k_rotateToAngleTargetZone = 5;

    // encoders
    static constexpr unsigned k_ctreMagEncoderTicksPerRev = 4096;
    static constexpr unsigned k_grayhillEncoderTicksPerRev = 512;

    // limelight
    static constexpr double k_limeLightHeight = 23.75;
    static constexpr double k_lineFinderKf = 0;
    static constexpr double k_lineFinderKp = 0;
    static constexpr double k_numVelocities = 10;

    // HatchSlide
    static constexpr double k_beltCircumference = 1.128 * 3.14; //1.625in * pi
    static constexpr double k_feedForwardHatch = 0.148;

    // Elevator
    static constexpr double k_elevatorVelocity = 0;
    static constexpr double k_elevatorAccel = 0;
    static constexpr double k_elevatorTicksPerRev = 4096;
    static constexpr double k_elevatorBeltCircumference = 1.504 * 3.14;
    static constexpr double k_elevatorCollisionMin = 0;
    static constexpr double k_elevatorCollisionMax = 5000;

    // CargoIntake
    static constexpr double k_cargoIntakeThreshold = 0; // point where it's no longer safe to move elevator down onto it
    static constexpr double k_cargoIntakeBeltCircumference = 1.128 * 3.14;
    static constexpr double k_cargoIntakeTicksPerRev = 4096;
    static constexpr double k_intakeSpeedFull = 1;
    static constexpr double k_intakeSpeedPartial = 0.4;

    // Climber
    static constexpr double k_climberTicksPerInch = 1;

}

#endif // ROBOT_PARAMETERS_H
