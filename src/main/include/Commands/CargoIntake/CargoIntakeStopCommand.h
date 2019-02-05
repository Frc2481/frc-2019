/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKESTOPCOMMAND
#define SRC_CARGOINTAKESTOPCOMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"

class CargoIntakeStopCommand : public frc::InstantCommand {
 public:
  CargoIntakeStopCommand() : InstantCommand("CargoIntakeStopCommand") {}
  void Initialize() override {
    CommandBase::m_pCargoIntake->StopIntake();
  }
};

#endif //SRC_CARGOINTAKESTOPCOMMAND