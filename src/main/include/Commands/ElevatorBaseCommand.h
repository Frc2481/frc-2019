/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_ELEVATOR_BASE_COMMAND_H
#define COMMANDS_ELEVATOR_BASE_COMMAND_H

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"
#include "CommandGroup.h"

template <double HEIGHT>
class ElevatorBaseCommand : public frc::Command {
 public:
  ElevatorBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
    CommandBase::m_pElevator->SetElevatorPosition(HEIGHT);
  }
  bool IsFinished() override {
    return fabs(CommandBase::m_pElevator->GetElevatorError()) < 0.5;
  }
};

template <double HEIGHT>
class ElevatorBaseCommandGroup() : public CommandGroup {
  public:
  ElevatorBaseCommandGroup(std::string name) : CommandGroup(name) {
    AddSequential(new ElevatorBaseCommand(HEIGHT));
  }
} 

typedef ElevatorBaseCommandGroup<0> ElevatorToLevelThreeCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorToLevelTwoCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorToLevelOneCommand;

#endif COMMANDS_ELEVATOR_BASE_COMMAND_H