/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Climber.h"

Climber::Climber() : Subsystem("Climber"),  m_pidController(m_climber->GetPIDController()) {
  m_climber = new rev::CANSparkMax{CLIMBER, rev::CANSparkMax::MotorType::kBrushless};

  m_pidController.SetFF(0); //TODO
  m_pidController.SetP(0);
  m_pidController.SetI(0);
  m_pidController.SetD(0);

  m_climber->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitFwdEn, 0);
  m_climber->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitRevEn, 0);

  m_pidController.SetOutputRange(0, 0); //TODO
  m_pidController.SetReference(0, rev::ControlType::kVelocity);

  m_climber->SetSmartCurrentLimit(0);
}

void Climber::InitDefaultCommand() {

}

void Climber::ClimberRetract() {
  m_pidController.SetReference(ConvertInchesToTicks(0), rev::ControlType::kPosition, 0);
}
void Climber::ClimberLevel2() {
  m_pidController.SetReference(ConvertInchesToTicks(0), rev::ControlType::kPosition, 0);
}
void Climber::ClimberLevel3() {
  m_pidController.SetReference(ConvertInchesToTicks(0), rev::ControlType::kPosition, 0);
}
double Climber::ConvertInchesToTicks(int inches) {
  return inches * RobotParameters::k_climberTicksPerInch;
}