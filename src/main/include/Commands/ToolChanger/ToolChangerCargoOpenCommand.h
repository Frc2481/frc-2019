/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERCARGOOPENCOMMAND
#define SRC_TOOLCHANGERCARGOOPENCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/ToolChanger.h"

class ToolChangerCargoOpenCommand : public frc::InstantCommand {
 public:
  ToolChangerCargoOpenCommand() : InstantCommand("ToolChangerCargoOpenCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override {
    CommandBase::m_pToolChanger->OpenCargo();
  }
};

#endif //SRC_TOOLCHANGERCARGOOPENCOMMAND