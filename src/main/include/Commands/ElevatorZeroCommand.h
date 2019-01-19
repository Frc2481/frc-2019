/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_ELEVATOR_ZERO_COMMAND
#define COMMANDS_ELEVATOR_ZERO_COMMAND

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"

class ElevatorZeroCommand : public frc::Command {
 public:
  ElevatorZeroCommand() : Command("ElevatorZeroCommand"){}
  void Initialize() override {
    CommandBase::m_pElevator->ZeroElevatorEncoder();
  }
  void Execute() override {}
  bool IsFinished() override {
    return true;
  }
  void End() override {}
  void Interrupted() override {
    End();
  }
};

#endif // COMMANDS_ELEVATOR_ZERO_COMMAND