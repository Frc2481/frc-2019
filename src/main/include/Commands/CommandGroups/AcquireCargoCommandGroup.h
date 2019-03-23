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
#include "Commands/CargoIntake/CargoIntakeWaitForCargoIntakenCommand.h"
#include "Commands/CommandGroups/ConditionalIntakeCommandGroup.h"
#include "Commands/HatchSlide/HatchSlideEnableCommand.h"
#include "Commands/HatchSlide/HatchSlideToCenterCommand.h"
#include "Commands/SetLEDsCommand.h"

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
    AddSequential(new WaitCommand(0.5));
    AddSequential(new ToolChangerFreeCargoCommand());

    //elevator up to allow intake out - conditional & only moves elevator & intake when needed
    AddSequential(new ExtendIntakeIfNeededCommand()); //TODO check to see if height is acceptable

    //prep for intaking ball - move height
    AddSequential(new ToolChangerRetractCommand());
    AddSequential(new ElevatorPreIntakeBallHeightCommand("ElevatorPreIntakeBallHeightCommand", false));

    //intake ball
    AddSequential(new CargoIntakeBallCommand(1));
    AddSequential(new CargoIntakeWaitForCargoIntakenCommand());
    AddSequential(new CargoIntakeBallCommand(0.6));
    AddSequential(new CargoIntakeWaitForBallCommand());
    AddSequential(new CargoIntakeStopCommand());
    AddSequential(new ToolChangerHoldCargoCommand());
    AddSequential(new WaitCommand(0.1));

    //move elevator up to allow intake in
    AddSequential(new ElevatorIntakeBallHeightCommand("ElevatorIntakeBallHeightCommand", false)); //TODO check to see if height is acceptable
    AddSequential(new CargoIntakeInCommand("CargoIntakeBackCommand"));

    //leds & elevator back down
    AddParallel(new SetLEDsCommand(5));
    AddSequential(new ElevatorCargoLowCommand("ElevatorCargoLowCommand"));
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