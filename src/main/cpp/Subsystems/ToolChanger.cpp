/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ToolChanger.h"

ToolChanger::ToolChanger() : Subsystem("ToolChanger") {
  m_hatchTool = new frc::Solenoid(HATCH_TOOL);
  m_cargoTool = new frc::Solenoid(CARGO_TOOL);

  m_limitSwitch = new frc::DigitalInput(TOOL_CHANGER_LIMIT_SWITCH);

  m_isHatchToolOpen = false;
  m_isCargoToolOpen = false; 
  m_hasCargo = false;
  m_hasHatch = false;
}

void ToolChanger::InitDefaultCommand() {
  
}

void ToolChanger::OpenHatch(){
  m_hatchTool->Set(true);
  m_isHatchToolOpen = true;
}
void ToolChanger::CloseHatch(){
  m_hatchTool->Set(false);
  m_isHatchToolOpen = false;
}
void ToolChanger::OpenCargo(){
  m_cargoTool->Set(true);
  m_isCargoToolOpen = true;
}
void ToolChanger::CloseCargo(){
  m_cargoTool->Set(false);
  m_isCargoToolOpen = false;
}
bool ToolChanger::IsHatchToolOpen(){
  return m_isHatchToolOpen;
}
bool ToolChanger::IsCargoToolOpen(){
  return m_isCargoToolOpen;
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

bool ToolChanger::GetIsLimitSwitchTriggered() {
  return m_limitSwitch->Get();
}