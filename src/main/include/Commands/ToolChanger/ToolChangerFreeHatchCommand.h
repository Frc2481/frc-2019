/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERFREEHATCHCOMMAND
#define SRC_TOOLCHANGERFREEHATCHCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerFreeHatchCommand : public frc::InstantCommand {
 public:
  ToolChangerFreeHatchCommand() : InstantCommand("ToolChangerFreeHatchCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override{
    CommandBase::m_pToolChanger->FreeHatch();
  }
};

#endif //SRC_TOOLCHANGERFREEHATCHCOMMAND