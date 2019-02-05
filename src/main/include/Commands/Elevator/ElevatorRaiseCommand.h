/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORRAISECOMMAND
#define SRC_ELEVATORRAISECOMMAND

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"
#include "CommandBase.h"

class ElevatorRaiseCommand : public frc::Command {
 public:
  ElevatorRaiseCommand() : Command("ElevatorRaiseCommand") {
      Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
      CommandBase::m_pElevator->SetOpenLoopSpeed(0.75);
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

#endif //SRC_ELEVATORRAISECOMMAND