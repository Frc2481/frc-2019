/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ROCKETAUTOCOMMANDGROUP
#define SRC_ROCKETAUTOCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/LimeLight/AutoLimeLightDriverDriveCommand.h"
#include "Commands/CommandGroups/AutoScoreHatchCommandGroup.h"
#include "Commands/CommandGroups/AutoMoveFromFeederToSecondHabCommandGroup.h"
#include "Commands/LimeLight/LimeLightWaitForTargetSeenCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/SwerveDrivetrain/AutoDriveAndRotateCommand.h"
#include "CommandBase.h"

class RocketAutoCommandGroup : public frc::CommandGroup {
 public:
  RocketAutoCommandGroup() : CommandGroup("RocketAutoCommandGroup"){
// L2 to rocket
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new InstantCommand([]() {CommandBase::m_pSwerveDrivetrain->setGyroOffset(180);}));
    AddSequential(new AutoDriveAndRotateCommand(0.5, 0, 0.0, 0.0, 1)); // drive off L2
    AddSequential(new AutoDriveAndRotateCommand(1.2, -30, 0.4, -150, 1)); //drive and turn to rocket
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.1, 0.2, 0.0, 0.0, -150.0));

// score hatch 1
    // AddSequential(new LimeLightWaitForTargetSeenCommand());
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.1, 0.2, 0.0, 0.0, -150.0));
    // AddSequential(new AutoScoreHatchCommandGroup());

// drive to feeder
    // AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    // AddSequential(new AutoDriveAndRotateCommand(2, -165, 0.4, 180.0, 1.0)); //change values
    // AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));

// pickup hatch 2
    // AddSequential(new AutoAquireHatchCommandGroup(true));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.2, 0.0, -0.3, 0.0));//change values

// drive to rocket from feeder
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(1.3, 12.0, 0.4, 270.0, 1.0)); //change values
    AddSequential(new AutoDriveAndRotateCommand(1.5, 0.0, 0.4, 270.0, 0.5)); //change values
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2, -0.2, 0.5, 0.4, 270.0));
    // AddSequential(new AutoDriveAndRotateCommand(0.02, 0.01, -0.01, 0.0, 270.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));

// score hatch 2
    // AddSequential(new AutoScoreHatchCommandGroup());
  }
};

#endif //SRC_ROCKETAUTOCOMMANDGROUP