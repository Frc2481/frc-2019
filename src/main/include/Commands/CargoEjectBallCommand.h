/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef CARGO_EJECT_BALL_COMMAND
#define CARGO_EJECT_BALL_COMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/CargoIntake.h"

class CargoEjectBallCommand : public frc::InstantCommand {
 private:
  double m_speed;
 public:
  CargoEjectBallCommand(double speed) : InstantCommand("CargoEjectBallCommand") {
    m_speed = speed;
  }
  void Initialize() override {
    CommandBase::m_pCargoIntake->SetSpeedOut(m_speed);
  }
};

#endif // CARGO_EJECT_BALL_COMMAND