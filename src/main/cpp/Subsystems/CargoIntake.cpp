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
  m_intakeMotor = new TalonSRX(CARGO_INTAKE_MOTOR);
  m_extendMotor = new TalonSRX(CARGO_INTAKE_EXTEND_MOTOR);
  m_extendEncoder = new CTREMagEncoder(m_extendMotor, "CARGO_INTAKE_ENCODER");

	ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_position = 0;

  m_extendMotor->Set(ControlMode::MotionMagic, 0);

  talonConfig.slot0.kF = 0;
  talonConfig.slot0.kP = 0;
  talonConfig.slot0.kI = 0;
  talonConfig.slot0.kD = 0;

  talonConfig.motionCruiseVelocity = 0; //TODO: change
  talonConfig.motionAcceleration = 0; //TODO: change

  m_extendMotor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);

  talonConfig.peakCurrentDuration = 0; //TODO:
  talonConfig.continuousCurrentLimit = 30; //TODO:
  m_extendMotor->EnableCurrentLimit(false);
  talonConfig.peakCurrentLimit = 0; //TODO
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitThreshold = 0; //TODO: change soft limit
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 0;
  talonConfig.reverseSoftLimitEnable = true;

  m_extendMotor->GetAllConfigs(talonConfig);
}

void CargoIntake::InitDefaultCommand() {}

void CargoIntake::Periodic() {
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
void CargoIntake::SetPosition(double pos) {
  m_extendMotor->Set(ControlMode::MotionMagic, ConvertInchesToTicks(pos));
  m_position = pos;
}
double CargoIntake::GetPosition() {
  return m_extendMotor->GetActiveTrajectoryPosition();
}
double CargoIntake::ConvertTicksToInches(int ticks) {
  return ticks / RobotParameters::k_cargoIntakeTicksPerInch;
}
int CargoIntake::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_cargoIntakeTicksPerInch;
}

double CargoIntake::GetCargoIntakeError() {
  return m_extendMotor->GetClosedLoopError();
}
bool CargoIntake::IsIntakeOut() {
  return GetPosition() > RobotParameters::k_cargoIntakeThreshold;
}
