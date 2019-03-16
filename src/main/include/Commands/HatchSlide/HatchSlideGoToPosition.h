/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEGOTOPOSITION
#define SRC_HATCHSLIDEGOTOPOSITION

#include <frc/commands/Command.h>
#include "Robot.h"
#include "CommandBase.h"
#include "OI.h"

class HatchSlideGoToPosition : public frc::Command {
  int m_setPoint;
  public:
    HatchSlideGoToPosition() : Command("HatchSlideGoToPosition") {}
    void Execute() {
      if(CommandBase::m_pHatchSlide->IsHatchSlideUserEnabled()) {
        m_setPoint = CommandBase::m_pHatchSlide->ConvertInchesToTicks(CommandBase::m_pHatchSlide->GetBrightPulseDist() - 13);
        if(CommandBase::m_pHatchSlide->IsLineVisible() && CommandBase::m_pHatchSlide->isZeroed()) {
          CommandBase::m_pHatchSlide->setSetPoint(m_setPoint);
        }
        else if(CommandBase::m_pHatchSlide->isZeroed()) {
          CommandBase::m_pHatchSlide->setSetPoint(0);
        }
        SmartDashboard::PutNumber("hatch slide setpoint", m_setPoint);
      }
    }
    bool IsFinished() {
      return false;
    }
    void End() {
      CommandBase::m_pHatchSlide->DisableUserHatchSlide();
    }
    void Interrupted() {
      End();
    }
 };

#endif //SRC_HATCHSLIDEGOTOPOSITION