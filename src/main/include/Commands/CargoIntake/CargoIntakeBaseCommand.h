/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEBASECOMMAND
#define SRC_CARGOINTAKEBASECOMMAND

#include <frc/commands/Command.h>
#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"
#include "RobotParameters.h"

template <int INTAKE_POS>
class CargoIntakeBaseCommand : public frc::Command {
 public:
  CargoIntakeBaseCommand(std::string name) : Command(name) {
    Requires(CommandBase::m_pCargoIntake.get());
  }
  void Initialize() override {
    if(IsPositionSetPointAllowed(INTAKE_POS)) {
      CommandBase::m_pCargoIntake->SetPosition(INTAKE_POS);
    }
  }
  
  bool IsFinished() override {
    return fabs(CommandBase::m_pCargoIntake->IsOnTarget());
  }

  bool IsPositionSetPointAllowed(int pos) {
    //if elevator in protected zone, don't move
    if(CommandBase::m_pElevator->IsPositionInProtectedZone(CommandBase::m_pElevator->GetElevatorPosition())) {
      return false;
    }
    else {
      return true;
    }
  }

  void End() override {
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0); //slide
  }
  void Interrupted() override {
    End();
  }
};

template <int INTAKE_POS>
class CargoIntakeBaseCommandGroup : public CommandGroup {
  public:
  CargoIntakeBaseCommandGroup(std::string name) : CommandGroup(name) {
    // AddSequential(new ElevatorRiseForIntakeCommand());
    AddSequential(new CargoIntakeBaseCommand<INTAKE_POS>(name));
  }
}; 

typedef CargoIntakeBaseCommandGroup<17700> CargoIntakeOutCommand;
typedef CargoIntakeBaseCommandGroup<0> CargoIntakeInCommand;

#endif //SRC_CARGOINTAKEBASECOMMAND