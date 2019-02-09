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
#include "Commands/CargoIntake/CargoIntakeExtendCommand.h"
#include "Commands/CargoIntake/CargoIntakeStopCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerCargoCloseCommand.h"
#include "Commands/ToolChanger/ToolChangerCargoOpenCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    AddParallel(new ToolChangerCargoOpenCommand());
    AddSequential(new ElevatorMidCommand("ElevatorMidCommand"));
    AddParallel(new CargoIntakeBallCommand(0)); //TODO: change speed
    AddSequential(new CargoIntakeExtendCommand());
    AddSequential(new CargoIntakeWaitForBallCommand());
    AddParallel(new CargoIntakeRetractCommand());
    AddSequential(new ElevatorLowCommand("ElevatorLowCommand"));
    AddParallel(new CargoIntakeStopCommand());
    AddSequential(new ToolChangerCargoCloseCommand());
    AddParallel(new ToolChangerSetHasCargoCommand(true));
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP