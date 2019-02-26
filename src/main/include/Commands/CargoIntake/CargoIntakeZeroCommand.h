/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEZEROCOMMAND
#define SRC_CARGOINTAKEZEROCOMMAND

#include "Subsystems/CargoIntake.h"
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class CargoIntakeZeroCommand : public frc::InstantCommand {
 public:
  CargoIntakeZeroCommand() : InstantCommand("CargoIntakeZeroCommand"){}
  void Initialize() override{
    CommandBase::m_pCargoIntake->ZeroCargoIntake();
  }
};

#endif //SRC_CARGOINTAKEZEROCOMMAND