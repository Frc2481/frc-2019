/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/HatchSlide.h"
#include "RobotParameters.h"
#include "Commands/HatchSlide/HatchSlideGoToPosition.h"

HatchSlide::HatchSlide() : Subsystem("HatchSlide") {
  m_motor = new TalonSRX(20);
  m_slideEncoder = new CTREMagEncoder(m_motor, "SLIDE_MOTOR_ENCODER");
  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_motor->SetSensorPhase(true);
  m_motor->SetInverted(false);
  m_motor->SelectProfileSlot(0, 0);
  m_motor->SetNeutralMode(Brake);
  m_motor->SetStatusFramePeriod(Status_2_Feedback0_, 10, 0);
  m_motor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_motor->EnableCurrentLimit(false);
  m_motor->ConfigAllSettings(talonConfig);

  talonConfig.slot0.kF = 0.1528;
  talonConfig.slot0.kP = 0.07;
  talonConfig.slot0.allowableClosedloopError = 0;
  talonConfig.motionCruiseVelocity = 6500; //convert to talonConfig speed: encoder count/100 ms / 2.0
  talonConfig.motionAcceleration = 13000; //9200
  talonConfig.peakCurrentDuration = 0; //TODO
  talonConfig.continuousCurrentLimit = 30; //TODO
  talonConfig.peakCurrentLimit = 0; //TODO
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  nt::NetworkTableInstance::GetDefault().SetUpdateRate(.01);

  m_irSensor = new frc::Counter();
  m_irSensor->SetSemiPeriodMode(true);
  m_irSensor->SetUpSource(0);

  m_desiredSetpoint = 0.0;
  m_hatchPosition = 0.0;
  m_isHatchZeroed = false;
  m_pulse = 0.0;
  m_isVibratable = false;
  m_encoderConnected = false;
  m_hatchSlideEnabled = false;
}

void HatchSlide::InitDefaultCommand() {
  SetDefaultCommand(new HatchSlideGoToPosition());
}

void HatchSlide::Periodic() {
  SmartDashboard::PutNumber("Hatch Slide error", m_desiredSetpoint - m_hatchPosition);
  SmartDashboard::PutBoolean("Is Hatch Zeroed", m_isHatchZeroed);

  m_pulse = m_irSensor->GetPeriod();

  SmartDashboard::PutNumber("Teensy dist", GetPulseDist());
  SmartDashboard::PutNumber("hatch slide dist", ConvertTicksToInches(GetHatchPosition()));
  if(m_motor->GetControlMode() == ControlMode::MotionMagic) {
    SmartDashboard::PutNumber("active trajectory position slide", ConvertTicksToInches(m_motor->GetActiveTrajectoryPosition()));
    SmartDashboard::PutNumber("active trajectory velocity slide", ConvertTicksToInches(m_motor->GetActiveTrajectoryVelocity() * 10));
  }

  SmartDashboard::PutBoolean("is line visible", IsLineVisible());
  
  m_encoderConnected = m_slideEncoder->isConnected();
  SmartDashboard::PutBoolean("slide encoder is connnected", m_encoderConnected);

  bool oldTargetValid = IsLineVisible();

  if(IsLineVisible() && !oldTargetValid) {
    m_isVibratable = true;
  }
  else {
    m_isVibratable = false;
  }
}

void HatchSlide::setSetPoint(int value) {
  // m_motor->Config_kF(0, CommandBase::m_pLineFinder->getXVel() * RobotParameters::k_lineFinderKp, 0);
  m_motor->Set(ControlMode::MotionMagic, value);
  // m_motor->Set(ControlMode::MotionMagic, value, DemandType_ArbitraryFeedForward, .03 * CommandBase::m_pLineFinder->getXVel());
  m_desiredSetpoint = value;
  SmartDashboard::PutNumber("setSetpoint value", value);
}

void HatchSlide::ZeroHatchPosition() {
  m_motor->SetSelectedSensorPosition(0, 0, 10);
  m_isHatchZeroed = true;
}

double HatchSlide::GetHatchPosition() {
  return m_motor->GetSelectedSensorPosition(0);
}

double HatchSlide::GetDesiredPos() {
  return ConvertInchesToTicks(GetPulseDist());
}

int HatchSlide::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_ctreMagEncoderTicksPerRev / RobotParameters::k_beltCircumference;
}

double HatchSlide::ConvertTicksToInches(int ticks) {
  return ticks * RobotParameters::k_beltCircumference / RobotParameters::k_ctreMagEncoderTicksPerRev;
}

double HatchSlide::GetPulseDist() {
  return ((m_pulse * 488.0 * 256.0) / 8.0); // pulse * teensy frequency * pulse width / scaling factor
}

bool HatchSlide::IsLineVisible() {
  return (GetPulseDist() >-1 && GetPulseDist() < 28);
}

bool HatchSlide::IsSlideOnTarget() {
  return fabs(GetHatchPosition() - GetDesiredPos()) < 0.5;
}

bool HatchSlide::IsVibratable() {
    return m_isVibratable;
}

void HatchSlide::ResetVibratable() {
    m_isVibratable = false;
}

bool HatchSlide::SlideEncoderConnected() {
  return m_encoderConnected;
}

void HatchSlide::EnableHatchSlide() {
  m_hatchSlideEnabled = true;
}

void HatchSlide::DisableHatchSlide() {
  m_hatchSlideEnabled = false;
}

bool HatchSlide::IsHatchSlideEnabled() {
  return m_hatchSlideEnabled;
}