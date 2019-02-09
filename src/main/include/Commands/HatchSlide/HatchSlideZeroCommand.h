/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEZEROCOMMAND
#define SRC_HATCHSLIDEZEROCOMMAND

#include "CommandBase.h"
#include "Subsystems/HatchSlide.h"

class HatchSlideZeroCommand : public frc::Command {
 public:
  HatchSlideZeroCommand() : Command("HatchSlideZeroCommand") {
    SetRunWhenDisabled(true);
  }
  void Initialize() {
    CommandBase::m_pHatchSlide->ZeroHatchPosition();
  }

  bool IsFinished() {
    return true;
  }
  void Interrupted() {
    End();
  }
};

#endif //SRC_HATCHSLIDEZEROCOMMAND