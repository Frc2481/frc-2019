/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERZEROCOMMAND
#define SRC_CLIMBERZEROCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberZeroCommand : public frc::InstantCommand {
 public:
  ClimberZeroCommand() : InstantCommand("ClimberZeroCommand"){
    SetRunWhenDisabled(true);
  }
  void Initialize() override {
    CommandBase::m_pClimber->ZeroClimber();
  }
};

#endif //SRC_CLIMBERZEROCOMMAND