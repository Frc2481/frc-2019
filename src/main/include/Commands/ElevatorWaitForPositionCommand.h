/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMAND_ELEVATOR_WAIT_FOR_POSITION_COMMAND
#define COMMAND_ELEVATOR_WAIT_FOR_POSITION_COMMAND

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"

class ElevatorWaitForPositionCommand : public frc::Command {
 public:
  ElevatorWaitForPositionCommand() : Command("ElevatorWaitForPositionCommand") {}
  bool IsFinished() override {
    return fabs(CommandBase::m_pElevator->GetElevatorError()) < 1;
  }
};

#endif // COMMAND_ELEVATOR_WAIT_FOR_POSITION_COMMAND