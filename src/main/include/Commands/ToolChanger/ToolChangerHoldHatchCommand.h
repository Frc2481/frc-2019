/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERHOLDHATCHCOMMAND
#define SRC_TOOLCHANGERHOLDHATCHCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerHoldHatchCommand : public frc::InstantCommand {
 public:
  ToolChangerHoldHatchCommand() : InstantCommand("ToolChangerHoldHatchCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override{
    CommandBase::m_pToolChanger->HoldHatch();
  }
};

#endif //SRC_TOOLCHANGERHOLDHATCHCOMMAND