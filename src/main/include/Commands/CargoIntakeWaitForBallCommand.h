/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_CARGO_INTAKE_WAIT_FOR_BALL_COMMAND_H
#define COMMANDS_CARGO_INTAKE_WAIT_FOR_BALL_COMMAND_H

#include <frc/commands/Command.h>
#include "Subsystems/CargoIntake.h"

class CargoIntakeWaitForBallCommand : public frc::Command {
 public:
  CargoIntakeWaitForBallCommand() : Command("CargoIntakeWaitForBallCommand"){}
  bool IsFinished() override {
    //fill with whatever we decide to use to detect ball
  }
};

#endif //COMMANDS_CARGO_INTAKE_WAIT_FOR_BALL_COMMAND_H