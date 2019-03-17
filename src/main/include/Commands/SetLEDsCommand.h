/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SETLEDSCOMMAND
#define SRC_SETLEDSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class SetLEDsCommand : public frc::Command {
  private:
    int m_blinkCount;
    int m_currBlinkCount;
  public:
  SetLEDsCommand(int blinkCount) : Command("SetLEDsCommand") {
    m_blinkCount = blinkCount;
  }
  void Initialize() override {
    m_currBlinkCount = 1;
  }
  void Execute() override {
    if(TimeSinceInitialized() < 0.2 * m_currBlinkCount - 0.1) {
      CommandBase::m_pHatchSlide->SetLEDs(true);
    }
    else if(TimeSinceInitialized() < 0.2 * m_currBlinkCount) {
      CommandBase::m_pHatchSlide->SetLEDs(false);
    } else {
      m_currBlinkCount++;
    }
  }
  bool IsFinished() override {
    return m_currBlinkCount >= m_blinkCount;
  }
  void End() override {
    CommandBase::m_pHatchSlide->SetLEDs(false);
  }
};

#endif //SRC_SETLEDSCOMMAND