/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKERETRACTCOMMAND
#define SRC_CARGOINTAKERETRACTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"

class CargoIntakeRetractCommand : public frc::InstantCommand {
 public:
  CargoIntakeRetractCommand() : InstantCommand("CargoIntakeRetractCommand") {}
  void Initialize() override {
    if(CommandBase::m_pCargoIntake->IsExtended() && IsPositionSetPointAllowed()) {
      Wait(0); //TODO: change amount of time for timeout
      CommandBase::m_pCargoIntake->Retract();
    }
  }

  bool IsPositionSetPointAllowed() {
    if(CommandBase::m_pElevator->GetElevatorPosition() > RobotParameters::k_intakeCollisionHeight)
      return true;
    else
      return false;  
  }  
};

#endif //SRC_CARGOINTAKERETRACTCOMMAND