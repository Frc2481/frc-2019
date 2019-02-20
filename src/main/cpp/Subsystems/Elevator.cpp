/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

Elevator::Elevator() : Subsystem("Elevator") {
  m_masterElevator = new TalonSRX(MASTER_ELEVATOR_MOTOR_ID);
  m_slaveElevator = new VictorSPX(SLAVE_ELEVATOR_MOTOR_ID);

  m_elevatorEncoder = new CTREMagEncoder(m_masterElevator, "ELEVATOR_ENCODER");

  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_slaveElevator->Follow(*m_masterElevator);

  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  m_masterElevator->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_masterElevator->EnableCurrentLimit(false);
  m_masterElevator->SetInverted(true);
  m_masterElevator->SetSensorPhase(true);
  m_slaveElevator->SetInverted(false);
  talonConfig.motionCurveStrength = 5;

// up gains
  talonConfig.slot0.kF = 0.42; //TODO
  talonConfig.slot0.kP = 0.5;
  talonConfig.slot0.kI = 0;
  talonConfig.slot0.kD = 0;

// down gains
  talonConfig.slot1.kF = 0; //TODO
  talonConfig.slot1.kP = 0;
  talonConfig.slot1.kI = 0;
  talonConfig.slot1.kD = 0;
  
  talonConfig.forwardLimitSwitchSource = LimitSwitchSource_FeedbackConnector;
  talonConfig.reverseLimitSwitchSource = LimitSwitchSource_FeedbackConnector;

  talonConfig.forwardLimitSwitchDeviceID = 0;
  talonConfig.reverseLimitSwitchDeviceID = 0;
  talonConfig.forwardLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;

  talonConfig.motionCruiseVelocity = 2400; //TODO: change
  talonConfig.motionAcceleration = 4800; //TODO: change

  talonConfig.peakCurrentDuration = 0; //TODO:
  talonConfig.continuousCurrentLimit = 30; //TODO:
  talonConfig.peakCurrentLimit = 0; //TODO
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitThreshold = 27450; //TODO: change soft limit
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 5200;
  talonConfig.reverseSoftLimitEnable = true;

  m_isElevatorZeroed = false;

  m_masterElevator->ConfigAllSettings(talonConfig);
  m_masterElevator->SelectProfileSlot(0, 0);

  double m_desiredElevatorPosition = 0;
}

void Elevator::InitDefaultCommand() {
}

void Elevator::Periodic() {
  frc::SmartDashboard::PutBoolean("IsElevatorZeroed", m_isElevatorZeroed);
  frc::SmartDashboard::PutNumber("Elevator Error", GetElevatorError());
  m_encoderConnected = m_elevatorEncoder->isConnected();
  frc::SmartDashboard::PutBoolean("IsElevatorEncoderConnected", m_encoderConnected);
}

void Elevator::SetElevatorPosition(double setPos, bool isMoving) {
  if(setPos > 0) {
    // m_masterElevator->Set(ControlMode::MotionMagic, ConvertInchesToTicks(setPos), DemandType::DemandType_ArbitraryFeedForward, 0.1);
    m_masterElevator->Set(ControlMode::MotionMagic, setPos, DemandType::DemandType_ArbitraryFeedForward, 0.1);
  }
  else {
  m_masterElevator->Set(ControlMode::MotionMagic, setPos);
  // m_masterElevator->Set(ControlMode::MotionMagic, ConvertInchesToTicks(setPos));
  }
  m_desiredElevatorPosition = setPos;
}

bool Elevator::IsOnTarget() {
  return fabs(m_desiredElevatorPosition - m_masterElevator->GetSelectedSensorPosition()) < ConvertInchesToTicks(1);
}
void Elevator::ZeroElevatorEncoder() {
  m_masterElevator->SetSelectedSensorPosition(0, 0, 10);
  m_isElevatorZeroed = true;
}

double Elevator::GetElevatorPosition() {
  return ConvertTicksToInches(m_masterElevator->GetSelectedSensorPosition(0));
}

double Elevator::GetElevatorError() {
  return ConvertTicksToInches(m_masterElevator->GetClosedLoopError());
}

bool Elevator::IsElevatorEncoderZeroed() {
  return m_isElevatorZeroed;
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
bool Elevator::IsElevatorEncoderConnected() {
  return m_encoderConnected;
}
bool Elevator::IsPositionInProtectedZone(double pos) {
  return pos < RobotParameters::k_elevatorCollisionMax && pos > RobotParameters::k_elevatorCollisionMin;
}