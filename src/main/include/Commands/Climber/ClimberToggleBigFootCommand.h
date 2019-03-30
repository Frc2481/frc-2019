/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERTOGGLEBIGFOOTCOMMAND
#define SRC_CLIMBERTOGGLEBIGFOOTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberToggleBigFootCommand : public frc::InstantCommand {
 public:
  ClimberToggleBigFootCommand() : InstantCommand("ClimberToggleBigFootCommand") {}
  void Initialize() override {
    if(CommandBase::m_pClimber->IsBigFootToggleActivated()) {
      CommandBase::m_pClimber->DeactivateBigFoot();
    }
    else {
      CommandBase::m_pClimber->ActivateBigFoot();
    }
  }
};


class ClimberUntiltBigFootCommand : public frc::InstantCommand {
 public:
  ClimberUntiltBigFootCommand() : InstantCommand("ClimberUntiltBigFootCommand") {}
  void Initialize() override {
      CommandBase::m_pClimber->DeactivateBigFoot();
  }
};


class ClimberTiltBigFootCommand : public frc::InstantCommand {
 public:
  ClimberTiltBigFootCommand() : InstantCommand("ClimberTiltBigFootCommand") {}
  void Initialize() override {
      CommandBase::m_pClimber->ActivateBigFoot();
  }
};

#endif //SRC_CLIMBERTOGGLEBIGFOOTCOMMAND