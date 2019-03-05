/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERRETRACTCOMMAND
#define SRC_TOOLCHANGERRETRACTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerRetractCommand : public frc::InstantCommand {
 public:
  ToolChangerRetractCommand() : InstantCommand("ToolChangerRetractCommand") {
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override {
    CommandBase::m_pToolChanger->RetractHatch();
  }
};

#endif //SRC_TOOLCHANGERRETRACTCOMMAND