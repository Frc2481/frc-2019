/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBSEQUENCECOMMANDGROUP
#define SRC_CLIMBSEQUENCECOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/Climber/ClimberWaitForHeightCommand.h"
#include "CommandBase.h"
#include "Commands/Climber/ClimberToggleBigFootCommand.h"
#include "Commands/Climber/ClimberToggleLittleFeetCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainSetOpenLoop.h"
#include "Commands/Climber/ClimberSetOpenLoopCommand.h"
#include "Commands/Climber/ClimberReleaseWeightsCommand.h"
#include "Commands/Climber/ClimberSetPositionCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainSetBrakeCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/Climber/ClimberCheckpointCommand.h"

class ClimbSequence2To3CommandGroup : public frc::CommandGroup {
 public:
  ClimbSequence2To3CommandGroup() : CommandGroup("ClimbSequence2To3CommandGroup"){
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0, 0.25, 0.0));
    AddParallel(new ClimberSetPositionCommand(150));
    AddSequential(new ClimberWaitForHeightCommand(50));
    AddSequential(new ClimberLittleFeetDownCommand());
    AddSequential(new ClimberWaitForHeightCommand(148));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.5, 0.0, 0.25, 0.0));
    AddSequential(new WaitCommand(3));
    AddSequential(new ClimberSetPositionCommand(125));
    AddSequential(new ClimberTiltBigFootCommand());
  }
};

class ClimbSequenceLevel3CommandGroup : public frc::CommandGroup {
 public:
  ClimbSequenceLevel3CommandGroup() : CommandGroup("ClimbSequenceLevel3CommandGroup"){
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0, 0.0, 0.0));
    AddSequential(new SwerveDrivetrainSetBrakeCommand());

    //lower climber & drive on
    AddParallel(new ClimberSetPositionCommand(205));
    AddSequential(new ClimberWaitForHeightCommand(60));
    AddSequential(new ClimberLittleFeetDownCommand());
    AddSequential(new ClimberWaitForHeightCommand(193));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.8, 0.0, 0.15, 0.0));
    AddParallel(new SwerveDrivetrainSetOpenLoop(10.0, 0.0, 0.15, 0.0));

    //make adjustments if needed
    // AddSequential(new ClimberCheckpointCommand());
    // AddSequential(new WaitCommand(0.5));

    //raise climber and drive on further
    AddParallel(new ClimberSetOpenLoopCommand(-0.3));
    AddSequential(new ClimberWaitForHeightCommand(185));
    AddSequential(new ClimberSetOpenLoopCommand(0));
    // AddSequential(new ClimberSetPositionCommand(180));
    AddSequential(new WaitCommand(0.1));
    AddSequential(new ClimberSetPositionCommand(175));
    AddParallel(new SwerveDrivetrainSetOpenLoop(10.0, 0.0, 0.0, 0.0));
    
    //tilt big foot
    AddSequential(new WaitCommand(0.5));
    AddSequential(new ClimberTiltBigFootCommand());
  }
};

class ClimbSequence1To2CommandGroup : public frc::CommandGroup {
 public:
  ClimbSequence1To2CommandGroup() : CommandGroup("ClimbSequence1To2CommandGroup"){
    AddSequential(new SwerveDrivetrainJoystickSetFieldFrame(false));
    // AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0, 0.0, 0.0));
    AddSequential(new SwerveDrivetrainSetBrakeCommand());

    //lower climber & drive on
    AddSequential(new ClimberSetPositionCommand(115));
    AddSequential(new ClimberLittleFeetDownCommand());
    AddSequential(new ClimberReleaseWeightsCommand());
    AddSequential(new WaitCommand(3.0));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.5, 0.0, 0.25, 0.0));
    // AddSequential(new ClimberSetPositionCommand(90));    
    // AddSequential(new ClimberTiltBigFootCommand());
    // AddSequential(new ClimberSetPositionCommand(0)); //TODO fix all of this
    // AddSequential(new ClimberUntiltBigFootCommand());
    // AddSequential(new ClimberSetPositionCommand(25));
    // AddSequential(new SwerveDrivetrainSetOpenLoop(0.5, 0.0, 0.25, 0.0));
  }
};

class ClimbSequenceFloorTo2CommandGroup : public frc::CommandGroup {
 public:
  ClimbSequenceFloorTo2CommandGroup() : CommandGroup("ClimbSequenceFloorTo2CommandGroup"){
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.1, 0.0, 0.25, 0.0));
    AddSequential(new SwerveDrivetrainSetBrakeCommand());

    AddSequential(new ClimberSetOpenLoopCommand(1.0));    
    AddSequential(new ClimberWaitForHeightCommand(50));
    AddSequential(new ClimberLittleFeetDownCommand());
    AddSequential(new ClimberWaitForHeightCommand(148));
    AddSequential(new ClimberSetOpenLoopCommand(0.0));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.5, 0.0, 0.25, 0.0));
    AddSequential(new WaitCommand(3));
    AddSequential(new ClimberTiltBigFootCommand());
    AddSequential(new ClimberSetOpenLoopCommand(-0.5));
    AddSequential(new ClimberWaitForHeightCommand(23));
    AddSequential(new ClimberSetOpenLoopCommand(0.0));
    AddSequential(new ClimberUntiltBigFootCommand());
    AddSequential(new ClimberSetOpenLoopCommand(0.5));
    AddSequential(new ClimberWaitForHeightCommand(0)); //find actual height
    AddSequential(new ClimberSetOpenLoopCommand(0.0));    
  }
};
#endif //SRC_CLIMBSEQUENCECOMMANDGROUP