/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERTOGGLELITTLEFEETCOMMAND
#define SRC_CLIMBERTOGGLELITTLEFEETCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberToggleLittleFeetCommand : public frc::InstantCommand {
 public:
  ClimberToggleLittleFeetCommand() : InstantCommand("ClimberToggleLittleFeetCommand") {}
  void Initialize() override {
    if(CommandBase::m_pClimber->IsLittleFeetToggleActivated()) {
      CommandBase::m_pClimber->DeactivateLittleFeet();
    }
    else {
      CommandBase::m_pClimber->ActivateLittleFeet();
    }
  }
};


class ClimberLittleFeetDownCommand : public frc::InstantCommand {
 public:
  ClimberLittleFeetDownCommand() : InstantCommand("ClimberLittleFeetDownCommand") {}
  void Initialize() override {
      CommandBase::m_pClimber->DeactivateLittleFeet();
  }
};


class ClimberLittleFeetUpCommand : public frc::InstantCommand {
 public:
  ClimberLittleFeetUpCommand() : InstantCommand("ClimberLittleFeetUpCommand") {}
  void Initialize() override {
      CommandBase::m_pClimber->ActivateLittleFeet();
  }
};
#endif //SRC_CLIMBERTOGGLELITTLEFEETCOMMAND