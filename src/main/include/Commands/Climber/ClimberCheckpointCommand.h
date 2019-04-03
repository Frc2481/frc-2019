/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERCHECKPOINTCOMMAND
#define SRC_CLIMBERCHECKPOINTCOMMAND

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "CommandBase.h"

class ClimberCheckpointCommand : public frc::Command {
 public:
  ClimberCheckpointCommand() : Command("ClimberCheckpointCommand") {}
  bool IsFinished() override {
    return CommandBase::m_pOI->GetDriverStick()->GetRawButton(XBOX_BACK_BUTTON) &&
           CommandBase::m_pOI->GetDriverStick()->GetRawButton(XBOX_X_BUTTON);
  }
};

#endif //SRC_CLIMBERCHECKPOINTCOMMAND