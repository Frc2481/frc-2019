/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_STOPALLCOMMAND
#define SRC_STOPALLCOMMAND
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class StopAllCommand : public frc::InstantCommand {
 public:
  StopAllCommand() : InstantCommand("StopAllCommand"){}
  void Initialize() override {
    CommandBase::m_pElevator->SetOpenLoopSpeed(0);
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0);
    CommandBase::m_pCargoIntake->SetSpeedIn(0);
    frc::Scheduler::GetInstance()->RemoveAll();
  }
};

#endif //SRC_STOPALLCOMMAND