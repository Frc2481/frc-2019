/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/CargoIntake.h"
#include "RobotMap.h"
#include "RobotParameters.h"

CargoIntake::CargoIntake() : Subsystem("CargoIntake") {
  m_intakeMotor = new VictorSPX(CARGO_INTAKE_MOTOR_ID);
  m_cargoPreIntakeSensor = new frc::DigitalInput(CARGO_PRE_INTAKE_BALL_SENSOR);
  m_extendIntakeSolenoid = new frc::Solenoid(CARGO_INTAKE_EXTEND_SOLENOID);
  m_extendIntakeSolenoid->Set(false);

  m_isIntakeOut = false;
}

void CargoIntake::InitDefaultCommand() {}

void CargoIntake::Periodic() {
  frc::SmartDashboard::PutBoolean("IsBallIntaken", IsBallIntaken());
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
bool CargoIntake::IsBallIntaken() {
  return !m_cargoPreIntakeSensor->Get();
}
void CargoIntake::ExtendIntake() {
  m_extendIntakeSolenoid->Set(true);
  m_isIntakeOut = true;
}
void CargoIntake::RetractIntake() {
  m_extendIntakeSolenoid->Set(false);
  m_isIntakeOut = false;
}
bool CargoIntake::IsIntakeOut() {
  return m_isIntakeOut;
}
