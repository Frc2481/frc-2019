/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_ELEVATORLOWERCOMMAND_H
#define COMMANDS_ELEVATORLOWERCOMMAND_H

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"
#include "CommandBase.h"

class ElevatorLowerCommand : public frc::Command {
 public:
  ElevatorLowerCommand() : Command("ElevatorLowerCommand") {
      Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
      CommandBase::m_pElevator->SetOpenLoopSpeed(-0.75);
  }
  void End() override {
      CommandBase::m_pElevator->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
  bool IsFinished() override {
    return false;
  }
};

#endif //COMMANDS_ELEVATORLOWERCOMMAND_H