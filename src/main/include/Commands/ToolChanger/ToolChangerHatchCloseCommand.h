/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERHATCHCLOSECOMMAND
#define SRC_TOOLCHANGERHATCHCLOSECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/ToolChanger.h"

class ToolChangerHatchCloseCommand : public frc::InstantCommand {
 public:
  ToolChangerHatchCloseCommand() : InstantCommand("ToolChangerHatchCloseCommand"){
    Requires(CommandBase::m_pToolChanger.get());
  }
  void Initialize() override{
    CommandBase::m_pToolChanger->CloseHatch();
  }
};

#endif //SRC_TOOLCHANGERHATCHCLOSECOMMAND