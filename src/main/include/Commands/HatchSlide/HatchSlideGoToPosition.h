/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEGOTOPOSITION
#define SRC_HATCHSLIDEGOTOPOSITION

#include <frc/commands/InstantCommand.h>
#include "Robot.h"
#include "CommandBase.h"
#include "OI.h"

class HatchSlideGoToPosition : public frc::InstantCommand {
  int m_setPoint;
  public:
    HatchSlideGoToPosition() : InstantCommand("HatchSlideGoToPosition") {
      Requires(CommandBase::m_pHatchSlide.get());
    }
    void Initialize() {
      m_setPoint = CommandBase::m_pHatchSlide->ConvertInchesToTicks(-CommandBase::m_pHatchSlide->GetBrightPulseDist());

      if(CommandBase::m_pOI->GetOperatorStick()->GetRawButton(XBOX_RIGHT_BUMPER)) {
        if(CommandBase::m_pHatchSlide->GetBrightPulseDist() > CommandBase::m_pHatchSlide->GetDimPulseDist()) {
          m_setPoint = CommandBase::m_pHatchSlide->ConvertInchesToTicks(-CommandBase::m_pHatchSlide->GetDimPulseDist());
        }
      }

      if(CommandBase::m_pHatchSlide->IsLineVisible() && CommandBase::m_pHatchSlide->IsHatchSlideEnabled()) {
        CommandBase::m_pHatchSlide->setSetPoint(m_setPoint);
      }
      else {
        CommandBase::m_pHatchSlide->setSetPoint(0);
      }
    }
};

#endif //SRC_HATCHSLIDEGOTOPOSITION