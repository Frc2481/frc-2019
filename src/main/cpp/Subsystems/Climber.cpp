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

  m_pidController = m_climberMotor->GetPIDController();
  
  m_climberMotor->RestoreFactoryDefaults();

  m_climberBigFootSolenoid = new frc::DoubleSolenoid(CLIMBER_BIG_FOOT_SOLENOID);
  m_climberLittleFeetSolenoid = new frc::DoubleSolenoid(CLIMBER_LITTLE_FEET_SOLENOID);
  m_climberGuidesSolenoid = new frc::DoubleSolenoid(CLIMBER_GUIDES_SOLENOID);
  m_weightsSolenoid = new frc::Solenoid(CLIMBER_WEIGHTS_SOLENOID);

  m_pidController.SetP(0);
  m_pidController.SetI(0);
  m_pidController.SetD(0);
  m_pidController.SetFF(1/4000.0);
  m_pidController.SetOutputRange(-1, 1);

  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitFwdEn, 0);
  // m_climberMotor->SetParameter(rev::CANSparkMax::ConfigParameter::kSoftLimitRevEn, 0);

  // m_pidController.SetOutputRange(0, 0); //TODO
  // m_pidController.SetReference(0, rev::ControlType::kVelocity);

  m_pidController.SetSmartMotionMaxAccel(12000);
  m_pidController.SetSmartMotionMaxVelocity(4000);
  m_pidController.SetSmartMotionAllowedClosedLoopError(0);
  m_pidController.SetSmartMotionMinOutputVelocity(0);

  m_climberMotor->SetSmartCurrentLimit(200);

  m_bigFootActivated = false;
  m_littleFeetActivated = false;

  m_climberBigFootSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_climberLittleFeetSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_climberGuidesSolenoid->Set(frc::DoubleSolenoid::kReverse);
  m_weightsSolenoid->Set(false);

  m_isClimberZeroed = false;
  m_areClimberGuidesExtended = false;
  m_desiredSetpoint = 0;
}
void Climber::Periodic(){
  static int loopCounter = -1;
  loopCounter++;
  loopCounter %= 3;
  if (loopCounter == 0) {
    frc::SmartDashboard::PutNumber("Climber Position", GetPos());
  }
  else if (loopCounter == 1) {
    frc::SmartDashboard::PutNumber("Climber Speed", GetSpeed());
  }
  else if (loopCounter == 2) {
    frc::SmartDashboard::PutNumber("Climber sensor speed", m_encoder->GetVelocity());
  }
}
void Climber::InitDefaultCommand() {
  // SetDefaultCommand(new ClimberDriveWithJoystickCommand());
}
void Climber::SetPosition(double setPoint) {
  m_pidController.SetReference(setPoint, rev::ControlType::kSmartMotion);
  m_desiredSetpoint = setPoint;
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
bool Climber::IsBigFootTilted() {
  return m_bigFootActivated;
}
void Climber::SetOpenLoopSpeed(double speed) {
  m_climberMotor->Set(speed);
}
double Climber::GetSpeed(){
  return m_climberMotor->Get();
}
double Climber::GetSensorSpeed(){
  return m_encoder->GetVelocity();
}
double Climber::GetPos(){
  return m_encoder->GetPosition();
}
double Climber::GetDesiredPos(){
  return m_desiredSetpoint;
}
void Climber::ZeroClimber(){
  m_encoder->SetPosition(0.0); //TODO is this right???
  m_isClimberZeroed = true;
}
void Climber::ExtendGuides(){
  m_climberGuidesSolenoid->Set(frc::DoubleSolenoid::kForward);
  m_areClimberGuidesExtended = true;
}

void Climber::RetractGuides(){
  m_climberGuidesSolenoid->Set(frc::DoubleSolenoid::kReverse);
  m_areClimberGuidesExtended = false;
}
bool Climber::IsGuidesExtended(){
  return m_areClimberGuidesExtended;
}
void Climber::ReleaseWeights() {
  m_weightsSolenoid->Set(true);
}
void Climber::ResetWeights() {
  m_weightsSolenoid->Set(false);
}
bool Climber::IsClimberZeroed(){
  return m_isClimberZeroed;
}
bool Climber::IsOnTarget() {
  return fabs(GetPos() - GetDesiredPos()) < 10;
}