/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMAND_VIBRATE_COMMAND_H
#define COMMAND_VIBRATE_COMMAND_H

#include <frc/commands/Command.h>
#include "CommandBase.h"
#include <frc/WPILib.h>

class VibrateCommand : public frc::Command {
 public:
  VibrateCommand() : Command("VibrateCommand"){
    SetTimeout(1);
  }
  void Initialize(){
    CommandBase::m_pOI->m_pDriverStick->SetRumble(GenericHID::RumbleType::kLeftRumble, 1);
		CommandBase::m_pOI->m_pDriverStick->SetRumble(GenericHID::RumbleType::kRightRumble, 1);
  }
  void Execute(){}
  bool IsFinished(){
    IsTimedOut();
  }
  void End(){
    CommandBase::m_pOI->m_pDriverStick->SetRumble(GenericHID::RumbleType::kLeftRumble, 0);
		CommandBase::m_pOI->m_pDriverStick->SetRumble(GenericHID::RumbleType::kRightRumble, 0);
  }
  void Interrupted(){
    End();
  }
};

#endif //COMMAND_VIBRATE_COMMAND_H