/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERRAISECOMMAND
#define SRC_CLIMBERRAISECOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ClimberRaiseCommand : public frc::Command {
 public:
  ClimberRaiseCommand() : Command("ClimberRaiseCommand"){}
  void Execute() override{
      CommandBase::m_pClimber->SetOpenLoopSpeed(0.8);
  }
  bool IsFinished() override{
    return false;
  }
  void End() override{
    CommandBase::m_pClimber->SetOpenLoopSpeed(0.0);
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_CLIMBERRAISECOMMAND