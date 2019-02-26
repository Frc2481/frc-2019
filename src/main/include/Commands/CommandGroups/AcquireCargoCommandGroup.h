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
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeStopCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForNoBallCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    AddSequential(new ToolChangerSetHasCargoCommand(true));
    AddSequential(new ToolChangerFreeHatchCommand());
    AddSequential(new ToolChangerRetractCommand());
    AddSequential(new ToolChangerFreeCargoCommand());
    AddSequential(new ElevatorMidCommand("ElevatorMidCommand"));
    AddSequential(new CargoIntakeOutCommand("CargoIntakeFrontCommand"));
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
    AddSequential(new CargoIntakeBallCommand(1));
    AddSequential(new CargoIntakeWaitForBallCommand());
    AddSequential(new WaitCommand(0.1));
    AddSequential(new CargoIntakeBallCommand(0.3));
    AddSequential(new ToolChangerHoldCargoCommand());
    AddSequential(new WaitCommand(0.1));
    AddSequential(new CargoIntakeBallCommand(0.1));
    AddSequential(new CargoIntakeWaitForNoBallCommand());
    AddSequential(new ElevatorMidCommand("ElevatorMidCommand"));
    AddSequential(new CargoIntakeStopCommand());
    AddSequential(new CargoIntakeInCommand("CargoIntakeBackCommand"));
    AddSequential(new ElevatorCargoLowCommand("ElevatorCargoLowCommand"));

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP