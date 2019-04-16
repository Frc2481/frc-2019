/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_LIMELIGHTABORTCOMMANDGROUP
#define SRC_LIMELIGHTABORTCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "CommandBase.h"

using namespace nt;

class LimeLightAbortCommandGroup : public frc::CommandGroup {
 public:
  LimeLightAbortCommandGroup() : CommandGroup("LimeLightAbortCommandGroup"){
    AddSequential(new InstantCommand([](){CommandBase::m_pHatchSlide->DisableUserHatchSlide();}));
    AddSequential(new InstantCommand([](){
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
       NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 1);
       }));
  }
};

#endif //SRC_LIMELIGHTABORTCOMMANDGROUP