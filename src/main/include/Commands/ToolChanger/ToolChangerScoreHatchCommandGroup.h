/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSCOREHATCHCOMMANDGROUP
#define SRC_TOOLCHANGERSCOREHATCHCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchRetractCommand.h"

class ToolChangerScoreHatchCommandGroup : public frc::CommandGroup {
 public:
  ToolChangerScoreHatchCommandGroup() : CommandGroup("ToolChangerScoreHatchCommandGroup") {
    // note: change for future once initial testing is done
    // AddParallel(new ToolChangerHoldCargoCommand());
    AddParallel(new ToolChangerHatchExtendCommand());
    // AddSequential(new ToolChangerHoldHatchCommand());
    AddSequential(new ToolChangerFreeCargoCommand());
    AddSequential(new ToolChangerFreeHatchCommand());
    AddSequential(new WaitCommand(0.3));
    AddSequential(new ToolChangerHoldCargoCommand());
    AddSequential(new ToolChangerHatchRetractCommand());
  }
};

#endif //SRC_TOOLCHANGERSCOREHATCHCOMMANDGROUP