/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORBASECOMMAND
#define SRC_ELEVATORBASECOMMAND

#include <frc/commands/Command.h>
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
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT, true);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT, true);
    } else {
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT, true);
    }
  }
  
  bool IsFinished() override {
    printf("checking is finished\n");
    return CommandBase::m_pElevator->IsOnTarget();
  }

  bool IsPositionSetPointAllowed(int pos) {
    //if traveling through protected zone while cargoIntake out, don't allow movement
    return true;
    if(CommandBase::m_pCargoIntake->IsIntakeOut() &&
          (CommandBase::m_pElevator->IsPositionInProtectedZone(CommandBase::m_pElevator->GetElevatorPosition()) ||
          CommandBase::m_pElevator->IsPositionInProtectedZone(pos))) {
      return false;
    }
    else {
      return true;
    }
  }

  void End() {
if(CommandBase::m_pToolChanger->HasCargo() && IsPositionSetPointAllowed(CARGO_HEIGHT)) {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT, false);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT, false);
    } else {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT, false);
    }
  }

  void Interrupted() {
    End();
  }
};

template <int CARGO_HEIGHT, int HATCH_HEIGHT>
class ElevatorBaseCommandGroup : public CommandGroup {
  public:
  ElevatorBaseCommandGroup(std::string name) : CommandGroup(name) {
    AddSequential(new ElevatorBaseCommand<CARGO_HEIGHT, HATCH_HEIGHT>(name), 3.0);
  }
}; 

typedef ElevatorBaseCommandGroup<84, 59> ElevatorHighCommand; // 27393, 25412
typedef ElevatorBaseCommandGroup<37, 31> ElevatorMidCommand; // 16075, 13180
typedef ElevatorBaseCommandGroup<9, 3> ElevatorLowCommand; // 3918, 1273
typedef ElevatorBaseCommandGroup<9, 9> ElevatorCargoLowCommand; // 3918, 3918
typedef ElevatorBaseCommandGroup<9, 3> ElevatorCargoShipCommand; // 3918, 1273
typedef ElevatorBaseCommandGroup<0, 0> ElevatorStowCommand;

#endif //SRC_ELEVATORBASECOMMAND