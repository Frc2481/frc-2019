/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOLVL2TOALIGNFORHATCHPLACEMENTCOMMANDGROUP
#define SRC_AUTOLVL2TOALIGNFORHATCHPLACEMENTCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"
#include "Commands/CommandGroups/AutoMoveFromFeederToSecondHabCommandGroup.h"
class AutoLv2ToAlignForHatchPlacementCommandGroup : public frc::CommandGroup {
 public:
  AutoLv2ToAlignForHatchPlacementCommandGroup() : CommandGroup("AutoLv2ToAlignForHatchPlacementCommandGroup"){
    AddSequential(new InstantCommand([]() {CommandBase::m_pSwerveDrivetrain->setGyroOffset(180);}));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(1.2, 0.0, 1.0, 0.0, 270.0));
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.5, -0.2, 1.0, 0.4, 270.0));
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2, -0.2, 0.5, 0.4, 270.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
  }
};

#endif //SRC_AUTOLVL2TOALIGNFORHATCHPLACEMENTCOMMANDGROUP