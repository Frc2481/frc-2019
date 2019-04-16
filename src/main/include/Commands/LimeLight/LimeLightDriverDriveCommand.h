/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_LIMELIGHTDRIVERDRIVECOMMAND
#define SRC_LIMELIGHTDRIVERDRIVECOMMAND

#include <frc/commands/Command.h>
#include "Subsystems/SwerveDrivetrain.h"
#include "CommandBase.h"
#include "Components/Joystick2481.h"
#include "networktables/NetworkTableInstance.h"
#include <sstream>

using namespace nt;

class LimeLightDriverDriveCommand : public frc::Command {
 public:
  LimeLightDriverDriveCommand() : Command("LimeLightDriverDriveCommand"){
    Requires(CommandBase::m_pSwerveDrivetrain.get());
  }

  virtual ~LimeLightDriverDriveCommand()
  {

  }

  void Initialize() override{}
  void Execute() override{
    double scaleScew = -0.015;
    double scaleYaw = 0.04;
    double skew = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0);
    
    // scaleScew = frc::Preferences::GetInstance()->GetDouble("Scale skew");
    // scaleYaw = frc::Preferences::GetInstance()->GetDouble("Scale yaw");//For Tunning
    if (skew < -45) { skew += 90.0; }
    if(-CommandBase::m_pOI->GetDriverStick()->GetRawAxis(XBOX_LEFT_Y_AXIS) > 0.1){
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(skew*scaleScew, 
                                            -CommandBase::m_pOI->GetDriverStick()->GetRawAxis(XBOX_LEFT_Y_AXIS),
                                            -NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0)*scaleYaw);
    }
    else{
       CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0.0, 0.0, 0.0);
    }
  }
  bool IsFinished() override{
    return false;
  }
  void End() override{
    CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0.0,0.0,0.0);
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_LIMELIGHTDRIVERDRIVECOMMAND