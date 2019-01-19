/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMAND_ELEVATOR_HOME_COMMAND
#define COMMAND_ELEVATOR_HOME_COMMAND 

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"

class ElevatorHomeCommand : public frc::Command {
 private:

 public:
  ElevatorHomeCommand() : Command("ElevatorHomeCommand"){
    }
  void Initialize() override {
    CommandBase::m_pElevator->Set(ControlMode::PercentOutput, -0.75); //might need to change direction
  }
  void Execute() override {}
  bool IsFinished() override {
    return CommandBase::m_pElevator->IsRevLimitSwitchClosed();
  }
  void End() override {
   CommandBase::m_pElevator->Set(ControlMode::PercentOutput, 0); 
  }
  void Interrupted() override {
    End();
  }
};

#endif // COMMAND_ELEVATOR_HOME_COMMAND