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

  m_slaveElevator->Set(ControlMode::Follower, MASTER_ELEVATOR);
  m_masterElevator->Set(ControlMode::MotionMagic, 0);
  
  m_masterElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0); //change if needed
  m_masterElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

 // m_masterElevator->Config_kP();
  // m_masterElevator->Config_kI();
  // m_masterElevator->Config_kD();
  // m_masterElevator->Config_kF();

  m_isElevatorZeroed = false;
}

void Elevator::InitDefaultCommand() {}

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
