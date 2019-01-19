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
  private:
  bool m_isOnTarget;

 public:
  ElevatorBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
    m_isOnTarget = false;
    CommandBase::m_pElevator->SetElevatorPosition(HEIGHT);
  }
  void Execute() override {}
  bool IsFinished() override {
    m_isOnTarget = fabs(CommandBase::m_pElevator->GetElevatorError()) < 0.5;
    return m_isOnTarget;
  }
  void End() override {}
  void Interrupted()override {
    End();
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