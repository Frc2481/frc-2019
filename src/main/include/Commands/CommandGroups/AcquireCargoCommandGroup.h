/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ACQUIRECARGOCOMMANDGROUP
#define SRC_ACQUIRECARGOCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeStopCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    AddParallel(new ToolChangerHoldCargoCommand());
    AddSequential(new ElevatorMidCommand("ElevatorMidCommand"));
    AddSequential(new ToolChangerFreeCargoCommand());
    AddParallel(new CargoIntakeBallCommand(0)); //TODO: change speed
    AddSequential(new CargoIntakeFrontCommand("CargoIntakeFrontCommand"));
    AddSequential(new CargoIntakeWaitForBallCommand());
    AddParallel(new CargoIntakeBackCommand("CargoIntakeBackCommand"));
    AddSequential(new ElevatorLowCommand("ElevatorLowCommand"));
    AddParallel(new CargoIntakeStopCommand());
    AddSequential(new ToolChangerHoldCargoCommand());
    AddParallel(new ToolChangerSetHasCargoCommand(true));
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP