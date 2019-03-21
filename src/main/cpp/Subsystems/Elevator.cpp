/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

Elevator::Elevator() : Subsystem("Elevator") {
  m_masterElevator = new TalonSRX(MASTER_ELEVATOR_MOTOR_ID);
  m_slaveElevator = new TalonSRX(SLAVE_ELEVATOR_MOTOR_ID);
  // m_slaveElevator = new VictorSPX(SLAVE_ELEVATOR_MOTOR_ID); // make sure to change back

  m_elevatorEncoder = new CTREMagEncoder(m_masterElevator, "ELEVATOR_ENCODER");

  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_slaveElevator->Follow(*m_masterElevator);

  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  m_masterElevator->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_masterElevator->EnableCurrentLimit(false);
  m_masterElevator->SetInverted(false); //used to be true
  m_masterElevator->SetSensorPhase(true);
  m_slaveElevator->SetInverted(true); //used to be false
  talonConfig.motionCurveStrength = 5;

// up gains
  talonConfig.slot0.kF = 0.42; 
  talonConfig.slot0.kP = 0.5;
  talonConfig.slot0.kI = 0.05; //0;
  talonConfig.slot0.integralZone = 1700;
  talonConfig.slot0.maxIntegralAccumulator = 500;
  talonConfig.slot0.kD = 0;

// down gains
  talonConfig.slot1.kF = 0;
  talonConfig.slot1.kP = 0;
  talonConfig.slot1.kI = 0;
  talonConfig.slot1.kD = 0;
  
  talonConfig.forwardLimitSwitchSource = LimitSwitchSource_FeedbackConnector;
  talonConfig.reverseLimitSwitchSource = LimitSwitchSource_FeedbackConnector;

  talonConfig.forwardLimitSwitchDeviceID = 0;
  talonConfig.reverseLimitSwitchDeviceID = 0;
  talonConfig.forwardLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;

  talonConfig.motionCruiseVelocity = 2400;
  talonConfig.motionAcceleration = 4800; 

  talonConfig.peakCurrentDuration = 0; 
  talonConfig.continuousCurrentLimit = 30;
  talonConfig.peakCurrentLimit = 0;
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitThreshold = 29100;
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 0; //5200;
  talonConfig.reverseSoftLimitEnable = true;

  m_isMasterZeroed = false;

  m_masterElevator->ConfigAllSettings(talonConfig);
  m_masterElevator->SelectProfileSlot(0, 0);

  m_desiredElevatorPosition = 0;
  m_isElevatorManualEnabled = false;
  m_hasResetOccurred = m_masterElevator->HasResetOccurred();
  frc::SmartDashboard::PutBoolean("IsElevatorMasterTalonReset", true);
}

void Elevator::InitDefaultCommand() {
}

void Elevator::Periodic() {
  static int loopCounter = -1;
  loopCounter++;
  loopCounter %= 5;
  if (loopCounter == 0) {
    frc::SmartDashboard::PutBoolean("IsElevatorZeroed", m_isMasterZeroed);
    frc::SmartDashboard::PutNumber("ElevatorError", GetElevatorError());
  } 
  else if (loopCounter == 1) {
    m_encoderConnected = m_elevatorEncoder->isConnected();
    frc::SmartDashboard::PutBoolean("IsElevatorEncoderConnected", m_encoderConnected);
  } 
  else if (loopCounter == 2){
    frc::SmartDashboard::PutBoolean("IsElevatorOnTarget", IsOnTarget());
    frc::SmartDashboard::PutNumber("ElevatorPos", GetElevatorPosition());
  } 
  else if (loopCounter == 3) {
    frc::SmartDashboard::PutNumber("ElevatorDesiredPos", GetDesiredPos());
  } 
  else if (loopCounter == 4) {
    if(m_masterElevator->HasResetOccurred() && m_isMasterZeroed){
      frc::SmartDashboard::PutBoolean("IsElevatorMasterTalonReset", !m_masterElevator->HasResetOccurred());
      m_isMasterZeroed = false;
      SetOpenLoopSpeed(0);
    }
  }
}

void Elevator::SetElevatorPosition(double setPos, bool isMoving) {
  if(m_isMasterZeroed){
    if(setPos > 0) {
      m_masterElevator->Set(ControlMode::MotionMagic, ConvertInchesToTicks(setPos), DemandType::DemandType_ArbitraryFeedForward, 0.1);
      // m_masterElevator->Set(ControlMode::MotionMagic, setPos, DemandType::DemandType_ArbitraryFeedForward, 0.1);
    }
    else {
      m_masterElevator->Set(ControlMode::MotionMagic, setPos);
      // m_masterElevator->Set(ControlMode::MotionMagic, ConvertInchesToTicks(setPos));
    }
    m_desiredElevatorPosition = setPos;
  }
}

double Elevator::GetDesiredPos(){
  return m_desiredElevatorPosition;
}

double Elevator::GetVelocity(){
  return m_masterElevator->GetActiveTrajectoryVelocity();
}
bool Elevator::IsOnTarget() {
  return fabs(m_desiredElevatorPosition - GetElevatorPosition()) < 0.5; //1
}
void Elevator::ZeroElevatorEncoder() {
  for(int i = 0; i < 5; i++) {
		ErrorCode error = m_masterElevator->SetSelectedSensorPosition(0, 0, 10);
		if(error == OK) {
			break;
		}
	}
	m_isMasterZeroed = true;
  m_masterElevator->ClearStickyFaults();
  m_slaveElevator->ClearStickyFaults();
}

double Elevator::GetElevatorPosition() {
  return ConvertTicksToInches(m_masterElevator->GetSelectedSensorPosition(0));
}

double Elevator::GetElevatorError() {
  return ConvertTicksToInches(m_masterElevator->GetClosedLoopError());
}

bool Elevator::IsElevatorEncoderZeroed() {
  return m_isMasterZeroed;
}

bool Elevator::IsForwardLimitSwitchClosed() {
  return m_masterElevator->GetSensorCollection().IsFwdLimitSwitchClosed();
}
bool Elevator::IsReverseLimitSwitchClosed() {
  return m_masterElevator->GetSensorCollection().IsRevLimitSwitchClosed();
}

double Elevator::ConvertTicksToInches(int ticks) {
  return (ticks * RobotParameters::k_elevatorBeltCircumference / RobotParameters::k_elevatorTicksPerRev) * 2;
}
int Elevator::ConvertInchesToTicks(double inches) {
  return (inches * RobotParameters::k_elevatorTicksPerRev / RobotParameters::k_elevatorBeltCircumference) / 2;
}

void Elevator::SetOpenLoopSpeed(double speed) {
  m_masterElevator->Set(ControlMode::PercentOutput, speed);
}
void Elevator::SetMasterOpenLoopSpeed(double speed) {
  // m_slaveElevator->set(); //unfollow
  m_masterElevator->Set(ControlMode::PercentOutput, speed);
}
void Elevator::SetSlaveOpenLoopSpeed(double speed) {
  // m_slaveElevator->set(); //unfollow
  m_slaveElevator->Set(ControlMode::PercentOutput, speed);
}
bool Elevator::IsElevatorEncoderConnected() {
  return m_encoderConnected;
}
bool Elevator::IsPositionInProtectedZone(double pos) {
  return pos < RobotParameters::k_elevatorCollisionMax && pos > RobotParameters::k_elevatorCollisionMin;
}
void Elevator::SetFollower() {
  m_slaveElevator->Follow(*m_masterElevator);
}
void Elevator::EnableElevatorManual(){
  m_isElevatorManualEnabled = true;
}
void Elevator::DisableElevatorManual(){
  m_isElevatorManualEnabled = false;
}
bool Elevator::IsElevatorManualEnabled(){
  return m_isElevatorManualEnabled;
}
bool Elevator::IsElevatorGoingUp() {
  return GetElevatorPosition() - GetDesiredPos() < 0;
}