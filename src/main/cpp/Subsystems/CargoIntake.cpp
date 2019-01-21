/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/CargoIntake.h"
#include "RobotMap.h"

CargoIntake::CargoIntake() : Subsystem("CargoIntake") {
  m_intakeMotor = new TalonSRX(CARGO_INTAKE_MOTOR);
  m_extendSolenoid = new frc::Solenoid(CARGO_INTAKE_SOLENOID);
  m_isExtended = false;
}

void CargoIntake::InitDefaultCommand() {}

void CargoIntake::Periodic() {
  frc::SmartDashboard::PutNumber("Is Extended", m_isExtended);
}

void CargoIntake::SetSpeedIn(double speed) {
  m_intakeMotor->Set(ControlMode::PercentOutput, speed);
}
void CargoIntake::SetSpeedOut(double speed) {
  m_intakeMotor->Set(ControlMode::PercentOutput, -speed);
}
void CargoIntake::StopIntake() {
    m_intakeMotor->Set(ControlMode::PercentOutput, 0);
}
bool CargoIntake::HasBall() {
  return false;
}
void CargoIntake::Extend() {
  m_extendSolenoid->Set(true);
  m_isExtended = true;
}
void CargoIntake::Retract() {
  m_extendSolenoid->Set(false);
  m_isExtended = false;
}
bool CargoIntake::IsExtended() {
  return m_isExtended;
}