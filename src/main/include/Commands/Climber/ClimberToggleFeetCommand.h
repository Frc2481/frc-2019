/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERTOGGLEFEETCOMMAND
#define SRC_CLIMBERTOGGLEFEETCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberToggleFeetCommand : public frc::InstantCommand {
 public:
  ClimberToggleFeetCommand() : InstantCommand("ClimberToggleFeetCommand") {}
  void Initialize() override {
    if(CommandBase::m_pClimber->IsFootToggleActivated()) {
      CommandBase::m_pClimber->DeactivateFeet();
      CommandBase::m_pClimber->DeactivateFootToggle();
    }
    else {
      CommandBase::m_pClimber->ActivateFeet();
      CommandBase::m_pClimber->ActivateFootToggle();
    }
  }
};

#endif //SRC_CLIMBERTOGGLEFEETCOMMAND