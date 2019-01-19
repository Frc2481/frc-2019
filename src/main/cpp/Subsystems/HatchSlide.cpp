/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/HatchSlide.h"
#include "Commands/HatchSlideGoToPosition.h"
#include "RobotParameters.h"

HatchSlide::HatchSlide() : Subsystem("HatchSlide") {
  m_motor = new TalonSRX(20);
  m_motor->SetSensorPhase(true);
  m_motor->SetInverted(false);
  m_motor->SelectProfileSlot(0, 0);

  m_motor->Config_kF(0, 0.1528, 0);

  m_motor->SetNeutralMode(Brake);

  m_motor->ConfigMotionCruiseVelocity(6500, 0); //convert to talon speed: encoder count/100 ms / 2.0
  m_motor->ConfigMotionAcceleration(6500, 0); //9200

  m_motor->SetStatusFramePeriod(Status_2_Feedback0_, 10, 0);
  m_motor->SetStatusFramePeriod(Status_10_MotionMagic, 10, 0);

  m_motor->ConfigAllowableClosedloopError(0, 0, 0);

  m_motor->ConfigPeakCurrentDuration(0, 0);
  m_motor->ConfigContinuousCurrentLimit(30, 0);
  m_motor->EnableCurrentLimit(false);
  m_motor->ConfigPeakCurrentLimit(0, 0);
  m_motor->ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, 0, 0);

  m_desiredSetpoint = 0.0;
  m_hatchPosition = 0.0;
  m_isHatchZeroed = false;
}

void HatchSlide::setSetPoint(int value) {
  m_motor->Set(ControlMode::MotionMagic, value);
  m_desiredSetpoint = value;
  // m_motor->Set(ControlMode::MotionMagic, value, DemandType_ArbitraryFeedForward, m_motor->Config_kF(0, RobotParameters::k_feedForwardHatch + CommandBase::m_pLineFinder->getXVel() / 100, 0));
}

void HatchSlide::ZeroHatchPosition() {
  m_motor->SetSelectedSensorPosition(0, 0, 10);
  m_isHatchZeroed = true;
}

double HatchSlide::GetHatchPosition() {
  return m_motor->GetSelectedSensorPosition(0);
}

double HatchSlide::GetDesiredPos() {
  return m_desiredSetpoint;
}

int HatchSlide::ConvertInchesToTicks(double inches) {
  return inches * RobotParameters::k_ctreMagEncoderTicksPerRev / RobotParameters::k_beltCircumference;
}

void HatchSlide::Periodic() {
  frc::SmartDashboard::GetNumber("Lime Light Chain Dist: ", GetHatchPosition());
  SmartDashboard::PutNumber("belt x dist", CommandBase::m_pHatchSlide->GetHatchPosition());
}

void HatchSlide::InitDefaultCommand() {
  SetDefaultCommand(new HatchSlideGoToPosition());
}
