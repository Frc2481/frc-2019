#include "Subsystems/CargoIntakeElevator.h"
#include "RobotMap.h"
#include "RobotParameters.h"

CargoIntakeElevator::CargoIntakeElevator()
    : Subsystem("CargoIntakeElevator"),
    m_cargoIntakeSlideMinGuard(0.1),
    m_cargoIntakeSlideMaxGuard(15.3),
    m_elevatorMinGuard(0),
    m_elevatorMaxGuard(22),
    m_cargoIntakeSlideOnTargetThresh(1),
    m_elevatorOnTargetThresh(1),
    m_isCargoIntakeSlideZeroed(false),
    m_isElevatorZeroed(false),
    m_cargoIntakeSlideRefP(0),
    m_elevatorRefP(0),
    m_isCargoBeamBreakTriggered(false),
    m_cargoIntakeSlidePulleyRad(0.564),
    m_elevatorPulleyRad(0.752 * 2) { // cascading elevator
    
    m_pCargoIntakeSlideMotor = new TalonSRX(CARGO_INTAKE_EXTEND_MOTOR_ID);
    m_pCargoIntakeSlideMotor->ConfigFactoryDefault();
    m_pCargoIntakeSlideEncoder = new CTREMagEncoder(m_pCargoIntakeSlideMotor, "CARGO_INTAKE_SLIDE_ENCODER");
    // m_pCargoIntakeSlideMotor->ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, 0, 10);
    
    m_pCargoIntakeSlideMotorController = new MotorPositionController(
        m_pCargoIntakeSlideMotor,
        m_pCargoIntakeSlideEncoder,
        true,
        true,
        0.5,
        0.05,
        1,
        0,
        0,
        0,
        0.22,
        3,
        1,
        RobotParameters::k_ctreMagEncoderTicksPerRev * 28 / 22);
    
    m_pCargoIntakeSlideMotor->ConfigReverseSoftLimitThreshold(0, 10);
    m_pCargoIntakeSlideMotor->ConfigReverseSoftLimitEnable(true, 10);
    m_pCargoIntakeSlideMotor->ConfigForwardSoftLimitThreshold(17700, 10);
    m_pCargoIntakeSlideMotor->ConfigForwardSoftLimitEnable(true, 10);
    m_pCargoIntakeSlideMotor->ConfigForwardLimitSwitchSource(LimitSwitchSource::LimitSwitchSource_FeedbackConnector, LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 10);
    // m_pCargoIntakeSlideMotor->SetClearPositionOnLimitR(true);
    m_pCargoIntakeSlideMotor->SetNeutralMode(Coast);
    
    m_pElevatorMasterMotor = new TalonSRX(MASTER_ELEVATOR_MOTOR_ID);
    m_pElevatorMasterMotor->ConfigFactoryDefault();
    m_pElevatorSlaveMotor = new TalonSRX(SLAVE_ELEVATOR_MOTOR_ID);
    m_pElevatorSlaveMotor->Follow(*m_pElevatorMasterMotor);
    m_pElevatorEncoder = new CTREMagEncoder(m_pElevatorMasterMotor, "ELEVATOR_ENCODER");
    
    m_pElevatorMotorController = new MotorPositionController(
        m_pElevatorMasterMotor,
        m_pElevatorEncoder,
        true,
        false,
        0.5,
        0.05,
        0,
        0,
        1,
        1,
        0,
        0, // 3
        0, // 1
        RobotParameters::k_ctreMagEncoderTicksPerRev);
    
    m_pElevatorMasterMotor->ConfigReverseSoftLimitThreshold(0, 10);
    m_pElevatorMasterMotor->ConfigReverseSoftLimitEnable(true, 10);
    m_pElevatorMasterMotor->ConfigForwardSoftLimitThreshold(29100, 10);
    m_pElevatorMasterMotor->ConfigForwardSoftLimitEnable(true, 10);
    m_pElevatorSlaveMotor->SetInverted(true);
    
    m_pCargoIntakeMotor = new VictorSPX(CARGO_INTAKE_MOTOR_ID);
    m_pCargoIntakeBeamBreak = new frc::DigitalInput(CARGO_PRE_INTAKE_BALL_SENSOR);

    m_pCargoIntakeSlideMotorController->setMotionMagicLinear(
        true,
        4000,
        20000,
        0.3,
        5,
        m_cargoIntakeSlidePulleyRad);
    
    m_pElevatorMotorController->setMotionMagicLinear(
        true,
        2400,
        4800,
        0.42,
        5,
        m_elevatorPulleyRad);
    
    // stop subsystem
    StopCargoIntakeSlide();
    StopElevator();
    StopCargoIntake();
}

CargoIntakeElevator::~CargoIntakeElevator() {
}

void CargoIntakeElevator::InitDefaultCommand() {
	// SetDefaultCommand(new DefaultCommandName());
}

void CargoIntakeElevator::Periodic() {
    m_pCargoIntakeSlideEncoder->update();
    m_pElevatorEncoder->update();
    
    CheckIsCargoBeamBreakTriggered();
    CheckCargoIntakeSlideZeroed();
    CheckElevatorZeroed();
    
    frc::SmartDashboard::PutNumber("CargoIntakeSlidePosition", GetCargoIntakeSlidePosition());
    frc::SmartDashboard::PutNumber("ElevatorPosition", GetElevatorPosition());
    
    frc::SmartDashboard::PutBoolean("IsCargoBeamBreakTriggered", IsCargoBeamBreakTriggered());
    
    frc::SmartDashboard::PutBoolean("IsCargoIntakeInSlideProtectedZone", IsCargoIntakeSlideInProtectedZone());
    frc::SmartDashboard::PutBoolean("IsElevatorInProtectedZone", IsElevatorInProtectedZone());
    
    frc::SmartDashboard::PutNumber("CargoIntakeRefSlidePosition", GetCargoIntakeSlideRefPosition());
    frc::SmartDashboard::PutNumber("ElevatorRefPosition", GetElevatorRefPosition());
    
    frc::SmartDashboard::PutBoolean("IsCargoIntakeSlideZeroed", IsCargoIntakeSlideZeroed());
    frc::SmartDashboard::PutBoolean("IsElevatorZeroed", IsElevatorZeroed());
    
    frc::SmartDashboard::PutBoolean("IsCargoIntakeSlideConnected", IsCargoIntakeSlideConnected());
    frc::SmartDashboard::PutBoolean("IsElevatorConnected", IsElevatorConnected());
}

double CargoIntakeElevator::GetCargoIntakeSlidePosition() {
    return m_pCargoIntakeSlideEncoder->getWheelDistance(m_cargoIntakeSlidePulleyRad, 1);
}

double CargoIntakeElevator::GetElevatorPosition() {
    return m_pElevatorEncoder->getWheelDistance(m_elevatorPulleyRad, 1);
}

void CargoIntakeElevator::CheckIsCargoBeamBreakTriggered() {
    m_isCargoBeamBreakTriggered = !m_pCargoIntakeBeamBreak->Get();
}

bool CargoIntakeElevator::IsCargoBeamBreakTriggered() {
    return m_isCargoBeamBreakTriggered;
}

void CargoIntakeElevator::MoveCargoIntakeSlideToPosition(CargoIntakeSlidePositions refP) {
    m_cargoIntakeSlideRefP = refP / 10.0;
    
    if(!IsElevatorInProtectedZone()) {
        if(refP > GetCargoIntakeSlidePosition()) {
            m_pCargoIntakeSlideMotorController->updateLinear(refP, 0, 0, m_cargoIntakeSlidePulleyRad);
        }
        else {
            m_pCargoIntakeSlideMotorController->updateLinear(refP, 0, 0, m_cargoIntakeSlidePulleyRad);
        }
    }
}

void CargoIntakeElevator::MoveElevatorToPosition(ElevatorPositions refP) {
    m_elevatorRefP = refP / 10.0;
    
    if(!IsCargoIntakeSlideInProtectedZone()) {
        m_pElevatorMotorController->updateLinear(refP, 0, 0, m_elevatorPulleyRad);
    }
    else if(!IsCargoIntakeSlideInProtectedZone() && ((refP == ElevatorPositions::HIGH_HATCH) || (refP == ElevatorPositions::HIGH_CARGO))) {
        refP = ElevatorPositions::MID_HATCH;
        m_elevatorRefP = refP;
        m_pElevatorMotorController->updateLinear(refP, 0, 0, m_elevatorPulleyRad); // TODO: check this math with a printf before arbitrary feedforward is set
    }
}

double CargoIntakeElevator::GetCargoIntakeSlideRefPosition() {
    return m_cargoIntakeSlideRefP;
}

double CargoIntakeElevator::GetElevatorRefPosition() {
    return m_elevatorRefP;
}

bool CargoIntakeElevator::IsCargoIntakeSlideInProtectedZone() {
    return (m_elevatorMinGuard < GetCargoIntakeSlidePosition()) && (GetCargoIntakeSlidePosition() < m_elevatorMaxGuard);
}

bool CargoIntakeElevator::IsElevatorInProtectedZone() {
    return (m_cargoIntakeSlideMinGuard < GetElevatorPosition()) && (GetElevatorPosition() < m_cargoIntakeSlideMaxGuard);
}

bool CargoIntakeElevator::IsCargoIntakeSlideOnTarget() {
    return fabs(GetCargoIntakeSlideRefPosition() - GetCargoIntakeSlidePosition()) < m_cargoIntakeSlideOnTargetThresh;
}

bool CargoIntakeElevator::IsElevatorOnTarget() {
    return fabs(GetElevatorRefPosition() - GetElevatorPosition()) < m_elevatorOnTargetThresh;
}

void CargoIntakeElevator::ZeroCargoIntakeSlide() {
    m_pCargoIntakeSlideEncoder->zero();
    m_isCargoIntakeSlideZeroed = true;
}

void CargoIntakeElevator::ZeroElevator() {
    m_pElevatorEncoder->zero();
    m_isElevatorZeroed = true;
}

void CargoIntakeElevator::CheckCargoIntakeSlideZeroed() {
    m_pCargoIntakeSlideMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
    
    if(m_pCargoIntakeSlideMotor->HasResetOccurred() && m_isCargoIntakeSlideZeroed) {
        m_isCargoIntakeSlideZeroed = false;
        StopCargoIntakeSlide();
    }
}

void CargoIntakeElevator::CheckElevatorZeroed() {
    if(m_pElevatorMasterMotor->HasResetOccurred() && m_isElevatorZeroed) {
        m_isElevatorZeroed = false;
        StopElevator();
    }
}

bool CargoIntakeElevator::IsCargoIntakeSlideZeroed() {
    return m_isCargoIntakeSlideZeroed;
}

bool CargoIntakeElevator::IsElevatorZeroed() {
    return m_isElevatorZeroed;
}

bool CargoIntakeElevator::IsCargoIntakeSlideConnected() {
    return m_pCargoIntakeSlideEncoder->isConnected();
}

bool CargoIntakeElevator::IsElevatorConnected() {
    return m_pElevatorEncoder->isConnected();
}

void CargoIntakeElevator::SetCargoIntakePercent(double percent) {
    m_pCargoIntakeMotor->Set(ControlMode::PercentOutput, percent);
}

void CargoIntakeElevator::StopCargoIntakeSlide() {
    m_pCargoIntakeSlideMotor->Set(ControlMode::PercentOutput, 0);
}

void CargoIntakeElevator::StopElevator() {
    m_pElevatorMasterMotor->Set(ControlMode::PercentOutput, 0);
}

void CargoIntakeElevator::StopCargoIntake() {
    m_pCargoIntakeMotor->Set(ControlMode::PercentOutput, 0);
}
