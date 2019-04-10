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
  m_intakeMotor->SetInverted(true);
  m_cargoPreIntakeSensor = new frc::DigitalInput(CARGO_PRE_INTAKE_BALL_SENSOR);
  m_extendMotor = new TalonSRX(CARGO_INTAKE_EXTEND_MOTOR_ID);
  m_extendEncoder = new CTREMagEncoder(m_extendMotor, "CARGO_INTAKE_ENCODER");

  // m_extendIntakeSolenoid = new frc::Solenoid(CARGO_INTAKE_EXTEND_SOLENOID);
  // m_extendIntakeSolenoid->Set(false);

  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;
  m_extendMotor->Set(ControlMode::MotionMagic, 0);
  m_extendMotor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_extendMotor->EnableCurrentLimit(true);
  m_extendMotor->SetSensorPhase(true);
  m_extendMotor->SetInverted(false);
  m_extendMotor->SetNeutralMode(Coast);

  talonConfig.slot0.integralZone = 0;
  talonConfig.slot0.kF = 0.19;
  talonConfig.slot0.kP = 0.075;
  talonConfig.slot0.kI = 0;
  talonConfig.slot0.kD = 0;
  talonConfig.slot0.maxIntegralAccumulator = 0;
  talonConfig.motionCruiseVelocity = 4000; 
  talonConfig.motionAcceleration = 100000;
  talonConfig.motionCurveStrength = 8;
  talonConfig.peakCurrentDuration = 500; 
  talonConfig.continuousCurrentLimit = 40;
  talonConfig.peakCurrentLimit = 60;
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;
  talonConfig.forwardSoftLimitThreshold = 14280;
  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitThreshold = 0;
  talonConfig.reverseSoftLimitEnable = true;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_NormallyOpen;
  talonConfig.clearPositionOnLimitR = true;
  
  m_extendMotor->ConfigAllSettings(talonConfig);
  m_extendMotor->SelectProfileSlot(0, 0);

  m_desiredPos = 0;
  m_isZeroed = false;
  frc::SmartDashboard::PutBoolean("HasCargoIntakeTalonReset", true);
  m_isBallIntaken = false;
  m_scale = 1;
}

void CargoIntake::InitDefaultCommand() {}

void CargoIntake::Periodic() {
  static int loopCounter = -1;
  loopCounter++;
  loopCounter %= 4;
  m_isBallIntaken = !m_cargoPreIntakeSensor->Get();
  if (loopCounter == 0) {
    frc::SmartDashboard::PutBoolean("IsBallIntaken", m_isBallIntaken);
    frc::SmartDashboard::PutBoolean("IsCargoIntakeZeroed", m_isZeroed);
  }
  else if (loopCounter == 1) {
    bool hasTalonReset = m_extendMotor->HasResetOccurred();
    if(m_isZeroed && hasTalonReset) {
      frc::SmartDashboard::PutBoolean("CargoIntakeTalonReset", hasTalonReset);
      m_isZeroed = false;
    }
  }
  else if (loopCounter == 2) {
    frc::SmartDashboard::PutNumber("CargoIntakeError", GetPos() - GetDesiredPos());
    frc::SmartDashboard::PutNumber("CargoIntakePos", GetPos());
    frc::SmartDashboard::PutNumber("CargoIntakeDesiredPos", GetDesiredPos());
  }
  else if (loopCounter == 3) {
    m_encoderConnected = m_extendEncoder->isConnected();
    frc::SmartDashboard::PutBoolean("IsCargoIntakeEncoderConnected", m_encoderConnected);
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
bool CargoIntake::IsBallIntaken() {
  return m_isBallIntaken;
}
void CargoIntake::SetPosition(double pos) {
  if(m_isZeroed){
    if(m_extendMotor->GetSelectedSensorPosition() < pos) {
      m_extendMotor->Set(ControlMode::MotionMagic, pos, DemandType::DemandType_ArbitraryFeedForward, 0.22);
    }
    else {
      m_extendMotor->Set(ControlMode::MotionMagic, pos, DemandType::DemandType_ArbitraryFeedForward, -0.22);
    }
    m_desiredPos = pos;
  }
}
// void CargoIntake::SetSpeed(double scale) {
	// m_scale = scale;
	// m_extendMotor->ConfigMotionCruiseVelocity(2000 * m_scale, 0);
	// m_extendMotor->ConfigMotionAcceleration(50000 * m_scale, 0);
// }
bool CargoIntake::IsOnTarget() {
  return fabs(GetPos() - GetDesiredPos()) < 200;
}
double CargoIntake::GetPos() {
  return m_extendMotor->GetSelectedSensorPosition(0);
}
double CargoIntake::GetDesiredPos() {
  return m_desiredPos;
}
double CargoIntake::ConvertTicksToInches(int ticks) {
  return ticks * RobotParameters::k_cargoIntakeBeltCircumference / RobotParameters::k_cargoIntakeTicksPerRev;
}
int CargoIntake::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_cargoIntakeTicksPerRev / RobotParameters::k_cargoIntakeBeltCircumference;
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
void CargoIntake::SetOpenLoopSpeed(double speed) {
  m_extendMotor->Set(ControlMode::PercentOutput, speed);
}