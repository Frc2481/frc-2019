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
#include "Commands/CommandGroups/RetractIntakeIfNeededCommandGroup.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"

template <int CARGO_HEIGHT, int HATCH_HEIGHT>
class ElevatorBaseCommand : public frc::Command {
 public:
  ElevatorBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
    if(HATCH_HEIGHT < 7 && !CommandBase::m_pToolChanger->HasHatch()) {
      CommandBase::m_pToolChanger->ExtendHatch();
    }
    if(CommandBase::m_pToolChanger->HasCargo() && IsPositionSetPointAllowed(CARGO_HEIGHT)) {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT, true);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT, true);
    } else if(IsPositionSetPointAllowed(HATCH_HEIGHT)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT, true);
    }
  }
  
  bool IsFinished() override {
    printf("checking is finished\n");
    return CommandBase::m_pElevator->IsOnTarget();
  }

  bool IsPositionSetPointAllowed(int pos) {
    //if traveling through protected zone while cargoIntake out, don't allow movement
    if(CommandBase::m_pCargoIntake->IsIntakeInProtectedZone() &&
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
    SmartDashboard::PutNumber("ElevatorExecutionTime", TimeSinceInitialized());
  }

  void Interrupted() {
    End();
  }
};

template <int CARGO_HEIGHT, int HATCH_HEIGHT>
class ElevatorBaseCommandGroup : public CommandGroup {
  public:
  ElevatorBaseCommandGroup(std::string name, bool safeIntakeRetract = true) : CommandGroup(name) {
    if(safeIntakeRetract) {
      AddSequential(new RetractIntakeIfNeededCommand());
    }
    AddSequential(new ElevatorBaseCommand<CARGO_HEIGHT, HATCH_HEIGHT>(name), 3.0);
  }
}; 

typedef ElevatorBaseCommandGroup<3, 3> ElevatorPreIntakeBallHeightCommand;
typedef ElevatorBaseCommandGroup<24, 24> ElevatorIntakeBallHeightCommand;
typedef ElevatorBaseCommandGroup<68, 65> ElevatorHighCommand; //67 cargo height
typedef ElevatorBaseCommandGroup<40, 36> ElevatorMidCommand;
typedef ElevatorBaseCommandGroup<11, 6> ElevatorLowCommand;
typedef ElevatorBaseCommandGroup<9, 9> ElevatorCargoLowCommand;
typedef ElevatorBaseCommandGroup<9, 3> ElevatorCargoShipCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorStowCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorIntakePosCommand;

#endif //SRC_ELEVATORBASECOMMAND