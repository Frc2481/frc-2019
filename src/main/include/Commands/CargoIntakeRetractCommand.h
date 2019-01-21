/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_CARGO_INTAKE_RETRACT_COMMAND_H
#define COMMANDS_CARGO_INTAKE_RETRACT_COMMAND_H

#include <frc/commands/InstantCommand.h>
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"

class CargoIntakeRetractCommand : public frc::InstantCommand {
 public:
  CargoIntakeRetractCommand() : InstantCommand("CargoIntakeRetractCommand") {}
  void Initialize() override {
    CommandBase::m_pCargoIntake->Retract();
  }
};

#endif //COMMANDS_CARGO_INTAKE_RETRACT_COMMAND_H