/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERLEVEL2COMMAND
#define SRC_CLIMBERLEVEL2COMMAND
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberLevel2Command : public frc::InstantCommand {
 public:
  ClimberLevel2Command() : InstantCommand("ClimberLevel2Command") {

  }
  void Initialize() override {
    CommandBase::m_pClimber->ClimberLevel2();
  }
};

#endif //SRC_CLIMBERLEVEL2COMMAND