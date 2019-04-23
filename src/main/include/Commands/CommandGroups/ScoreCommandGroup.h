/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SCORECOMMANDGROUP
#define SRC_SCORECOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include <frc/commands/ConditionalCommand.h>
#include "CommandBase.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"

class ScoreHatchCommandGroup : public frc::CommandGroup {
 public:
  ScoreHatchCommandGroup() : CommandGroup("ScoreHatchCommandGroup") {
    AddSequential(new ToolChangerFreeCargoCommand());
    AddSequential(new WaitCommand(0.1));
    AddSequential(new ToolChangerFreeHatchCommand());
    AddSequential(new WaitCommand(0.6)); //1.5
    AddSequential(new ToolChangerHoldCargoCommand());
    AddSequential(new ToolChangerSetHasCargoCommand(false));
    AddSequential(new ToolChangerSetHasHatchCommand(false));
  }
};

class ScoreCargoCommandGroup : public frc::CommandGroup {
 public:
  ScoreCargoCommandGroup() : CommandGroup("ScoreCargoCommandGroup") {
    AddSequential(new ToolChangerFreeCargoCommand());
    AddSequential(new ToolChangerHatchExtendCommand());
    AddSequential(new WaitCommand(0.3));
    // AddSequential(new ToolChangerHatchRetractCommand());
    AddSequential(new ToolChangerSetHasCargoCommand(false));
    AddSequential(new ToolChangerSetHasHatchCommand(false));
  }
};

class ScoreCommand : public frc::ConditionalCommand {
 public:
  ScoreCommand() : ConditionalCommand("ScoreCommand", new ScoreHatchCommandGroup(), new ScoreCargoCommandGroup()) {}
  bool Condition() {
    return CommandBase::m_pToolChanger->HasHatch();
  }
};
#endif //SRC_SCORECOMMANDGROUP