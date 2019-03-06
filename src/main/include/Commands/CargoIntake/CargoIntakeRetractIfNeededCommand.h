/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKERETRACTIFNEEDEDCOMMAND
#define SRC_CARGOINTAKERETRACTIFNEEDEDCOMMAND

#include <frc/commands/ConditionalCommand.h>
#include "CommandBase.h"
#include "Commands/CommandGroups/RevertElevatorTestingCommandGroup.h"

class CargoIntakeRetractIfNeededCommand : public frc::ConditionalCommand {
 public:
  CargoIntakeRetractIfNeededCommand() : frc::ConditionalCommand("CargoIntakeRetractIfNeededCommand",
       new RevertElevatorTestingCommandGroup(), nullptr) {}
  bool Condition() {
    return CommandBase::m_pCargoIntake->IsIntakeOut();
  }
};

#endif //SRC_CARGOINTAKERETRACTIFNEEDEDCOMMAND