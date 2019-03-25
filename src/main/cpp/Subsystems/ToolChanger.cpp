/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ToolChanger.h"

ToolChanger::ToolChanger() : Subsystem("ToolChanger") {
  m_hatchTool = new frc::DoubleSolenoid(HATCH_TOOL_SOLENOID);
  m_cargoTool = new frc::DoubleSolenoid(CARGO_TOOL_SOLENOID);
  m_hatchExtender = new frc::DoubleSolenoid(HATCH_EXTENDER_SOLENOID);
 
  m_capacitiveSensor = new frc::DigitalInput(TOOL_CHANGER_CAPACITIVE_SENSOR);

  m_hatchTool->Set(frc::DoubleSolenoid::kReverse); // held
  m_cargoTool->Set(frc::DoubleSolenoid::kReverse); // held
  m_hatchExtender->Set(frc::DoubleSolenoid::kReverse); // extended

  m_isHatchToolHeld = false;
  m_isCargoToolHeld = false; 
  m_hasCargo = false;
  m_hasHatch = true;
}

void ToolChanger::InitDefaultCommand() {
}
void ToolChanger::Periodic() {
  frc::SmartDashboard::PutBoolean("HasCargo", m_hasCargo);
  frc::SmartDashboard::PutBoolean("HasHatch", m_hasHatch);
}
void ToolChanger::HoldHatch(){
  m_hatchTool->Set(frc::DoubleSolenoid::kReverse);
  m_isHatchToolHeld = true;
}
void ToolChanger::FreeHatch(){
  m_hatchTool->Set(frc::DoubleSolenoid::kForward);
  m_isHatchToolHeld = false;
}
void ToolChanger::HoldCargo(){
  m_cargoTool->Set(frc::DoubleSolenoid::kReverse);
  m_isCargoToolHeld = true;
}
void ToolChanger::FreeCargo(){
  m_cargoTool->Set(frc::DoubleSolenoid::kForward);
  m_isCargoToolHeld = false;
}
void ToolChanger::ExtendHatch() {
  m_hatchExtender->Set(frc::DoubleSolenoid::kReverse);
  m_isHatchExtended = true;
}
void ToolChanger::RetractHatch() {
  m_hatchExtender->Set(frc::DoubleSolenoid::kForward);
  m_isHatchExtended = false;
}
bool ToolChanger::IsHatchToolHeld(){
  return m_isHatchToolHeld;
}
bool ToolChanger::IsCargoToolHeld(){
  return m_isCargoToolHeld;
}
bool ToolChanger::IsHatchExtended(){
  return m_isHatchExtended;
}
bool ToolChanger::HasCargo(){
  return m_hasCargo;
}
bool ToolChanger::HasHatch(){
  return m_hasHatch;
}
void ToolChanger::SetHasCargo(bool hasCargo){
  m_hasCargo = hasCargo;
  m_hasHatch = false;
}
void ToolChanger::SetHasHatch(bool hasHatch){
  m_hasHatch = hasHatch;
  m_hasCargo = false;
}