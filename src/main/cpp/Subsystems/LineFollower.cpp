#include "Subsystems/LineFollower.h"
#include <math.h>
#include "Utils/MathConstants.h"
#include "Utils/Sign.h"
#include "RobotMap.h"
#include "RobotParameters.h"

LineFollower::LineFollower()
    : Subsystem("LineFollower"),
    m_targetPos(0),
    m_targetVel(0),
    m_targetValid(false) {
    
    m_pLimeLightTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    m_pLineFollowerMotor = new TalonSRX(LINE_FOLLOWER_MOTOR_ID);
	m_pLineFollowerEncoder = new CTREMagEncoder(m_pLineFollowerMotor, "LINE_FOLLOWER_MOTOR_ENCODER");
	m_pLineFollowerMotorController = new MotorPositionController(
		m_pLineFollowerMotor,
		m_pLineFollowerEncoder,
		false,
		RobotParameters::k_lineFollowerMotorControllerKp,
		RobotParameters::k_lineFollowerMotorControllerKi,
		RobotParameters::k_lineFollowerMotorControllerKd,
		RobotParameters::k_lineFollowerMotorControllerKv,
		RobotParameters::k_lineFollowerMotorControllerKap,
		RobotParameters::k_lineFollowerMotorControllerKan,
		RobotParameters::k_lineFollowerMotorControllerKsf,
		0,
		0,
		RobotParameters::k_ctreMagEncoderTicksPerRev * RobotParameters::k_lineFollowerEncoderToPulleyGearRatio);

    m_pLineFollowerMotorController->setMotionMagicLinear(
        true,
        RobotParameters::k_lineFollowerMaxVel,
        RobotParameters::k_lineFollowerMaxAccel,
        RobotParameters::k_lineFollowerKf,
        RobotParameters::k_lineFollowerPulleyRadius);
}

LineFollower::~LineFollower() { 
}

void LineFollower::InitDefaultCommand() {
}

void LineFollower::Periodic() {
    updateTargetPose();
}

double LineFollower::getTargetPos() {
    return m_targetPos;
}

double LineFollower::getTargetVel() {
    return m_targetVel;
}

void LineFollower::updateTargetPose() {
    bool oldTargetValid = m_targetValid;
    m_targetValid = m_pLimeLightTable->GetNumber("tv", false);
    
    if(m_targetValid) {
        double targetYaw = m_pLimeLightTable->GetNumber("tx", 0) * MATH_CONSTANTS_PI / 180.0;
        double targetPosOld = m_targetPos;
        m_targetPos = RobotParameters::k_limeLightHeight * tan(targetYaw);

        if(!oldTargetValid) {
            targetPosOld = RobotParameters::k_limeLightHeight * tan(Sign::Sign(targetYaw) * LIMELIGHT_FOV_YAW / 2.0 * MATH_CONSTANTS_PI / 180.0);
        }

        m_targetVel = (m_targetPos - targetPosOld) * RobotParameters::k_updateRate;
    }
    else {
        m_targetPos = 0;
        m_targetVel = 0;
    }

    frc::SmartDashboard::PutNumber("targetPos", m_targetPos);
    frc::SmartDashboard::PutNumber("targetVel", m_targetVel);
}

void LineFollower::zeroEncoder() {
    m_pLineFollowerEncoder->zero();
}

void LineFollower::updateMotorController() {
    m_pLineFollowerMotorController->updateLinear(m_targetPos, 0, 0, RobotParameters::k_lineFollowerPulleyRadius);
}
