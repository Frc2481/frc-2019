/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERWAITFORHATCHCOMMAND
#define SRC_TOOLCHANGERWAITFORHATCHCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ToolChangerWaitForHatchCommand : public frc::Command {
 public:
  ToolChangerWaitForHatchCommand() : Command("ToolChangerWaitForHatchCommand") {}
  bool IsFinished() override {
    return CommandBase::m_pHatchSlide->IsHatchSeen();
  }
};

#endif //SRC_TOOLCHANGERWAITFORHATCHCOMMAND