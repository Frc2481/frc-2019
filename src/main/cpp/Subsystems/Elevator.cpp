/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

Elevator::Elevator() : Subsystem("Elevator") {
  m_masterElevator = new TalonSRX(MASTER_ELEVATOR);
  m_slaveElevator = new TalonSRX(SLAVE_ELEVATOR);
  m_elevatorSlideA = new frc::DoubleSolenoid(ELEVATOR_SLIDE_SOLENOID_A1, ELEVATOR_SLIDE_SOLENOID_A2);
  m_elevatorSlideB = new frc::DoubleSolenoid(ELEVATOR_SLIDE_SOLENOID_B1, ELEVATOR_SLIDE_SOLENOID_B2);

  m_elevatorEncoder = new CTREMagEncoder(m_masterElevator, "ELEVATOR_ENCODER");

  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

// up gains
  talonConfig.slot0.kF = 0; //TODO
  talonConfig.slot0.kP = 0;
  talonConfig.slot0.kI = 0;
  talonConfig.slot0.kD = 0;

// down gains
  talonConfig.slot1.kF = 0; //TODO
  talonConfig.slot1.kP = 0;
  talonConfig.slot1.kI = 0;
  talonConfig.slot1.kD = 0;

  m_slaveElevator->Set(ControlMode::Follower, MASTER_ELEVATOR);
  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  
  talonConfig.forwardLimitSwitchSource = LimitSwitchSource_FeedbackConnector;
  talonConfig.reverseLimitSwitchSource = LimitSwitchSource_FeedbackConnector;

  talonConfig.forwardLimitSwitchDeviceID = 0;
  talonConfig.reverseLimitSwitchDeviceID = 0;
  talonConfig.forwardLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;

  talonConfig.motionCruiseVelocity = 0; //TODO: change
  talonConfig.motionAcceleration = 0; //TODO: change

  m_masterElevator->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);

  talonConfig.peakCurrentDuration = 0; //TODO:
  talonConfig.continuousCurrentLimit = 30; //TODO:
  m_masterElevator->EnableCurrentLimit(false);
  talonConfig.peakCurrentLimit = 0; //TODO
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitThreshold = 0; //TODO: change soft limit
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 0;
  talonConfig.reverseSoftLimitEnable = true;

  m_masterElevator->GetAllConfigs(talonConfig);
  m_slaveElevator->GetAllConfigs(talonConfig);

  m_isElevatorZeroed = false;
  m_isSlideForward = false;
}

void Elevator::InitDefaultCommand() {}

void Elevator::Periodic() {
  frc::SmartDashboard::PutBoolean("IsElevatorZeroed", m_isElevatorZeroed);
  frc::SmartDashboard::PutNumber("Elevator Error", GetElevatorError());
  m_encoderConnected = m_elevatorEncoder->isConnected();
  frc::SmartDashboard::PutBoolean("IsElevatorEncoderConnected", m_encoderConnected);
}

void Elevator::SetElevatorPosition(double setPos) {
  m_masterElevator->Set(ControlMode::MotionMagic, ConvertInchesToTicks(setPos));
  m_desiredElevatorPosition = setPos;
}
void Elevator::ZeroElevatorEncoder() {
  m_masterElevator->SetSelectedSensorPosition(0, 0, 10);
  m_isElevatorZeroed = true;
}

double Elevator::GetElevatorPosition() {
  return ConvertTicksToInches(m_masterElevator->GetSelectedSensorPosition(0));
}

double Elevator::GetElevatorError() {
  return m_masterElevator->GetLastError();
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
  return ticks / RobotParameters::k_elevatorTicksPerInch;
}
int Elevator::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_elevatorTicksPerInch;
}

void Elevator::SetOpenLoopSpeed(double speed) {
  m_masterElevator->Set(ControlMode::PercentOutput, speed);
}

void Elevator::SetElevatorSlidePosition(elevator_slide_position pos){
  if(pos == FRONT){
    m_elevatorSlideA->Set(frc::DoubleSolenoid::kForward);
    m_elevatorSlideB->Set(frc::DoubleSolenoid::kForward);
  }
  else if(pos == MID){
    m_elevatorSlideA->Set(frc::DoubleSolenoid::kForward);
    m_elevatorSlideB->Set(frc::DoubleSolenoid::kReverse);
  }
  else{
    m_elevatorSlideA->Set(frc::DoubleSolenoid::kReverse);
    m_elevatorSlideB->Set(frc::DoubleSolenoid::kReverse);
  }
}

Elevator::elevator_slide_position Elevator::GetElevatorSlidePosition(){
  return m_slidePos;
}

bool Elevator::IsElevatorEncoderConnected() {
  return m_encoderConnected;
}