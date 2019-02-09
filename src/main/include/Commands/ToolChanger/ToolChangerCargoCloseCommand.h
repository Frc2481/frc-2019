/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERCARGOCLOSECOMMAND
#define SRC_TOOLCHANGERCARGOCLOSECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/ToolChanger.h"

class ToolChangerCargoCloseCommand : public frc::InstantCommand {
 public:
  ToolChangerCargoCloseCommand() : InstantCommand("ToolChangerCargoCloseCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override{
    CommandBase::m_pToolChanger->CloseCargo();
  }
};

#endif //SRC_TOOLCHANGERCARGOCLOSECOMMAND