/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBCOMMANDGROUP
#define SRC_CLIMBCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainDistance.h"
#include "Commands/Climber/ClimberRetractCommand.h"

class ClimbCommandGroup : public frc::CommandGroup {
 public:
  ClimbCommandGroup(Command* climbLevelCommand) : CommandGroup("ClimbCommandGroup"){
    AddSequential(climbLevelCommand);
    AddSequential(new SwerveDrivetrainDistance(2));
    AddSequential(new ClimberRetractCommand());
  }
};

#endif //SRC_CLIMBCOMMANDGROUP