/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSCORECARGOCOMMANDGROUP
#define SRC_TOOLCHANGERSCORECARGOCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"

class ToolChangerScoreCargoCommandGroup : public frc::CommandGroup {
 public:
  ToolChangerScoreCargoCommandGroup() : CommandGroup("ToolChangerScoreCargoCommandGroup") {
    // note: change for future once initial testing is done
    AddSequential(new ToolChangerHatchExtendCommand());
    AddSequential(new WaitCommand(0.3));
    AddSequential(new ToolChangerHoldCargoCommand());
    AddSequential(new ToolChangerRetractCommand());
  }
};

#endif //SRC_TOOLCHANGERSCORECARGOCOMMANDGROUP