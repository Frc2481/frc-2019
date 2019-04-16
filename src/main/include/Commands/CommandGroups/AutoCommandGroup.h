/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOCOMMANDGROUP
#define SRC_AUTOCOMMANDGROUP
#include <frc/commands/CommandGroup.h>
#include "Commands/CommandGroups/AutoLegCargoToHatchCommandGroup.h"
#include "Commands/LimeLight/AutoLimeLightDriverDriveCommand.h"
#include "Commands/CommandGroups/AutoScoreHatchCommandGroup.h"
#include "Commands/CommandGroups/AutoMoveFromFeederToSecondHabCommandGroup.h"
#include "Commands/CommandGroups/AutoLv2ToAlignForHatchPlacementCommandGroup.h"
#include "Commands/LimeLight/LimeLightWaitForTargetSeenCommand.h"
#include "CommandBase.h"
class AutoCommandGroup : public frc::CommandGroup {
 public:
  AutoCommandGroup() : CommandGroup("AutoCommandGroup"){
    AddParallel(new AutoLv2ToAlignForHatchPlacementCommandGroup());
    AddSequential(new LimeLightWaitForTargetSeenCommand());
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.1, 0.2, 0.0, 0.0, 270.0));
    AddSequential(new AutoScoreHatchCommandGroup());
    // AddSequential(new AutoLegCargoToHatchCommandGroup());
    // AddSequential(new AutoAquireHatchCommandGroup(true));
    // AddSequential(new AutoMoveFromFeederToSecondHabCommandGroup());
    // AddSequential(new AutoScoreHatchCommandGroup());
  }
};

#endif //SRC_AUTOCOMMANDGROUP