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
    if(((HATCH_HEIGHT / 10.0) < 3 || (CARGO_HEIGHT / 10.0) < 3) && CommandBase::m_pCargoIntake->IsIntakeIn()) {
      CommandBase::m_pToolChanger->ExtendHatch();
    }
    if(CommandBase::m_pToolChanger->HasCargo() && IsPositionSetPointAllowed(CARGO_HEIGHT / 10.0)) {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT / 10.0, true);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT / 10.0)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT / 10.0, true);
    } else if(IsPositionSetPointAllowed(HATCH_HEIGHT / 10.0)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT / 10.0, true);
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
    if(CommandBase::m_pToolChanger->HasCargo() && IsPositionSetPointAllowed(CARGO_HEIGHT / 10.0)) {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT / 10.0, false);
    }
    else if(CommandBase::m_pToolChanger->HasHatch() && IsPositionSetPointAllowed(HATCH_HEIGHT / 10.0)){
      CommandBase::m_pElevator->SetElevatorPosition(HATCH_HEIGHT / 10.0, false);
    } else {
      CommandBase::m_pElevator->SetElevatorPosition(CARGO_HEIGHT / 10.0, false);
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
    if(safeIntakeRetract) {
      AddSequential(new RetractIntakeIfNeededCommand());
    }
  }
}; 

typedef ElevatorBaseCommandGroup<25, 25> ElevatorPreIntakeBallHeightCommand;
typedef ElevatorBaseCommandGroup<300, 300> ElevatorIntakeBallHeightCommand;
typedef ElevatorBaseCommandGroup<680, 650> ElevatorHighCommand; //67 cargo height
typedef ElevatorBaseCommandGroup<400, 360> ElevatorMidCommand;
typedef ElevatorBaseCommandGroup<110, 60> ElevatorLowCommand;
typedef ElevatorBaseCommandGroup<90, 90> ElevatorCargoLowCommand;
typedef ElevatorBaseCommandGroup<300, 30> ElevatorCargoShipCommand;
typedef ElevatorBaseCommandGroup<0, 0> ElevatorStowCommand;
typedef ElevatorBaseCommandGroup<3, 3> ElevatorIntakePosCommand;

#endif //SRC_ELEVATORBASECOMMAND