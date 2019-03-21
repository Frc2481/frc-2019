/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEENABLECOMMAND
#define SRC_HATCHSLIDEENABLECOMMAND

#include <frc/commands/Command.h>
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class HatchSlideEnableCommand : public frc::Command {
 public:
  HatchSlideEnableCommand() : frc::Command("HatchSlideEnableCommand") {}
  void Initialize() override {
    CommandBase::m_pHatchSlide->EnableUserHatchSlide();
  }
  void End() override{
    CommandBase::m_pHatchSlide->DisableUserHatchSlide();
  }
  bool IsFinished() override {
    return false;
  }
  void Interrupted() override {
    End();
  }
};

class HatchSlideDisableCommand : public frc::InstantCommand {
 public:
  HatchSlideDisableCommand() : frc::InstantCommand("HatchSlideDisableCommand") {}
  void Initialize() override {
    CommandBase::m_pHatchSlide->DisableUserHatchSlide();
  }
};

#endif //SRC_HATCHSLIDEENABLECOMMAND