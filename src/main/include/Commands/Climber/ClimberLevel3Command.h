/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERLEVEL3COMMAND
#define SRC_CLIMBERLEVEL3COMMAND
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberLevel3Command : public frc::InstantCommand {
 public:
  ClimberLevel3Command() : InstantCommand("ClimberLevel3Command") {

  }
  void Initialize() override {
    CommandBase::m_pClimber->ClimberLevel3();
  }
};

#endif //SRC_CLIMBERLEVEL3COMMAND