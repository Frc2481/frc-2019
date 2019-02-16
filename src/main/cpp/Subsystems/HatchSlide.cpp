/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/HatchSlide.h"
#include "RobotParameters.h"
#include "Commands/HatchSlide/HatchSlideGoToPosition.h"
#include "RobotMap.h"

HatchSlide::HatchSlide() : Subsystem("HatchSlide") {
  m_motor = new TalonSRX(HATCH_SLIDE_MOTOR_ID);
  m_slideEncoder = new CTREMagEncoder(m_motor, "SLIDE_MOTOR_ENCODER");
  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_motor->SetSensorPhase(true);
  m_motor->SetInverted(false);
  m_motor->SetNeutralMode(Brake);
  m_motor->SetStatusFramePeriod(Status_2_Feedback0_, 10, 0);
  m_motor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_motor->EnableCurrentLimit(false);

  talonConfig.slot0.kF = 0.1528;
  talonConfig.slot0.kP = 0.07;
  talonConfig.slot0.allowableClosedloopError = 0;
  talonConfig.motionCruiseVelocity = 6500; //convert to talonConfig speed: encoder count/100 ms / 2.0
  talonConfig.motionAcceleration = 13000; //9200
  talonConfig.peakCurrentDuration = 0; //TODO
  talonConfig.continuousCurrentLimit = 30; //TODO
  talonConfig.peakCurrentLimit = 0; //TODO
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  m_motor->ConfigAllSettings(talonConfig);
  m_motor->SelectProfileSlot(0, 0);

  nt::NetworkTableInstance::GetDefault().SetUpdateRate(.01);

  m_irSensorBright = new frc::Counter();
  m_irSensorBright->SetSemiPeriodMode(true);
  m_irSensorBright->SetUpSource(0);

  m_irSensorDim = new frc::Counter();
  m_irSensorDim->SetSemiPeriodMode(true);
  m_irSensorDim->SetUpSource(0);

  m_isHatchZeroed = false;
  m_pulseBright = 0.0;
  m_pulseDim = 0.0;
  m_isVibratable = false;
  m_encoderConnected = false;
  m_hatchSlideEnabled = false;
  m_oldTargetValid = false;
}

void HatchSlide::InitDefaultCommand() {
  SetDefaultCommand(new HatchSlideGoToPosition());
}

void HatchSlide::Periodic() {
  SmartDashboard::PutNumber("Hatch Slide error", m_motor->GetClosedLoopError());;
  SmartDashboard::PutBoolean("Is Hatch Zeroed", m_isHatchZeroed);

  m_pulseBright = m_irSensorBright->GetPeriod();
  m_pulseDim = m_irSensorDim->GetPeriod();

  SmartDashboard::PutNumber("Teensy dist bright", GetBrightPulseDist());
  SmartDashboard::PutNumber("Teensy dist dim", GetDimPulseDist());
  SmartDashboard::PutNumber("hatch slide dist", ConvertTicksToInches(GetHatchPosition()));
  if(m_motor->GetControlMode() == ControlMode::MotionMagic) {
    SmartDashboard::PutNumber("active trajectory position slide", ConvertTicksToInches(m_motor->GetActiveTrajectoryPosition()));
    SmartDashboard::PutNumber("active trajectory velocity slide", ConvertTicksToInches(m_motor->GetActiveTrajectoryVelocity() * 10));
  }

  SmartDashboard::PutBoolean("is line visible", IsLineVisible());
  
  m_encoderConnected = m_slideEncoder->isConnected();
  SmartDashboard::PutBoolean("slideEncConnnected", m_encoderConnected);

  if(IsLineVisible() && !m_oldTargetValid) {
    m_isVibratable = true;
  }
  else {
    m_isVibratable = false;
  }

  m_oldTargetValid = IsLineVisible();
}

void HatchSlide::setSetPoint(int value) {
  // m_motor->Config_kF(0, CommandBase::m_pLineFinder->getXVel() * RobotParameters::k_lineFinderKp, 0);
  m_motor->Set(ControlMode::MotionMagic, value);
  // m_motor->Set(ControlMode::MotionMagic, value, DemandType_ArbitraryFeedForward, .03 * CommandBase::m_pLineFinder->getXVel());
  SmartDashboard::PutNumber("setSetpoint value", value);
}

void HatchSlide::ZeroHatchPosition() {
  m_motor->SetSelectedSensorPosition(0, 0, 10);
  m_isHatchZeroed = true;
}

double HatchSlide::GetHatchPosition() {
  return m_motor->GetSelectedSensorPosition(0);
}

double HatchSlide::GetSuggestedPos() {
  return ConvertInchesToTicks(GetBrightPulseDist());
}

int HatchSlide::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_ctreMagEncoderTicksPerRev / RobotParameters::k_beltCircumference;
}

double HatchSlide::ConvertTicksToInches(int ticks) {
  return ticks * RobotParameters::k_beltCircumference / RobotParameters::k_ctreMagEncoderTicksPerRev;
}

double HatchSlide::GetBrightPulseDist() {
  return ((m_pulseBright * 488.0 * 256.0) / 8.0); // pulse * teensy frequency * pulse width / scaling factor
}

double HatchSlide::GetDimPulseDist() {
  return ((m_pulseDim * 488.0 * 256.0) / 8.0); // pulse * teensy frequency * pulse width / scaling factor
}

bool HatchSlide::IsLineVisible() {
  return (GetBrightPulseDist() >-1 && GetBrightPulseDist() < 28);
}

bool HatchSlide::IsSlideOnTarget() {
  return fabs(m_motor->GetClosedLoopError()) < 0.5;
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