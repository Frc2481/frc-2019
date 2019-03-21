/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDESETSETPOINTCOMMAND
#define SRC_HATCHSLIDESETSETPOINTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class HatchSlideSetSetpointCommand : public frc::InstantCommand {
  private:
  double m_setPoint;
 public:
  HatchSlideSetSetpointCommand(double pos) : InstantCommand("HatchSlideSetSetpointCommand"){
    Requires(CommandBase::m_pHatchSlide.get());
    m_setPoint = pos;
  }
    void Initialize(){
    CommandBase::m_pHatchSlide->setSetPoint(CommandBase::m_pHatchSlide->ConvertInchesToTicks(m_setPoint));
  }
};

#endif //SRC_HATCHSLIDESETSETPOINTCOMMAND