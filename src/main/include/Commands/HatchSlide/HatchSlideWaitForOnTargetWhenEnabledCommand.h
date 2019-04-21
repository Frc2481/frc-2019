/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEWAITFORONTARGETWHENENABLEDCOMMAND
#define SRC_HATCHSLIDEWAITFORONTARGETWHENENABLEDCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class HatchSlideWaitForOnTargetWhenEnabledCommand : public frc::Command {
 public:
  HatchSlideWaitForOnTargetWhenEnabledCommand() : Command("HatchSlideWaitForOnTargetWhenEnabledCommand") {}
  bool IsFinished() override {
    if(CommandBase::m_pHatchSlide->IsHatchSlideUserEnabled()) {
      return CommandBase::m_pHatchSlide->IsSlideOnTarget();
    }
    else {
      return true;
    }
  }
};

#endif //SRC_HATCHSLIDEWAITFORONTARGETWHENENABLEDCOMMAND