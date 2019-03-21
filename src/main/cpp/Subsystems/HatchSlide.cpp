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

  m_hatchSensor = new frc::DigitalInput(TOOL_CHANGER_CAPACITIVE_SENSOR);

	m_LED = new Solenoid(LED);
  m_LED->Set(false);

  m_motor->SetInverted(false);
  m_motor->SetSensorPhase(true);
  m_motor->SetNeutralMode(Brake);
  m_motor->SetStatusFramePeriod(Status_2_Feedback0_, 10, 0);
  m_motor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_motor->EnableCurrentLimit(false);

  talonConfig.motionCurveStrength = 5;

  talonConfig.slot0.kF = 0.15; // 1024/max speed //old = 0.1528;
  talonConfig.slot0.kP = 1;
  talonConfig.slot0.allowableClosedloopError = RobotParameters::k_allowableCloseLoopError;
  talonConfig.motionCruiseVelocity = 7000; //convert to talonConfig speed: encoder count/100 ms / 2.0
  talonConfig.motionAcceleration = 56000; //9200
  talonConfig.peakCurrentDuration = 0; 
  talonConfig.continuousCurrentLimit = 30;
  talonConfig.peakCurrentLimit = 0;
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitEnable = true;
  talonConfig.forwardSoftLimitThreshold = 9000;
  talonConfig.reverseSoftLimitThreshold = -9000;

  talonConfig.forwardLimitSwitchNormal = LimitSwitchNormal_Disabled;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_Disabled;

  m_motor->ConfigAllSettings(talonConfig);
  m_motor->SelectProfileSlot(0, 0);

  // nt::NetworkTableInstance::GetDefault().SetUpdateRate(.01);P

  m_irSensorBright = new frc::Counter();
  m_irSensorBright->SetSemiPeriodMode(true);
  m_irSensorBright->SetUpSource(IR_SENSOR_BRIGHT);

  m_irSensorDim = new frc::Counter();
  m_irSensorDim->SetSemiPeriodMode(true);
  m_irSensorDim->SetUpSource(IR_SENSOR_DIM);

  m_isHatchZeroed = false;
  m_pulseBright = 0.0;
  m_pulseDim = 0.0;
  m_isVibratable = false;
  m_encoderConnected = false;
  m_hatchSlideUserEnabled = false;
  m_hatchSlideSafetyEnabled = false;
  m_oldTargetValid = false;
  m_hasResetOccurred = m_motor->HasResetOccurred();
  SmartDashboard::PutBoolean("IsSlideTalonReset", true);
  m_ledDesiredState = false;
  m_noLineCounter = 0;
  m_desiredPos = 0.0;
}

void HatchSlide::InitDefaultCommand() {
  // SetDefaultCommand(new HatchSlideGoToPosition());
}

void HatchSlide::Periodic() {
  SmartDashboard::PutNumber("HatchSlideError", m_motor->GetClosedLoopError());
  SmartDashboard::PutBoolean("IsHatchZeroed", m_isHatchZeroed);
  SmartDashboard::PutBoolean("IsSlideOnTarget", IsSlideOnTarget());
  SmartDashboard::PutNumber("HatchSlidePos", ConvertTicksToInches(GetHatchPosition()));
  frc::SmartDashboard::PutBoolean("IsHatchSeen", IsHatchSeen());
  frc::SmartDashboard::PutBoolean("HasBall", HasBall());
  if(m_motor->HasResetOccurred() && m_isHatchZeroed){
  SmartDashboard::PutBoolean("IsSlideTalonReset", !m_motor->HasResetOccurred());
    m_isHatchZeroed = false;
    SetOpenLoopSpeed(0);
  }

  m_pulseBright = m_irSensorBright->GetPeriod();
  m_pulseDim = m_irSensorDim->GetPeriod();

  SmartDashboard::PutNumber("PWM value", m_pulseBright);

  SmartDashboard::PutNumber("Teensy dist bright", GetBrightPulseDist());
  SmartDashboard::PutNumber("Teensy dist dim", GetDimPulseDist());

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

  //go to position
  if(IsHatchSlideUserEnabled()) {
    if(IsLineVisible() && isZeroed()) {
      setSetPoint(ConvertInchesToTicks(GetBrightPulseDist() - 13));
      m_noLineCounter = 0;
    }
    else if(!IsLineVisible() && isZeroed()) {
      m_noLineCounter++;
      if(m_noLineCounter > 20) {
        setSetPoint(0);
      }
    }
    else if(!isZeroed()) {
      SetOpenLoopSpeed(0);
    }
    SmartDashboard::PutNumber("hatch slide setpoint", ConvertInchesToTicks(GetBrightPulseDist() - 13));
  }
  else {
    setSetPoint(0);
  }

  if(RobotParameters::k_allowableCloseLoopError > fabs(m_motor->GetSelectedSensorPosition() - m_desiredPos)) {
      m_LED->Set(true);
  }
  else {
    m_LED->Set(false);
  }
}

void HatchSlide::setSetPoint(int value) {
  if(m_isHatchZeroed){
  // m_motor->Set(ControlMode::MotionMagic, value);
    // if(m_motor->GetSelectedSensorPosition() < value) {
    //   m_motor->Set(ControlMode::MotionMagic, value, DemandType::DemandType_ArbitraryFeedForward, 0); //0.1);
    //           m_LED->Set(true);
    // }
    // else if(m_motor->GetSelectedSensorPosition() > value){
    // }
    m_desiredPos = value;
    if(RobotParameters::k_allowableCloseLoopError > fabs(m_motor->GetSelectedSensorPosition() - value)) {
      SetOpenLoopSpeed(0);
    }
    else {
      m_motor->Set(ControlMode::MotionMagic, value, DemandType::DemandType_ArbitraryFeedForward, 0); //-0.1);
    }
  }
  SmartDashboard::PutNumber("HatchDesiredPos", value);
}

void HatchSlide::ZeroHatchPosition() {
  for(int i = 0; i < 5; i++) {
    ErrorCode error = m_motor->SetSelectedSensorPosition(0, 0, 10);
    if(error == OK) {
      break;
    }
  }
  m_isHatchZeroed = true;
  m_motor->ClearStickyFaults();
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
  return GetBrightPulseDist() < 29;
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

void HatchSlide::EnableUserHatchSlide() {
  m_hatchSlideUserEnabled = true;
}

void HatchSlide::DisableUserHatchSlide() {
  m_hatchSlideUserEnabled = false;
}

bool HatchSlide::IsHatchSlideUserEnabled() {
  return m_hatchSlideUserEnabled;
}

void HatchSlide::EnableSafetyHatchSlide() {
  m_hatchSlideSafetyEnabled = true;
}

void HatchSlide::DisableSafetyHatchSlide() {
  m_hatchSlideSafetyEnabled = false;
}

bool HatchSlide::IsHatchSlideSafetyEnabled() {
  return m_hatchSlideSafetyEnabled;
}

void HatchSlide::SetOpenLoopSpeed(double speed) {
  m_motor->Set(ControlMode::PercentOutput, speed);
}

bool HatchSlide::isZeroed(){
  return m_isHatchZeroed;
}
bool HatchSlide::HasBall() {
  return m_motor->GetSensorCollection().IsFwdLimitSwitchClosed();
}
bool HatchSlide::IsHatchSeen() {
  return m_hatchSensor;
}
void HatchSlide::SetLEDs(bool led) {
  m_LED->Set(led);
}

bool HatchSlide::GetLEDs() {
  return m_LED->Get();
}