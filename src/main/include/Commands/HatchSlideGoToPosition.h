/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_HATCH_SLIDE_GO_TO_POSITION_H
#define COMMANDS_HATCH_SLIDE_GO_TO_POSITION_H

#include <frc/commands/InstantCommand.h>
#include "Robot.h"
#include "Subsystems/HatchSlide.h"
#include "CommandBase.h"

class HatchSlideGoToPosition : public frc::InstantCommand {
  int m_setPoint;
  public:
    HatchSlideGoToPosition() : InstantCommand("HatchSlideGoToPosition") {
      Requires(CommandBase::m_pHatchSlide.get());
    }
    void Initialize() {
      m_setPoint = CommandBase::m_pHatchSlide->ConvertInchesToTicks(-CommandBase::m_pHatchSlide->GetPulseDist());
      if(CommandBase::m_pHatchSlide->IsLineVisible()) {
        CommandBase::m_pHatchSlide->setSetPoint(m_setPoint);
      }
      else {
        CommandBase::m_pHatchSlide->setSetPoint(0);
      }
    }
};

#endif