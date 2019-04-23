/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/HatchSlide.h"
#include "RobotParameters.h"
#include "RobotMap.h"

HatchSlide::HatchSlide() : Subsystem("HatchSlide") {
  m_motor = new TalonSRX(HATCH_SLIDE_MOTOR_ID);
  m_slideEncoder = new CTREMagEncoder(m_motor, "SLIDE_MOTOR_ENCODER");
  ctre::phoenix::motorcontrol::can::TalonSRXConfiguration talonConfig;

  m_hatchSensor = new frc::DigitalInput(TOOL_CHANGER_CAPACITIVE_SENSOR);

	m_LED = new frc::Solenoid(LED);
  m_LED->Set(false);

  m_motor->SetInverted(false);
  m_motor->SetSensorPhase(true);
  m_motor->SetNeutralMode(Brake);
  m_motor->SetStatusFramePeriod(Status_2_Feedback0_, 10, 0);
  m_motor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);
  m_motor->EnableCurrentLimit(true);

  talonConfig.motionCurveStrength = 5;

  talonConfig.slot0.kF = 0.15; // 1024/max speed //old = 0.1528;
  talonConfig.slot0.kP = 1;
  talonConfig.slot0.allowableClosedloopError = RobotParameters::k_allowableCloseLoopError;
  talonConfig.motionCruiseVelocity = 7000; //convert to talonConfig speed: encoder count/100 ms / 2.0
  talonConfig.motionAcceleration = 56000; //9200
  talonConfig.peakCurrentDuration = 500; 
  talonConfig.continuousCurrentLimit = 20;
  talonConfig.peakCurrentLimit = 30;
  talonConfig.primaryPID.selectedFeedbackSensor = CTRE_MagEncoder_Relative;

  talonConfig.forwardSoftLimitEnable = true;
  talonConfig.reverseSoftLimitEnable = true;
  talonConfig.forwardSoftLimitThreshold = 9000;
  talonConfig.reverseSoftLimitThreshold = -9000;

  talonConfig.forwardLimitSwitchNormal = LimitSwitchNormal_Disabled;
  talonConfig.reverseLimitSwitchNormal = LimitSwitchNormal_Disabled;

  m_motor->ConfigAllSettings(talonConfig);
  m_motor->SelectProfileSlot(0, 0);

  // nt::NetworkTableInstance::GetDefault().SetUpdateRate(.01);

  m_irSensorBright = new frc::Counter();
  m_irSensorBright->SetSemiPeriodMode(true);
  m_irSensorBright->SetUpSource(IR_SENSOR_BRIGHT);
  m_irSensorBright->SetUpdateWhenEmpty(true);
  m_irSensorBright->SetMaxPeriod(0.004);

  m_irSensorDim = new frc::Counter();
  m_irSensorDim->SetSemiPeriodMode(true);
  m_irSensorDim->SetUpSource(IR_SENSOR_DIM);
  m_irSensorDim->SetUpdateWhenEmpty(true);
  m_irSensorDim->SetMaxPeriod(0.004);

  m_isHatchZeroed = false;
  m_pulseBright = 0.0;
  m_pulseDim = 0.0;
  m_isVibratable = false;
  m_encoderConnected = false;
  m_hatchSlideUserEnabled = false;
  m_hatchSlideSafetyEnabled = false;
  m_oldTargetValid = false;
  frc::SmartDashboard::PutBoolean("IsSlideTalonReset", true);
  m_ledDesiredState = false;
  m_noLineCounter = 0;
  m_desiredPos = 0.0;
}

void HatchSlide::InitDefaultCommand() {}

void HatchSlide::Periodic() {
  m_pulseBright = m_irSensorBright->GetPeriod();
  m_pulseDim = m_irSensorDim->GetPeriod();
  static int loopCounter = -1;
  loopCounter++;
  loopCounter %= 8;
  if (loopCounter == 0) {
    frc::SmartDashboard::PutNumber("HatchSlideError", m_motor->GetClosedLoopError());
    frc::SmartDashboard::PutBoolean("IsHatchZeroed", m_isHatchZeroed);
  }
  else if (loopCounter == 1) {
    frc::SmartDashboard::PutBoolean("IsSlideOnTarget", IsSlideOnTarget());
    frc::SmartDashboard::PutNumber("HatchSlidePos", ConvertTicksToInches(GetHatchPosition()));
  }
  else if (loopCounter == 2) {
    frc::SmartDashboard::PutBoolean("IsHatchSeen", IsHatchSeen());
    frc::SmartDashboard::PutBoolean("HasBall", HasBall());
  }
  else if (loopCounter == 3) {
    bool hasResetOccurred = m_motor->HasResetOccurred();
    if(hasResetOccurred && m_isHatchZeroed){
      frc::SmartDashboard::PutBoolean("IsSlideTalonReset", !hasResetOccurred);
      m_isHatchZeroed = false;
      SetOpenLoopSpeed(0);
      printf("!!! Hatch Slide Talon Reset !!!\n");
    }
  }
  else if (loopCounter == 4) {
    frc::SmartDashboard::PutNumber("PWM value", m_pulseBright);
  }
  else if (loopCounter == 5) {
    frc::SmartDashboard::PutNumber("Teensy dist bright", GetBrightPulseDist());
    frc::SmartDashboard::PutNumber("Teensy dist dim", GetDimPulseDist());
  }
  else if (loopCounter == 6) {
    frc::SmartDashboard::PutBoolean("is line visible", IsLineVisible());
    frc::SmartDashboard::PutBoolean("IsLineSensorWorking", IsLineSensorWorking());
    m_encoderConnected = m_slideEncoder->isConnected();
    frc::SmartDashboard::PutBoolean("slideEncConnnected", m_encoderConnected);
  }
  else if (loopCounter == 7) {
    if(IsLineVisible() && !m_oldTargetValid) {
      m_isVibratable = true;
    }
    else {
      m_isVibratable = false;
    }

    m_oldTargetValid = IsLineVisible();
  }
  if(IsHatchSlideUserEnabled() & IsLineSensorWorking()) {
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
    frc::SmartDashboard::PutNumber("hatch slide setpoint", ConvertInchesToTicks(GetBrightPulseDist() - 13));
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
    m_desiredPos = value;
    if(RobotParameters::k_allowableCloseLoopError > fabs(m_motor->GetSelectedSensorPosition() - value)) {
      SetOpenLoopSpeed(0);
    }
    else {
      m_motor->Set(ControlMode::MotionMagic, value, DemandType::DemandType_ArbitraryFeedForward, 0); //-0.1);
    }
  }
  frc::SmartDashboard::PutNumber("HatchDesiredPos", value);
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
  return fabs(m_desiredPos - GetHatchPosition()) < 500;
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
bool HatchSlide::IsLineSensorWorking() {
  return !m_irSensorBright->GetStopped(); // || m_irSensorDim->GetStopped();
}
