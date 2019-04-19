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
#include "Commands/SwerveDrivetrain/AutoDriveAndRotateCommand.h"

class AutoMoveFromFeederToSecondHabCommandGroup : public frc::CommandGroup {
 public:
  AutoMoveFromFeederToSecondHabCommandGroup() : CommandGroup("AutoMoveFromFeederToSecondHabCommandGroup"){
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(1.3, 12.0, 0.4, 270.0, 1.0));
    AddSequential(new AutoDriveAndRotateCommand(1.5, 0.0, 0.4, 270.0, 0.5));
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2, -0.2, 0.5, 0.4, 270.0));
    // AddSequential(new AutoDriveAndRotateCommand(0.02, 0.01, -0.01, 0.0, 270.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
  }
};

#endif //SRC_AUTOMOVEFROMFEEDERTOSECONDHABCOMMANDGROUP