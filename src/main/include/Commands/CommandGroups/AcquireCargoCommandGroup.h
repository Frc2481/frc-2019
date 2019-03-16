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
#include "Commands/CargoIntake/CargoIntakeWaitForNoBallCommand.h"
#include "Commands/CommandGroups/ConditionalIntakeCommandGroup.h"
#include "Commands/HatchSlide/HatchSlideEnableCommand.h"
#include "Commands/HatchSlide/HatchSlideToCenterCommand.h"
#include "Commands/SetLEDsCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    if(!CommandBase::m_pHatchSlide->IsCargoLimitSwitchHit()) {
      AddParallel(new HatchSlideDisableCommand());
      AddParallel(new HatchSlideToCenterCommand());
      AddParallel(new ToolChangerFreeHatchCommand());
      AddSequential(new WaitCommand(0.5));
      AddSequential(new ToolChangerFreeCargoCommand());
      AddSequential(new ExtendIntakeIfNeededCommand()); //TODO check to see if height is acceptable
      AddSequential(new ToolChangerRetractCommand());
      AddSequential(new ElevatorPreIntakeBallHeightCommand("ElevatorPreIntakeBallHeightCommand", false));
      AddSequential(new CargoIntakeBallCommand(1));
      AddSequential(new CargoIntakeWaitForBallCommand());
      AddSequential(new CargoIntakeStopCommand());
      AddSequential(new ToolChangerHoldCargoCommand());
      AddSequential(new ElevatorIntakeBallHeightCommand("ElevatorIntakeBallHeightCommand")); //TODO check to see if height is acceptable
      AddSequential(new CargoIntakeInCommand("CargoIntakeBackCommand"));
      AddSequential(new ElevatorCargoLowCommand("ElevatorCargoLowCommand"));
      AddParallel(new ToolChangerSetHasCargoCommand(true));
      AddSequential(new SetLEDsCommand(false));
    }

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP