/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Climber.h"
#include "Commands/Climber/ClimberDriveWithJoystickCommand.h"

Climber::Climber() : Subsystem("Climber"),  
  m_climberMotor(new rev::CANSparkMax(CLIMBER_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless)),
  m_pidController(m_climberMotor->GetPIDController()) {
  
  m_climberMotor->RestoreFactoryDefaults();

  m_climberSolenoid = new frc::DoubleSolenoid(CLIMBER_SOLENOID);

  // m_pidController.SetFF(0); //TODO
  // m_pidController.SetP(0);
  // m_pidController.SetI(0);
  // m_pidController.SetD(0);

  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitFwdEn, 0);
  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitRevEn, 0);

  // m_pidController.SetOutputRange(0, 0); //TODO
  // m_pidController.SetReference(0, rev::ControlType::kVelocity);

  m_climberMotor->SetSmartCurrentLimit(200);

  m_feetActivated = false;

  m_climberSolenoid->Set(frc::DoubleSolenoid::kReverse);
}

void Climber::InitDefaultCommand() {
  SetDefaultCommand(new ClimberDriveWithJoystickCommand());
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
void Climber::ActivateFeet() {
  m_climberSolenoid->Set(frc::DoubleSolenoid::kReverse);
}
void Climber::DeactivateFeet() {
  m_climberSolenoid->Set(frc::DoubleSolenoid::kForward);
}
bool Climber::IsFootToggleActivated() {
  return m_feetActivated;
}
void Climber::ActivateFootToggle() {
  m_feetActivated = true;
}
void Climber::DeactivateFootToggle() {
  m_feetActivated = false;
}
void Climber::SetOpenLoopSpeed(double speed) {
  m_climberMotor->Set(speed);
}