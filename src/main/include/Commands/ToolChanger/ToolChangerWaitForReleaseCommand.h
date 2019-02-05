/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERWAITFORRELEASECOMMAND
#define SRC_TOOLCHANGERWAITFORRELEASECOMMAND

#include <frc/commands/Command.h>
#include "Subsystems/ToolChanger.h"

class ToolChangerWaitForReleaseCommand : public frc::Command {
 public:
  ToolChangerWaitForReleaseCommand() : Command("ToolChangerWaitForReleaseCommand") {}
  bool IsFinished() override {
    return CommandBase::m_pToolChanger->GetIsLimitSwitchTriggered();
  }
};

#endif // SRC_TOOLCHANGERWAITFORRELEASECOMMAND