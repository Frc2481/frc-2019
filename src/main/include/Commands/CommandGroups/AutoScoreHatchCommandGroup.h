/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOSCOREHATCHSOMMANDGROUP
#define SRC_AUTOSCOREHATCHSOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/LimeLight/AutoLimeLightDriverDriveCommand.h"
#include "CommandBase.h"
#include "Commands/CommandGroups/ScoreCommandGroup.h"
#include "Commands\SwerveDrivetrain\SwerveDrivetrainSetOpenLoop.h"
#include "Commands/HatchSlide/HatchSlideWaitForOnTargetCommand.h"
#include "Commands/CommandGroups/AcquireHatchCommandGroup.h"
#include "Commands/SwerveDrivetrain/AutoDriveAndRotateCommand.h"
#include "Commands/HatchSlide/HatchSlideWaitForOnTargetWhenEnabledCommand.h"

class AutoAquireHatchCommandGroup : public frc::CommandGroup {
 public:
  AutoAquireHatchCommandGroup(bool noWait = false) : CommandGroup("AutoAquireHatchCommandGroup"){
    AddParallel(new PrepForAcquireHatchCommandGroup());
     AddSequential(new InstantCommand([](){
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);
       }));
    // AddSequential(new InstantCommand([](){CommandBase::m_pHatchSlide->EnableUserHatchSlide();}));
    AddSequential(new AutoLimeLightDriverDriveCommand());
    AddSequential(new HatchSlideWaitForOnTargetCommand());
    AddParallel(new AcquireHatchCommandGroup());
    AddSequential(new WaitCommand(0.7));
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.2, 0.0,-0.3,0.0));//this is in field centric
    AddSequential(new SwerveDrivetrainSetOpenLoop(0.5, 0.0,-0.6,0.0));//this is in field centric

    AddSequential(new InstantCommand([](){CommandBase::m_pHatchSlide->DisableUserHatchSlide();}));
    
    //used on while held and don't want it to repeat itself
    if(!noWait){
      AddSequential(new WaitCommand(10.0));
    }
    // AddSequential(new InstantCommand([](){
    //    NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
    //    NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 1);
    //    }));
  }
};

class AutoScoreHatchCommandGroup : public frc::CommandGroup {
 public:
  AutoScoreHatchCommandGroup() : CommandGroup("AutoScoreHatchCommandGroup"){
     AddSequential(new InstantCommand([](){
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);
       }));
    // AddSequential(new InstantCommand([](){CommandBase::m_pHatchSlide->EnableUserHatchSlide();}));
    AddSequential(new AutoLimeLightDriverDriveCommand());
    // AddSequential(new HatchSlideWaitForOnTargetCommand());
    AddSequential(new HatchSlideWaitForOnTargetWhenEnabledCommand());
    AddSequential(new ScoreCommand());
    AddSequential(new InstantCommand([](){CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0.0,0.0,0.0);}));
    // AddSequential(new WaitCommand(0.2));
    // AddSequential(new SwerveDrivetrainSetOpenLoop(0.3,0.0,-0.3,0.0));
    AddSequential(new InstantCommand([](){CommandBase::m_pHatchSlide->DisableUserHatchSlide();}));
    // AddSequential(new InstantCommand([](){
    //    NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
    //    NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 1);
    //    }));
  }
};
#endif //SRC_AUTOSCOREHATCHSOMMANDGROUP