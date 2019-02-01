/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMANDS_CARGOINTAKEACQUIREBALLCOMMANDGROUP_H
#define COMMANDS_CARGOINTAKEACQUIREBALLCOMMANDGROUP_H

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntakeBallCommand.h"
#include "Commands/CargoIntakeExtendCommand.h"
#include "Commands/CargoIntakeStopCommand.h"
#include "Commands/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntakeRetractCommand.h"
#include "CommandBase.h"

class CargoIntakeAcquireBallCommandGroup : public frc::CommandGroup {
 public:
  CargoIntakeAcquireBallCommandGroup() : CommandGroup("CargoIntakeAcquireBallCommandGroup") {
    AddParallel(new CargoIntakeBallCommand(0)); //change speed
    AddSequential(new CargoIntakeExtendCommand());
    AddSequential(new CargoIntakeWaitForBallCommand());
    AddParallel(new CargoIntakeRetractCommand());
    AddSequential(new CargoIntakeStopCommand());
  }
};

#endif //COMMANDS_CARGOINTAKEACQUIREBALLCOMMANDGROUP_H