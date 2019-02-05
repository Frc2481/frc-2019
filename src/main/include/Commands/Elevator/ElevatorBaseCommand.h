/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORBASECOMMAND
#define SRC_ELEVATORBASECOMMAND

#include <frc/commands/Command.h>
#include "Subsystems/Elevator.h"
#include "Subsystems/ToolChanger.h"
#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"
#include "RobotParameters.h"

template <int CARGO_HEIGHT,int HATCH_HEIGHT>
class ElevatorBaseCommand : public frc::Command {
 public:
  ElevatorBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
    if(CommandBase::m_pToolChanger->HasCargo() && IsPositionSetPointAllowed(CARGO_HEIGHT)) {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT);
    }
  }
  
  bool IsFinished() override {
    return fabs(CommandBase::m_pElevator->GetElevatorError()) < 1;
  }

  bool IsPositionSetPointAllowed(int pos) {
    // if not in (back & in) OR (front & out), return true
    if(!(((CommandBase::m_pElevator->GetElevatorSlidePosition() == CommandBase::m_pElevator->BACK) && !CommandBase::m_pCargoIntake->IsExtended()) || 
        ((CommandBase::m_pElevator->GetElevatorSlidePosition() == CommandBase::m_pElevator->FRONT) && CommandBase::m_pCargoIntake->IsExtended()))) {
      return true;
    }
    //if (back & in) OR (front & out) & (current and setpoint above max) OR (current and setpoint below min), move freely
    else if((CommandBase::m_pElevator->GetElevatorPosition() > RobotParameters::k_elevatorCollisionMax 
          && pos > RobotParameters::k_elevatorCollisionMax) || 
          (CommandBase::m_pElevator->GetElevatorPosition() < RobotParameters::k_elevatorCollisionMin 
          && pos < RobotParameters::k_elevatorCollisionMin)) {
        return true;
    }
    else {
      return false;
    }
  }
};

template <int CARGO_HEIGHT, int HATCH_HEIGHT>
class ElevatorBaseCommandGroup : public CommandGroup {
  public:
  ElevatorBaseCommandGroup(std::string name) : CommandGroup(name) {
    AddSequential(new ElevatorBaseCommand<CARGO_HEIGHT, HATCH_HEIGHT>(name));
  }
}; 

typedef ElevatorBaseCommandGroup<0, 0> ElevatorHighCommand; //TODO
typedef ElevatorBaseCommandGroup<0, 0> ElevatorMidCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorLowCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorCargoShipCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorStowCommand; //keep both values here as zero

#endif //SRC_ELEVATORBASECOMMAND