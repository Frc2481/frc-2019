/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_HATCH_SLIDE_TO_CENTER_H
#define COMMANDS_HATCH_SLIDE_TO_CENTER_H

#include <frc/commands/InstantCommand.h>
#include "Robot.h"
#include "Subsystems/HatchSlide.h"
#include "Subsystems/LineFinder.h"
#include "CommandBase.h"

class HatchSlideToCenterCommand : public frc::InstantCommand {
  int m_setPoint;
 public:
  HatchSlideToCenterCommand(int setPoint) : m_setPoint(setPoint){}
    void Initialize(){
    CommandBase::m_pHatchSlide->setSetPoint(0);
  }
};

#endif