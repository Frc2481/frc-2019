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
  m_encoder(new rev::CANEncoder(*m_climberMotor)),
  m_pidController(m_climberMotor->GetPIDController()) {
  
  m_climberMotor->RestoreFactoryDefaults();

  m_climberBigFootSolenoid = new frc::DoubleSolenoid(CLIMBER_BIG_FOOT_SOLENOID);
  m_climberLittleFeetSolenoid = new frc::DoubleSolenoid(CLIMBER_LITTLE_FEET_SOLENOID);
  m_climberGuidesSolenoid = new frc::DoubleSolenoid(CLIMBER_GUIDES_SOLENOID);
  m_weightsSolenoid = new frc::Solenoid(CLIMBER_WEIGHTS_SOLENOID);

  m_pidController.SetP(0);
  m_pidController.SetI(0);
  m_pidController.SetD(0);
  m_pidController.SetFF(0);

  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitFwdEn, 0);
  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitRevEn, 0);

  // m_pidController.SetOutputRange(0, 0); //TODO
  // m_pidController.SetReference(0, rev::ControlType::kVelocity);

  m_climberMotor->SetSmartCurrentLimit(200);

  m_bigFootActivated = false;
  m_littleFeetActivated = false;

  m_climberBigFootSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_climberLittleFeetSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_climberManualActivated = false;
}
void Climber::Periodic(){
  frc::SmartDashboard::PutNumber("Climber Position", GetPos());
  frc::SmartDashboard::PutNumber("Climber Speed", GetSpeed());
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
void Climber::ActivateLittleFeet() {
  m_climberLittleFeetSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_littleFeetActivated = true;
}
void Climber::DeactivateLittleFeet() {
  m_climberLittleFeetSolenoid->Set(frc::DoubleSolenoid::kReverse);
  m_littleFeetActivated = false;
}
void Climber::ActivateBigFoot() {
  m_climberBigFootSolenoid->Set(frc::DoubleSolenoid::kReverse);
  m_bigFootActivated = true;
}
void Climber::DeactivateBigFoot() {
  m_climberBigFootSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_bigFootActivated = false;
}
bool Climber::IsBigFootToggleActivated() {
  return m_bigFootActivated;
}
bool Climber::IsLittleFeetToggleActivated() {
  return m_littleFeetActivated;
}
void Climber::ActivateBigFootToggle() {
  m_bigFootActivated = true;
}
void Climber::DeactivateBigFootToggle() {
  m_bigFootActivated = false;
}
bool Climber::IsBigFootTilted() {
  return m_bigFootActivated;
}
void Climber::ActivateLittleFeetToggle() {
  m_littleFeetActivated = true;
}
void Climber::DeactivateLittleFeetToggle() {
  m_littleFeetActivated = false;
}
void Climber::SetOpenLoopSpeed(double speed) {
  m_climberMotor->Set(speed);
}
double Climber::GetSpeed(){
  return m_climberMotor->Get();
}
double Climber::GetPos(){
  return m_encoder->GetPosition();
}
void Climber::ZeroClimber(){
  m_encoder->SetPosition(0.0); //is this right???
}
void Climber::RetractGuides(){
  m_climberGuidesSolenoid->Set(frc::DoubleSolenoid::kReverse);
}
void Climber::ExtendGuides(){
  m_climberGuidesSolenoid->Set(frc::DoubleSolenoid::kForward);//TODO check if correct
}
void Climber::ReleaseWeights() {
  m_weightsSolenoid->Set(true);
}
void Climber::EnableClimberManual(){
  m_climberManualActivated = true;
}
void Climber::DisableClimberManual(){
  m_climberManualActivated = false;
}
bool Climber::IsClimberEnabled(){
  return m_climberManualActivated;
}