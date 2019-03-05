/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDETOGGLECOMMAND
#define SRC_HATCHSLIDETOGGLECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class HatchSlideToggleCommand : public frc::InstantCommand {
 public:
  HatchSlideToggleCommand() : InstantCommand("HatchSlideToggleCommand"){}
  void Initialize() override{
    if(CommandBase::m_pHatchSlide->IsHatchSlideEnabled()){
      CommandBase::m_pHatchSlide->DisableHatchSlide();
    }
    else{
      CommandBase::m_pHatchSlide->EnableHatchSlide();
    }
  }
};

#endif //SRC_HATCHSLIDETOGGLECOMMAND