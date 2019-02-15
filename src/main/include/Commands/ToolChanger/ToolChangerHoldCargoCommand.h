/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERHOLDCARGOCOMMAND
#define SRC_TOOLCHANGERHOLDCARGOCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/ToolChanger.h"

class ToolChangerHoldCargoCommand : public frc::InstantCommand {
 public:
  ToolChangerHoldCargoCommand() : InstantCommand("ToolChangerHoldCargoCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override {
    CommandBase::m_pToolChanger->HoldCargo();
  }
};

#endif //SRC_TOOLCHANGERHOLDCARGOCOMMAND