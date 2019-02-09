/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEEJECTCOMMAND
#define SRC_CARGOINTAKEEJECTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"

class CargoIntakeEjectCommand : public frc::InstantCommand {
 private:
  double m_speed;
 public:
  CargoIntakeEjectCommand(double speed) : InstantCommand("CargoIntakeEjectCommand") {
    m_speed = speed;
  }
  void Initialize() override {
    CommandBase::m_pCargoIntake->SetSpeedOut(m_speed);
  }
};

#endif // SRC_CARGOINTAKEEJECTCOMMAND