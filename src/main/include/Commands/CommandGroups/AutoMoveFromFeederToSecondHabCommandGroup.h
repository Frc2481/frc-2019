/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOMOVEFROMFEEDERTOSECONDHABCOMMANDGROUP
#define SRC_AUTOMOVEFROMFEEDERTOSECONDHABCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainDriveAndRotateCommand.h"

class AutoMoveFromFeederToSecondHabCommandGroup : public frc::CommandGroup {
 public:
  AutoMoveFromFeederToSecondHabCommandGroup() : CommandGroup("AutoMoveFromFeederToSecondHabCommandGroup"){
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2.1, 0.25, 0.7, 0.4, 270.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
  }
};

#endif //SRC_AUTOMOVEFROMFEEDERTOSECONDHABCOMMANDGROUP