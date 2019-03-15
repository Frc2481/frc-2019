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
  m_extendMotor = new TalonSRX(CARGO_INTAKE_EXTEND_MOTOR_ID);
  m_extendEncoder = new CTREMagEncoder(m_extendMotor, "CARGO_INTAKE_ENCODER");
  m_beamBreak = new frc::DigitalInput(CARGO_BEAM_BREAK_SENSOR);

	ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_extendMotor->Set(ControlMode::MotionMagic, 0);
  m_extendMotor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_extendMotor->EnableCurrentLimit(false);

  m_extendMotor->SetSensorPhase(true);
  m_extendMotor->SetInverted(true);

  talonConfig.slot0.integralZone = 1700;
  talonConfig.slot0.kF = 0.3;
  talonConfig.slot0.kP = 0.5;
  talonConfig.slot0.kI = 0.05;
  talonConfig.slot0.kD = 1;
  talonConfig.slot0.maxIntegralAccumulator = 500;

  talonConfig.motionCruiseVelocity = 4000; 
  talonConfig.motionAcceleration = 20000; 
  talonConfig.motionCurveStrength = 5;

  talonConfig.peakCurrentDuration = 0; 
  talonConfig.continuousCurrentLimit = 30;

  talonConfig.peakCurrentLimit = 0; 
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitThreshold = 17700;
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 0;
  talonConfig.reverseSoftLimitEnable = true;

  m_extendMotor->ConfigAllSettings(talonConfig);
  m_extendMotor->SelectProfileSlot(0, 0);

  m_desiredPosition = 0;
  m_isZeroed = false;
  m_hasResetOccurred = m_extendMotor->HasResetOccurred();
}

void CargoIntake::InitDefaultCommand() {
  SetOpenLoopSpeed(0.0);
}

void CargoIntake::Periodic() {
  frc::SmartDashboard::PutBoolean("intakeEncConnnected", m_extendEncoder->isConnected());
  frc::SmartDashboard::PutBoolean("ballIntaken", IsBallIntaken());
  frc::SmartDashboard::PutBoolean("HasBall", HasBall()); //Only returns False
  frc::SmartDashboard::PutNumber("CargoIntakeError", GetCargoIntakeError());
  frc::SmartDashboard::PutNumber("CargoPos", GetPosition());
  frc::SmartDashboard::PutNumber("GetDesiredPos", GetDesiredPosition());
  frc::SmartDashboard::PutBoolean("IsCargoIntakeOnTarget", IsOnTarget());
  // frc::SmartDashboard::PutBoolean("IsCargoIntakeTalonReset", m_extendMotor->HasResetOccurred());
  frc::SmartDashboard::PutBoolean("IsCargoIntakeZeroed", m_isZeroed);
  if (m_extendMotor->HasResetOccurred() && m_isZeroed){
    m_isZeroed = false;
    SetOpenLoopSpeed(0);
  }
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
bool CargoIntake::HasBall() { //TODO
  return false;
}
void CargoIntake::SetPosition(double pos) {
  if(m_isZeroed){
    // m_extendMotor->Set(ControlMode::MotionMagic, ConvertInchesToTicks(pos));
    if(m_extendMotor->GetSelectedSensorPosition() < pos) {
      m_extendMotor->Set(ControlMode::MotionMagic, pos, DemandType::DemandType_ArbitraryFeedForward, 0.22);
    }
    else {
      m_extendMotor->Set(ControlMode::MotionMagic, pos, DemandType::DemandType_ArbitraryFeedForward, -0.22);
    }
    m_desiredPosition = pos;
  }
}
double CargoIntake::GetDesiredPosition(){
  return m_desiredPosition;
}
double CargoIntake::GetPosition() {
  return m_extendMotor->GetSelectedSensorPosition(0);
}
double CargoIntake::GetVelocity() {
  return m_extendMotor->GetActiveTrajectoryVelocity();
}
double CargoIntake::ConvertTicksToInches(int ticks) {
  return ticks * RobotParameters::k_cargoIntakeBeltCircumference / RobotParameters::k_cargoIntakeTicksPerRev;

}
int CargoIntake::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_cargoIntakeTicksPerRev / RobotParameters::k_cargoIntakeBeltCircumference;
}

double CargoIntake::GetCargoIntakeError() {
  return ConvertTicksToInches(m_extendMotor->GetClosedLoopError());
}
bool CargoIntake::IsIntakeInProtectedZone() {
  return GetPosition() > RobotParameters::k_cargoIntakeThresholdIn && GetPosition() < RobotParameters::k_cargoIntakeThresholdOut; //assuming zero measures from point that intake is in
}
bool CargoIntake::IsIntakeOut() {
  return GetPosition() > RobotParameters::k_cargoIntakeThresholdOut; //assuming zero measures from point that intake is in
}
bool CargoIntake::IsIntakeIn() {
  return GetPosition() < RobotParameters::k_cargoIntakeThresholdIn; //assuming zero measures from point that intake is in
}
bool CargoIntake::IsBallIntaken() {
  return !m_beamBreak->Get();
}
void CargoIntake::SetOpenLoopSpeed(double speed) {
  m_extendMotor->Set(ControlMode::PercentOutput, speed);
}

bool CargoIntake::IsOnTarget() {
  return fabs(m_desiredPosition - m_extendMotor->GetSelectedSensorPosition()) < ConvertInchesToTicks(0.25);
}

void CargoIntake::ZeroCargoIntake() {
  for(int i = 0; i < 5; i++) {
  ErrorCode error = m_extendMotor->SetSelectedSensorPosition(0, 0, 10);
    if(error == OK) {
      break;
    }
  }
  m_isZeroed = true;
  m_extendMotor->ClearStickyFaults(0);
}
