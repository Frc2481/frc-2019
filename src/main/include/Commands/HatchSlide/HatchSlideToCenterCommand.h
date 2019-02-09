/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDETOCENTERCOMMAND
#define SRC_HATCHSLIDETOCENTERCOMMAND

#include <frc/commands/InstantCommand.h>
#include "Robot.h"
#include "Subsystems/HatchSlide.h"
#include "CommandBase.h"

class HatchSlideToCenterCommand : public frc::InstantCommand {
  int m_setPoint;
 public:
  HatchSlideToCenterCommand() : InstantCommand("HatchSlideToCenterCommand"){}
    void Initialize(){
    CommandBase::m_pHatchSlide->setSetPoint(0);
  }
};

#endif //SRC_HATCHSLIDETOCENTERCOMMAND