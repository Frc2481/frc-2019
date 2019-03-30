/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERHATCHRETRACTCOMMAND
#define SRC_TOOLCHANGERHATCHRETRACTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerHatchRetractCommand : public frc::InstantCommand {
 public:
  ToolChangerHatchRetractCommand() : InstantCommand("ToolChangerHatchRetractCommand") {}
  void Initialize() override {
    CommandBase::m_pToolChanger->RetractHatch();
  }
};

#endif //SRC_TOOLCHANGERHATCHRETRACTCOMMAND