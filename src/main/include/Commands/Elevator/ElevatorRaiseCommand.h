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
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"
#include "RobotParameters.h"

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
    // if not in (back & in) OR (front & out), return true
    if(!(((CommandBase::m_pElevator->GetElevatorSlidePosition() == CommandBase::m_pElevator->BACK) && !CommandBase::m_pCargoIntake->IsExtended()) || 
        ((CommandBase::m_pElevator->GetElevatorSlidePosition() == CommandBase::m_pElevator->FRONT) && CommandBase::m_pCargoIntake->IsExtended()))) {
      return false;
    }    
    //if (back & in) OR (front & out) & (current and setpoint above max) OR (current and setpoint below min), move freely
    else if((CommandBase::m_pElevator->GetElevatorPosition() > RobotParameters::k_elevatorCollisionMax) || 
          (CommandBase::m_pElevator->GetElevatorPosition() < (RobotParameters::k_elevatorCollisionMin))) {
        return false;
    }
    else {
      return true;
    }
  }
};

#endif //SRC_ELEVATORRAISECOMMAND