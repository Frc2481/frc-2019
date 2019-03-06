/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORWAITFORPOSITIONCOMMAND
#define SRC_ELEVATORWAITFORPOSITIONCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ElevatorWaitForPositionCommand : public frc::Command {
 public:
  ElevatorWaitForPositionCommand() : Command("ElevatorWaitForPositionCommand") {}
  bool IsFinished() override {
    return fabs(CommandBase::m_pElevator->GetElevatorError()) < 1;
  }
};

#endif // SRC_ELEVATORWAITFORPOSITIONCOMMAND