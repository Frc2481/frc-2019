/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEDISABLECOMMAND
#define SRC_HATCHSLIDEDISABLECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class HatchSlideDisableCommand : public frc::InstantCommand {
 public:
  HatchSlideDisableCommand() : frc::InstantCommand("HatchSlideDisableCommand") {}
  void Initialize() override {
    CommandBase::m_pHatchSlide->DisableHatchSlide();
  }
};

#endif //SRC_HATCHSLIDEDISABLECOMMAND