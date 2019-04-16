/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOLEGCARGOTOHATCHCOMMANDGROUP
#define SRC_AUTOLEGCARGOTOHATCHCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainDriveAndRotateCommand.h"

class AutoLegCargoToHatchCommandGroup : public frc::CommandGroup {
 public:
  AutoLegCargoToHatchCommandGroup() : CommandGroup("AutoLegCargoToHatchCommandGroup"){
      AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
      AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2.3, -0.35, -0.8, 0.4, 180.0));
      AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
  }
};

#endif //SRC_AUTOLEGCARGOTOHATCHCOMMANDGROUP