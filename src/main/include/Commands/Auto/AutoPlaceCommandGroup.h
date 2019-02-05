/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOPLACECOMMANDGROUP
#define SRC_AUTOPLACECOMMANDGROUP
#include <frc/commands/CommandGroup.h>
#include "Commands/HatchSlide/HatchSlideWaitForOnTargetCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerWaitForReleaseCommand.h"
#include "Commands/ToolChanger/ToolChangerScoreCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"

class AutoPlaceCommandGroup : public frc::CommandGroup {
 public:
  AutoPlaceCommandGroup(Command* elevatorBaseCommand) : CommandGroup("AutoPlaceCommandGroup") {
    Requires(CommandBase::m_pElevator.get());
    Requires(CommandBase::m_pToolChanger.get());

    AddSequential(elevatorBaseCommand);
    AddSequential(new HatchSlideWaitForOnTargetCommand());
    AddSequential(new ToolChangerScoreCommand());
    AddSequential(new ToolChangerWaitForReleaseCommand());
    AddSequential(new ToolChangerRetractCommand());
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
  }
};

#endif // SRC_AUTOPLACECOMMANDGROUP