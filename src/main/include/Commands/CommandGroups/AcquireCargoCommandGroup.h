/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ACQUIRECARGOCOMMANDGROUP
#define SRC_ACQUIRECARGOCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeStopCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForCargoIntakenCommand.h"
#include "Commands/HatchSlide/HatchSlideEnableCommand.h"
#include "Commands/HatchSlide/HatchSlideToCenterCommand.h"
#include "Commands/SetLEDsCommand.h"
#include "Commands/Elevator/ElevatorWaitForPositionCommand.h"
#include "Commands/CargoIntake/CargoIntakeExtensionCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    Requires(CommandBase::m_pElevator.get());
    Requires(CommandBase::m_pCargoIntake.get());
    Requires(CommandBase::m_pHatchSlide.get());

    //set up for command - hatch slide center
    AddParallel(new HatchSlideDisableCommand());
    AddParallel(new HatchSlideToCenterCommand());
    AddParallel(new ToolChangerFreeHatchCommand());
    AddParallel(new ToolChangerRetractCommand());
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
    // AddSequential(new WaitCommand(0.35));

    //intake out
    AddSequential(new CargoIntakeExtendCommand());
    AddSequential(new WaitCommand(0.75));
    AddSequential(new ToolChangerFreeCargoCommand());

    //intake ball
    AddParallel(new CargoIntakeBallCommand(0.8));
    AddSequential(new CargoIntakeWaitForCargoIntakenCommand());
    AddSequential(new WaitCommand(0.5));
    AddParallel(new CargoIntakeBallCommand(0.3));
    AddSequential(new CargoIntakeRetractCommand());
    AddSequential(new CargoIntakeWaitForBallCommand(), 0.75);
    AddParallel(new CargoIntakeStopCommand());
    AddParallel(new ToolChangerHoldCargoCommand());
    AddSequential(new WaitCommand(0.1));

    //leds & elevator back down
    AddParallel(new SetLEDsCommand(5));
    AddParallel(new ToolChangerSetHasCargoCommand(true));

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP