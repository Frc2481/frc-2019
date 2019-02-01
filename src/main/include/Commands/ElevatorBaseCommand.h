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
#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"

template <int HEIGHT>
class ElevatorBaseCommand : public frc::Command {
 public:
  ElevatorBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
    CommandBase::m_pElevator->SetElevatorPosition(HEIGHT);
  }
  bool IsFinished() override {
    return fabs(CommandBase::m_pElevator->GetElevatorError()) < 1;
  }
};

template <int HEIGHT>
class ElevatorBaseCommandGroup : public CommandGroup {
  public:
  ElevatorBaseCommandGroup(std::string name) : CommandGroup(name) {
    AddSequential(new ElevatorBaseCommand<HEIGHT>(name));
  }
}; 

typedef ElevatorBaseCommandGroup<0> ElevatorHighHatchCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorMidHatchCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorLowHatchCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorHighCargoCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorMidCargoCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorLowCargoCommand;
typedef ElevatorBaseCommandGroup<0> ElevatorCargoShipCommand;

#endif //COMMANDS_ELEVATOR_BASE_COMMAND_H