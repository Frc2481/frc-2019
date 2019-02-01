/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

Elevator::Elevator() : Subsystem("ExampleSubsystem") {
  m_masterElevator = new TalonSRX(MASTER_ELEVATOR);
  m_slaveElevator = new TalonSRX(SLAVE_ELEVATOR);
  m_elevatorSlide = new frc::Solenoid(ELEVATOR_SLIDE_SOLENOID);

  m_slaveElevator->Set(ControlMode::Follower, MASTER_ELEVATOR);
  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  
  m_masterElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0); //change if needed
  m_masterElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

  m_masterElevator->ConfigMotionCruiseVelocity(0, 0);
  m_masterElevator->ConfigMotionAcceleration(0, 0);

  m_masterElevator->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);

  // m_masterElevator->Config_kP();
  // m_masterElevator->Config_kI();
  // m_masterElevator->Config_kD();
  // m_masterElevator->Config_kF();

  m_isElevatorZeroed = false;

  m_isSlideForward = false;
}

void Elevator::InitDefaultCommand() {}

void Elevator::Periodic() {
  frc::SmartDashboard::PutNumber("Is Elevator Zeroed", m_isElevatorZeroed);
  frc::SmartDashboard::PutNumber("Elevator Error", GetElevatorError());
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

void Elevator::SlideElevatorFront() {
  m_elevatorSlide->Set(true); //potentially reverse
  m_isSlideForward = true;
}

void Elevator::SlideElevatorBack() {
  m_elevatorSlide->Set(false); //potentially reverse
  m_isSlideForward = false;
}

bool Elevator::IsSlideFront() {
  return m_isSlideForward; //potentially reverse
}
