/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/ToolChanger.h"

ToolChanger::ToolChanger() : Subsystem("ExampleSubsystem") {
  m_changer = new frc::Solenoid(TOOL_CHANGER);
  m_isHatchFront = true;
  
}

void ToolChanger::InitDefaultCommand() {
  
}

void ToolChanger::SwitchToHatch() {
  m_changer->Set(true); //potentially reverse
  m_isHatchFront = true;
}

void ToolChanger::SwitchToCargo() {
  m_changer->Set(false); //potentially reverse
  m_isHatchFront = false;
}

bool ToolChanger::IsHatchToolFront() {
  return m_isHatchFront; //potentially reverse
}

