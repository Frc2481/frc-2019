/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ACQUIREHATCHCOMMANDGROUP
#define SRC_ACQUIREHATCHCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"
#include "Commands/ToolChanger/ToolChangerSetHasHatchCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"

class AcquireHatchCommandGroup : public frc::CommandGroup {
 public:
  AcquireHatchCommandGroup() : CommandGroup("AcquireHatchCommandGroup") {
    AddParallel(new ToolChangerSetHasHatchCommand(true));
    AddSequential(new ElevatorLowCommand("ElevatorLowCommand"));
    AddSequential(new ToolChangerHatchExtendCommand());
    AddSequential(new ToolChangerHoldHatchCommand());
    AddSequential(new ToolChangerRetractCommand());
  }
};

#endif //SRC_ACQUIREHATCHCOMMANDGROUP