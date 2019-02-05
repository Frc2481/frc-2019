/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEWAITFORONTARGETCOMMAND
#define SRC_HATCHSLIDEWAITFORONTARGETCOMMAND
#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"
#include "CommandBase.h"

class HatchSlideWaitForOnTargetCommand : public frc::Command {
 public:
  HatchSlideWaitForOnTargetCommand() : Command("HatchSlideWaitForOnTargetCommand") {}
  bool IsFinished() override {
    if(CommandBase::m_pHatchSlide->IsHatchSlideEnabled()) {
      CommandBase::m_pHatchSlide->IsSlideOnTarget();
    }
  }
};

#endif // SRC_HATCHSLIDEWAITFORONTARGETCOMMAND