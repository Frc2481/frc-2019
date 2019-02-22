#include "Subsystems/SwerveDrivetrain.h"
#include "RobotMap.h"
#include "RobotParameters.h"
#include "Utils/Sign.h"
#include "Utils/MathConstants.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickDrive.h"

SwerveDrivetrain::SwerveDrivetrain()
    : Subsystem("SwerveDrivetrain"),
	m_kinematics(
		Translation2D(RobotParameters::k_wheelTrack / 2.0, RobotParameters::k_wheelBase / 2.0),
		Translation2D(RobotParameters::k_wheelTrack / 2.0, -RobotParameters::k_wheelBase / 2.0),
		Translation2D(-RobotParameters::k_wheelTrack / 2.0, -RobotParameters::k_wheelBase / 2.0),
		Translation2D(-RobotParameters::k_wheelTrack / 2.0, RobotParameters::k_wheelBase / 2.0)),
    m_gyroYaw(0),
	m_isOpenLoopFieldFrame(false), 
	m_areAllSteerEncodersConnected(false) {

m_pFRDriveMotor = new VictorSPX(FR_DRIVE_MOTOR_ID);
	m_pFRDriveMotorController = new MotorVelocityController(
		m_pFRDriveMotor,
		true,
        RobotParameters::k_driveMotorControllerKp,
        RobotParameters::k_driveMotorControllerKi,
        RobotParameters::k_driveMotorControllerKd,
        RobotParameters::k_driveMotorControllerKv,
        RobotParameters::k_driveMotorControllerKap,
		RobotParameters::k_driveMotorControllerKan,
		RobotParameters::k_driveMotorControllerKsf,
        0,
		0,
        0);

	m_pBRDriveMotor = new VictorSPX(BR_DRIVE_MOTOR_ID);
	m_pBRDriveMotorController = new MotorVelocityController(
		m_pBRDriveMotor,
		true,
		RobotParameters::k_driveMotorControllerKp,
		RobotParameters::k_driveMotorControllerKi,
		RobotParameters::k_driveMotorControllerKd,
		RobotParameters::k_driveMotorControllerKv,
		RobotParameters::k_driveMotorControllerKap,
		RobotParameters::k_driveMotorControllerKan,
		RobotParameters::k_driveMotorControllerKsf,
		0,
		0,
		0);

	m_pBLDriveMotor = new VictorSPX(BL_DRIVE_MOTOR_ID);
	m_pBLDriveMotorController = new MotorVelocityController(
		m_pBLDriveMotor,
		true,
		RobotParameters::k_driveMotorControllerKp,
		RobotParameters::k_driveMotorControllerKi,
		RobotParameters::k_driveMotorControllerKd,
		RobotParameters::k_driveMotorControllerKv,
		RobotParameters::k_driveMotorControllerKap,
		RobotParameters::k_driveMotorControllerKan,
		RobotParameters::k_driveMotorControllerKsf,
		0,
		0,
		0);

	m_pFLDriveMotor = new VictorSPX(FL_DRIVE_MOTOR_ID);
	m_pFLDriveMotorController = new MotorVelocityController(
		m_pFLDriveMotor,
		true,
		RobotParameters::k_driveMotorControllerKp,
		RobotParameters::k_driveMotorControllerKi,
		RobotParameters::k_driveMotorControllerKd,
		RobotParameters::k_driveMotorControllerKv,
		RobotParameters::k_driveMotorControllerKap,
		RobotParameters::k_driveMotorControllerKan,
		RobotParameters::k_driveMotorControllerKsf,
		0,
		0,
		0);

	m_pFRSteerMotor = new TalonSRX(FR_STEER_MOTOR_ID);
	m_pFRSteerEncoder = new CTREMagEncoder(m_pFRSteerMotor, "FR_STEER_MOTOR_ENCODER");
	m_pFRSteerMotorController = new MotorPositionController(
		m_pFRSteerMotor,
		m_pFRSteerEncoder,
		true,
		RobotParameters::k_steerMotorControllerKp,
		RobotParameters::k_steerMotorControllerKi,
		RobotParameters::k_steerMotorControllerKd,
		RobotParameters::k_steerMotorControllerKv,
		RobotParameters::k_steerMotorControllerKap,
		RobotParameters::k_steerMotorControllerKan,
		RobotParameters::k_steerMotorControllerKsf,
		0,
		0,
		RobotParameters::k_ctreMagEncoderTicksPerRev * RobotParameters::k_steerEncoderToWheelGearRatio);

	m_pBRSteerMotor = new TalonSRX(BR_STEER_MOTOR_ID);
	m_pBRSteerEncoder = new CTREMagEncoder(m_pBRSteerMotor, "BR_STEER_MOTOR_ENCODER");
	m_pBRSteerMotorController = new MotorPositionController(
		m_pBRSteerMotor,
		m_pBRSteerEncoder,
		true,
		RobotParameters::k_steerMotorControllerKp,
		RobotParameters::k_steerMotorControllerKi,
		RobotParameters::k_steerMotorControllerKd,
		RobotParameters::k_steerMotorControllerKv,
		RobotParameters::k_steerMotorControllerKap,
		RobotParameters::k_steerMotorControllerKan,
		RobotParameters::k_steerMotorControllerKsf,
		0,
		0,
		RobotParameters::k_ctreMagEncoderTicksPerRev * RobotParameters::k_steerEncoderToWheelGearRatio);

	m_pBLSteerMotor = new TalonSRX(BL_STEER_MOTOR_ID);
	m_pBLSteerEncoder = new CTREMagEncoder(m_pBLSteerMotor, "BL_STEER_MOTOR_ENCODER");
	m_pBLSteerMotorController = new MotorPositionController(
		m_pBLSteerMotor,
		m_pBLSteerEncoder,
		true,
		RobotParameters::k_steerMotorControllerKp,
		RobotParameters::k_steerMotorControllerKi,
		RobotParameters::k_steerMotorControllerKd,
		RobotParameters::k_steerMotorControllerKv,
		RobotParameters::k_steerMotorControllerKap,
		RobotParameters::k_steerMotorControllerKan,
		RobotParameters::k_steerMotorControllerKsf,
		0,
		0,
		RobotParameters::k_ctreMagEncoderTicksPerRev * RobotParameters::k_steerEncoderToWheelGearRatio);

	m_pFLSteerMotor = new TalonSRX(FL_STEER_MOTOR_ID);
	m_pFLSteerEncoder = new CTREMagEncoder(m_pFLSteerMotor, "FL_STEER_MOTOR_ENCODER");
	m_pFLSteerMotorController = new MotorPositionController(
		m_pFLSteerMotor,
		m_pFLSteerEncoder,
		true,
		RobotParameters::k_steerMotorControllerKp,
		RobotParameters::k_steerMotorControllerKi,
		RobotParameters::k_steerMotorControllerKd,
		RobotParameters::k_steerMotorControllerKv,
		RobotParameters::k_steerMotorControllerKap,
		RobotParameters::k_steerMotorControllerKan,
		RobotParameters::k_steerMotorControllerKsf,
		0,
		0,
		RobotParameters::k_ctreMagEncoderTicksPerRev * RobotParameters::k_steerEncoderToWheelGearRatio);

    m_pChassisIMU = new AHRS(SPI::kMXP);
}

SwerveDrivetrain::~SwerveDrivetrain() {
	delete m_pFRDriveMotor;
	m_pFRDriveMotor = nullptr;

	delete m_pBRDriveMotor;
	m_pBRDriveMotor = nullptr;

	delete m_pBLDriveMotor;
	m_pBLDriveMotor = nullptr;

	delete m_pFLDriveMotor;
	m_pFLDriveMotor = nullptr;

	delete m_pFRSteerMotor;
	m_pFRSteerMotor = nullptr;

	delete m_pBRSteerMotor;
	m_pBRSteerMotor = nullptr;

	delete m_pBLSteerMotor;
	m_pBLSteerMotor = nullptr;

	delete m_pFLSteerMotor;
	m_pFLSteerMotor = nullptr;

	delete m_pFRDriveMotorController;
	m_pFRDriveMotorController = nullptr;

	delete m_pBRDriveMotorController;
	m_pBRDriveMotorController = nullptr;

	delete m_pBLDriveMotorController;
	m_pBLDriveMotorController = nullptr;

	delete m_pFLDriveMotorController;
	m_pFLDriveMotorController = nullptr;

	delete m_pFRSteerMotorController;
	m_pFRSteerMotorController = nullptr;

	delete m_pBRSteerMotorController;
	m_pBRSteerMotorController = nullptr;

	delete m_pBLSteerMotorController;
	m_pBLSteerMotorController = nullptr;

	delete m_pFLSteerMotorController;
	m_pFLSteerMotorController = nullptr;

	delete m_pFRSteerEncoder;
	m_pFRSteerEncoder = nullptr;

	delete m_pBRSteerEncoder;
	m_pBRSteerEncoder = nullptr;

	delete m_pBLSteerEncoder;
	m_pBLSteerEncoder = nullptr;

	delete m_pFLSteerEncoder;
	m_pFLSteerEncoder = nullptr;

	delete m_pChassisIMU;
	m_pChassisIMU = nullptr;
}

void SwerveDrivetrain::InitDefaultCommand() {
	SetDefaultCommand(new SwerveDrivetrainJoystickDrive());
}

void SwerveDrivetrain::Periodic() {
	// update encoders
	m_pFRSteerEncoder->update();
	m_pBRSteerEncoder->update();
	m_pBLSteerEncoder->update();
	m_pFLSteerEncoder->update();

	if(frc::DriverStation::GetInstance().IsDisabled()) {
		SmartDashboard::PutBoolean("FL steer encoder connected", m_pFLSteerEncoder->isConnected());
		SmartDashboard::PutBoolean("FR steer encoder connected", m_pFRSteerEncoder->isConnected());
		SmartDashboard::PutBoolean("BL steer encoder connected", m_pBLSteerEncoder->isConnected());
		SmartDashboard::PutBoolean("BR steer encoder connected", m_pBRSteerEncoder->isConnected());
		m_areAllSteerEncodersConnected = m_pFLSteerEncoder->isConnected() && m_pFRSteerEncoder->isConnected()
			 && m_pBLSteerEncoder->isConnected() && m_pBRSteerEncoder->isConnected();
	}
}

void SwerveDrivetrain::driveOpenLoopControl(
	double percentVelX,
	double percentVelY,
	double percentYawRate) {

	// format yaw rate for inverse kinematics
	Translation2D percentVel = Translation2D(percentVelX, percentVelY);
	percentYawRate *= (1.0 / pow(pow(RobotParameters::k_wheelTrack / 2.0, 2) + pow(RobotParameters::k_wheelBase / 2.0, 2), 0.5)) * 180.0 / MATH_CONSTANTS_PI;
	
	// limit open loop steer for controllability
	percentYawRate *= RobotParameters::k_openLoopSteerLimitPercent;

	// field reference frame driving
	if(m_isOpenLoopFieldFrame) {
		Rotation2D gyroYaw = Rotation2D::fromDegrees(m_gyroYaw);
		percentVel = percentVel.rotateBy(gyroYaw.inverse());
	}

	Translation2D frWheelPercent;
	Translation2D brWheelPercent;
	Translation2D blWheelPercent;
	Translation2D flWheelPercent;
	m_kinematics.inverseKinematics(
		percentVel,
		percentYawRate,
		frWheelPercent,
		brWheelPercent,
		blWheelPercent,
		flWheelPercent);

	// limit wheel percent
	double maxWheelSpeed = std::max(frWheelPercent.norm(), std::max(brWheelPercent.norm(), std::max(blWheelPercent.norm(), flWheelPercent.norm())));
	if(maxWheelSpeed > 1) {
		frWheelPercent.scaleBy(1.0 / maxWheelSpeed);
		brWheelPercent.scaleBy(1.0 / maxWheelSpeed);
		blWheelPercent.scaleBy(1.0 / maxWheelSpeed);
		flWheelPercent.scaleBy(1.0 / maxWheelSpeed);
	}

	// steer optimization
	Rotation2D steerError;
	int frInvertDrive = 1;
	Rotation2D frWheelYaw = Rotation2D(frWheelPercent.getX(), frWheelPercent.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	steerError = frWheelYaw - Rotation2D::fromDegrees(m_pFRSteerEncoder->getAngle());
	if((steerError.getDegrees() > 90) || (steerError.getDegrees() < -90)) {
		frWheelYaw = frWheelYaw.rotateBy(Rotation2D::fromDegrees(180));
		frInvertDrive = -1;
	}

	int brInvertDrive = 1;
	Rotation2D brWheelYaw = Rotation2D(brWheelPercent.getX(), brWheelPercent.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	steerError = brWheelYaw - Rotation2D::fromDegrees(m_pBRSteerEncoder->getAngle());
	if((steerError.getDegrees() > 90) || (steerError.getDegrees() < -90)) {
		brWheelYaw = brWheelYaw.rotateBy(Rotation2D::fromDegrees(180));
		brInvertDrive = -1;
	}

	int blInvertDrive = 1;
	Rotation2D blWheelYaw = Rotation2D(blWheelPercent.getX(), blWheelPercent.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	steerError = blWheelYaw - Rotation2D::fromDegrees(m_pBLSteerEncoder->getAngle());
	if((steerError.getDegrees() > 90) || (steerError.getDegrees() < -90)) {
		blWheelYaw = blWheelYaw.rotateBy(Rotation2D::fromDegrees(180));
		blInvertDrive = -1;
	}

	int flInvertDrive = 1;
	Rotation2D flWheelYaw = Rotation2D(flWheelPercent.getX(), flWheelPercent.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	steerError = flWheelYaw - Rotation2D::fromDegrees(m_pFLSteerEncoder->getAngle());
	if((steerError.getDegrees() > 90) || (steerError.getDegrees() < -90)) {
		flWheelYaw = flWheelYaw.rotateBy(Rotation2D::fromDegrees(180));
		flInvertDrive = -1;
	}

	// update steer motors
	m_pFRSteerMotorController->updateAngular(frWheelYaw.getDegrees(), 0, 0);
	m_pBRSteerMotorController->updateAngular(brWheelYaw.getDegrees(), 0, 0);
	m_pBLSteerMotorController->updateAngular(blWheelYaw.getDegrees(), 0, 0);
	m_pFLSteerMotorController->updateAngular(flWheelYaw.getDegrees(), 0, 0);

	// update drive motors
	m_pFRDriveMotorController->updateOpenLoopControl(frInvertDrive * frWheelPercent.norm());
	m_pBRDriveMotorController->updateOpenLoopControl(brInvertDrive * brWheelPercent.norm());
	m_pBLDriveMotorController->updateOpenLoopControl(blInvertDrive * blWheelPercent.norm());
	m_pFLDriveMotorController->updateOpenLoopControl(flInvertDrive * flWheelPercent.norm());
}

void SwerveDrivetrain::driveClosedLoopControl(
	double robotVelX,
	double robotVelY,
	double robotAccelX,
	double robotAccelY,
	double robotYawRate,
	double robotYawAccel) {

    // convert robot vel to wheel vel
	Translation2D frWheelVel;
	Translation2D brWheelVel;
	Translation2D blWheelVel;
	Translation2D flWheelVel;
	m_kinematics.inverseKinematics(
		Translation2D(robotVelX, robotVelY),
		robotYawRate,
		frWheelVel,
		brWheelVel,
		blWheelVel,
		flWheelVel);

	// limit wheel vel
	double maxWheelSpeed = std::max(frWheelVel.norm(), std::max(brWheelVel.norm(), std::max(blWheelVel.norm(), flWheelVel.norm())));
	if(maxWheelSpeed > RobotParameters::k_maxSpeed) {
		frWheelVel.scaleBy(RobotParameters::k_maxSpeed / maxWheelSpeed);
		brWheelVel.scaleBy(RobotParameters::k_maxSpeed / maxWheelSpeed);
		blWheelVel.scaleBy(RobotParameters::k_maxSpeed / maxWheelSpeed);
		flWheelVel.scaleBy(RobotParameters::k_maxSpeed / maxWheelSpeed);
	}

    // convert robot accel to wheel accel
	Translation2D frWheelAccel;
	Translation2D brWheelAccel;
	Translation2D blWheelAccel;
	Translation2D flWheelAccel;
	m_kinematics.inverseKinematics(
		Translation2D(robotAccelX, robotAccelY),
		robotYawAccel,
		frWheelAccel,
		brWheelAccel,
		blWheelAccel,
		flWheelAccel);

	// limit wheel accel
	double maxWheelAccel = std::max(frWheelAccel.norm(), std::max(brWheelAccel.norm(), std::max(blWheelAccel.norm(), flWheelAccel.norm())));
	if(maxWheelAccel > RobotParameters::k_maxAccel) {
		frWheelAccel.scaleBy(RobotParameters::k_maxAccel / maxWheelAccel);
		brWheelAccel.scaleBy(RobotParameters::k_maxAccel / maxWheelAccel);
		blWheelAccel.scaleBy(RobotParameters::k_maxAccel / maxWheelAccel);
		flWheelAccel.scaleBy(RobotParameters::k_maxAccel / maxWheelAccel);
	}

    // update steer motors
	Rotation2D frWheelYaw = Rotation2D(frWheelVel.getX(), frWheelVel.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	Rotation2D brWheelYaw = Rotation2D(brWheelVel.getX(), brWheelVel.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	Rotation2D blWheelYaw = Rotation2D(blWheelVel.getX(), blWheelVel.getY()).rotateBy(Rotation2D::fromDegrees(-90));
	Rotation2D flWheelYaw = Rotation2D(flWheelVel.getX(), flWheelVel.getY()).rotateBy(Rotation2D::fromDegrees(-90));

	m_pFRSteerMotorController->updateAngular(frWheelYaw.getDegrees(), 0, 0);
	m_pBRSteerMotorController->updateAngular(brWheelYaw.getDegrees(), 0, 0);
	m_pBLSteerMotorController->updateAngular(blWheelYaw.getDegrees(), 0, 0);
	m_pFLSteerMotorController->updateAngular(flWheelYaw.getDegrees(), 0, 0);

    // convert wheel vel from translational to rotational
    double frWheelAngVel = frWheelVel.rotateBy(frWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double brWheelAngVel = brWheelVel.rotateBy(brWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double blWheelAngVel = blWheelVel.rotateBy(blWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double flWheelAngVel = flWheelVel.rotateBy(flWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double frWheelAngAccel = frWheelAccel.rotateBy(frWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double brWheelAngAccel = brWheelAccel.rotateBy(brWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double blWheelAngAccel = blWheelAccel.rotateBy(blWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
    double flWheelAngAccel = flWheelAccel.rotateBy(flWheelYaw.inverse()).getY() / RobotParameters::k_wheelRad * 180.0 / MATH_CONSTANTS_PI;
}

void SwerveDrivetrain::stop() {
	driveOpenLoopControl(0, 0, 0);
}

void SwerveDrivetrain::zeroSteerEncoders() {
	m_pFRSteerEncoder->zero();
	m_pBRSteerEncoder->zero();
	m_pBLSteerEncoder->zero();
	m_pFLSteerEncoder->zero();
}

void SwerveDrivetrain::zeroGyroYaw() {
	m_pChassisIMU->ZeroYaw();
}

void SwerveDrivetrain::setIsOpenLoopFieldFrame(bool isOpenLoopFieldFrame) {
	// zero gyro yaw if changed state
	if(m_isOpenLoopFieldFrame != isOpenLoopFieldFrame) {
		zeroGyroYaw();
	}
	
	m_isOpenLoopFieldFrame = isOpenLoopFieldFrame;
}

bool SwerveDrivetrain::areAllSteerEncodersConnected() {
	return m_areAllSteerEncodersConnected;
}
