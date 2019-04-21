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
#include "Commands/Elevator/ElevatorBaseCommand.h"

class RocketAutoCommandGroup : public frc::CommandGroup {
 public:
  RocketAutoCommandGroup() : CommandGroup("RocketAutoCommandGroup"){
// L2 to rocket
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new InstantCommand([]() {CommandBase::m_pSwerveDrivetrain->setGyroOffset(180);}));
    AddSequential(new AutoDriveAndRotateCommand(1.3, 0.0, 0.0, 0.0, 1));  // Drives off hab
    AddSequential(new AutoDriveAndRotateCommand(0.8, -28.75, 0.3, -208.75, 1)); //drive and turn to rocket
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, -208.75)); //brake
    AddParallel(new AutoDriveAndRotateCommand(2, -28.75, 0.3, -208.75, 0.2)); //drive and turn to rocket
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.1, 0.2, 0.0, 0.0, -150.0));

// score hatch 1
    AddParallel(new ElevatorLowCommand("ElevatorLowCommand"));
    AddSequential(new LimeLightWaitForTargetSeenCommand());
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.1, 0.2, 0.0, 0.0, -208.75)); //brake
    AddSequential(new AutoScoreHatchCommandGroup());

// drive to feeder
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(1.5, -0.7, -0.3, 0.0, -208.75));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(0.55, -270, 0.0, -208.75, 1.0)); //change values
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, -208.75)); //brake
    AddSequential(new AutoDriveAndRotateCommand(1.8, -170, 0.3, 180.0, 1.0)); //change values
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));

// pickup hatch 2
    AddSequential(new AutoAquireHatchCommandGroup(true));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0,-0.3,0.0));

// drive to rocket from feeder
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(1.6, 7.0, 0.7, 28.75, 0.5));
    AddParallel(new ElevatorLowCommand("ElevatorLowCommand"));

// score hatch 2
    AddSequential(new InstantCommand([]() {NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("pipeline", 0);})); //leftmost
    AddSequential(new LimeLightWaitForTargetSeenCommand());
    // AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    AddSequential(new AutoScoreHatchCommandGroup());
  }
};

#endif //SRC_ROCKETAUTOCOMMANDGROUP