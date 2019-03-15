/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERSETPOSITIONCOMMAND
#define SRC_CLIMBERSETPOSITIONCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ClimberSetPositionCommand : public frc::Command {
  private:
  double m_pos;
 public:
  ClimberSetPositionCommand(double pos) : Command("ClimberSetPositionCommand") {
    Requires(CommandBase::m_pClimber.get());
    m_pos = pos;
  }
  void Initialize() override {
    CommandBase::m_pClimber->SetPosition(m_pos);
  }
  bool IsFinished() override {
    return CommandBase::m_pClimber->IsOnTarget();
  }
};

#endif //SRC_CLIMBERSETPOSITIONCOMMAND