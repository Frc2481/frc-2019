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
  m_elevatorSlideA = new frc::Solenoid(ELEVATOR_SLIDE_SOLENOID_A);
  m_elevatorSlideB = new frc::Solenoid(ELEVATOR_SLIDE_SOLENOID_B);

  m_elevatorEncoder = new CTREMagEncoder(m_masterElevator, "ELEVATOR_ENCODER");

// up gains
  m_masterElevator->Config_kF(0, 0, 0); //TODO
  m_masterElevator->Config_kP(0, 0, 0);
  m_masterElevator->Config_kP(0, 0, 0);
  m_masterElevator->Config_kP(0, 0, 0);

// down gains
  m_masterElevator->Config_kF(1, 0, 0);
  m_masterElevator->Config_kP(1, 0, 0);
  m_masterElevator->Config_kP(1, 0, 0);
  m_masterElevator->Config_kP(1, 0, 0);

  m_slaveElevator->Set(ControlMode::Follower, MASTER_ELEVATOR);
  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  
  m_masterElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0); //change if needed
  m_masterElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

  m_masterElevator->ConfigMotionCruiseVelocity(0, 0); //TODO: change
  m_masterElevator->ConfigMotionAcceleration(0, 0); //TODO: change

  m_masterElevator->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);

  m_masterElevator->ConfigPeakCurrentDuration(0, 0); //TODO:
  m_masterElevator->ConfigContinuousCurrentLimit(30, 0); //TODO:
  m_masterElevator->EnableCurrentLimit(false);
  m_masterElevator->ConfigPeakCurrentLimit(0, 0); //TODO
  m_masterElevator->ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, 0, 0);

  m_masterElevator->ConfigForwardSoftLimitThreshold(0, 0); //TODO: change soft limit
  m_masterElevator->ConfigForwardSoftLimitEnable(true);
  m_masterElevator->ConfigReverseSoftLimitThreshold(0, 0);
  m_masterElevator->ConfigReverseSoftLimitEnable(true);

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
  m_masterElevator->Set(ControlMode::PercentOutput, ConvertInchesToTicks(setPos));
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
    m_elevatorSlideA->Set(true);
    m_elevatorSlideB->Set(true);
  }
  else if(pos == MID){
    m_elevatorSlideA->Set(true);
    m_elevatorSlideB->Set(false);
  }
  else{
    m_elevatorSlideA->Set(false);
    m_elevatorSlideB->Set(false);
  }
}

Elevator::elevator_slide_position Elevator::GetElevatorSlidePosition(){
  return m_slidePos;
}

bool Elevator::IsElevatorEncoderConnected() {
  return m_encoderConnected;
}