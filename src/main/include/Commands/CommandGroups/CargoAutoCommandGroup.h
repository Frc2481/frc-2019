/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOAUTOCOMMANDGROUP
#define SRC_CARGOAUTOCOMMANDGROUP
#include <frc/commands/CommandGroup.h>
#include "Commands/LimeLight/AutoLimeLightDriverDriveCommand.h"
#include "Commands/CommandGroups/AutoScoreHatchCommandGroup.h"
#include "Commands/CommandGroups/AutoMoveFromFeederToSecondHabCommandGroup.h"
#include "Commands/LimeLight/LimeLightWaitForTargetSeenCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/SwerveDrivetrain/AutoDriveAndRotateCommand.h"
#include "CommandBase.h"

class CargoAutoCommandGroup : public frc::CommandGroup {
 public:
  CargoAutoCommandGroup() : CommandGroup("CargoAutoCommandGroup"){
// Level 2 to 1st cargoship dropoff location
    AddSequential(new InstantCommand([]() {CommandBase::m_pSwerveDrivetrain->setGyroOffset(180);}));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(0.8, 0.0, 0.0, 0.0, 1));  // Drives off hab
    AddSequential(new AutoDriveAndRotateCommand(1.1, -15.0, 0.4, 270.0, 1));   //rotate & move toward cargoship //.75
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, 270.0));
    AddSequential(new AutoDriveAndRotateCommand(2, 0.0, 0.4, 270.0, 0.2));    //rotate & move toward cargoship but slow //1.5
    // AddSequential(new AutoDriveAndRotateCommand(0.02, 0.01, -0.01, 0.0, 270.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));

// score hatch 1

    AddSequential(new LimeLightWaitForTargetSeenCommand());
    AddSequential(new InstantCommand([]() {NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("pipeline", 1);})); // rightmost target bc coast
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, 270.0)); // brake
    
    AddSequential(new AutoScoreHatchCommandGroup());

// drive to feeder
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(2.0, -165, 0.4, 180.0, 1.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));

// pickup hatch 2
    AddSequential(new AutoAquireHatchCommandGroup(true));
    // AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false)); //remove later
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0,-0.3,0.0));


// drive to cargo ship
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(1.6, 20.0, 0.4, 270.0, 1.0));
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, 270.0));
    // AddSequential(new AutoDriveAndRotateCommand(1.0, 0.0, 0.4, 270.0, 1.0));
    AddSequential(new SwerveDrivetrainDriveAndRotateCommand(0.2, 0.02, 0.0, 0.0, 270.0));
    AddParallel(new AutoDriveAndRotateCommand(3, 0.0, 0.4, 270.0, 0.2));
    // AddSequential(new SwerveDrivetrainDriveAndRotateCommand(2, -0.2, 0.5, 0.4, 270.0));
    // AddSequential(new AutoDriveAndRotateCommand(0.02, 0.01, -0.01, 0.0, 270.0));

// score hatch 2
    AddSequential(new InstantCommand([]() {NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("pipeline", 0);})); //leftmost
    AddSequential(new LimeLightWaitForLeftTargetSeenCommand());
    // AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    AddSequential(new AutoScoreHatchCommandGroup());

// drive to feeder
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(true));
    AddSequential(new AutoDriveAndRotateCommand(2.0, -165, 0.4, 180.0, 1.0));
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
  }
};

#endif //SRC_CARGOAUTOCOMMANDGROUP