/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ACQUIREHATCHCOMMANDGROUP
#define SRC_ACQUIREHATCHCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/ToolChanger/ToolChangerSetHasHatchCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"

class AcquireHatchCommandGroup : public frc::CommandGroup {
 public:
  AcquireHatchCommandGroup() : CommandGroup("AcquireHatchCommandGroup") {
    AddParallel(new ToolChangerSetHasHatchCommand(true));
    AddParallel(new ToolChangerFreeHatchCommand());
    AddSequential(new ElevatorLowCommand("ElevatorLowCommand"));
    AddSequential(new ToolChangerHatchExtendCommand());
    
    AddSequential(new WaitCommand(0.1)); //shrink as we become confident
    AddSequential(new ToolChangerHoldHatchCommand());
    AddSequential(new WaitCommand(0.1)); //shrink as we become confident
    AddSequential(new ToolChangerFreeCargoCommand());

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Free
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_ACQUIREHATCHCOMMANDGROUP