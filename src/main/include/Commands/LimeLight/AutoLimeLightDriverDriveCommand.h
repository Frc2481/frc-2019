/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTOLIMELIGHTDRIVERDRIVECOMMAND
#define SRC_AUTOLIMELIGHTDRIVERDRIVECOMMAND

#include <frc/commands/Command.h>
#include "Subsystems/SwerveDrivetrain.h"
#include "CommandBase.h"
#include "Components/Joystick2481.h"
#include "networktables/NetworkTableInstance.h"
#include <math.h>

using namespace nt;

class AutoLimeLightDriverDriveCommand : public frc::Command {
 private:
  bool m_prevFieldCentric;
 public:
  AutoLimeLightDriverDriveCommand() : Command("AutoLimeLightDriverDriveCommand"){
    Requires(CommandBase::m_pSwerveDrivetrain.get());
  }

  virtual ~AutoLimeLightDriverDriveCommand()
  {

  }

  void Initialize() override{
    m_prevFieldCentric = CommandBase::m_pSwerveDrivetrain->getFieldFrame();
    CommandBase::m_pSwerveDrivetrain->setIsOpenLoopFieldFrame(false);
  }
  void Execute() override{
    double scaleTs = -0.015;
    double scaleTx = 0.01;
    double scaleTy = 0.0;
    double y = 0.35;
    double skew = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ts",0);
    double tx = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0);
    double tv = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv",0);
    double scaleAll = frc::Preferences::GetInstance()->GetDouble("ScaleAll");
    scaleTs = frc::Preferences::GetInstance()->GetDouble("Scale ts");
    scaleTx = frc::Preferences::GetInstance()->GetDouble("Scale tx");
    scaleTy = frc::Preferences::GetInstance()->GetDouble("Scale ty");
    if (skew < -45) { skew += 90.0; }
    if((skew > 2) && (tx > 2)){
      y = 0.1;
    }
    else{
      y = 0.35*scaleTy;
    }
    if(bool(tv)){
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(-tx*scaleTx*scaleAll, y*scaleAll, skew*scaleAll*scaleTs);
    }
    else{
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0, y, 0);
    }
  }
  bool IsFinished() override{
    double angle = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty",0);
    double distance = 16.5*tan((60.0+angle)*M_PI/180.0);
    // double distance = 15.75*tan((58.04+angle)*M_PI/180.0);
    SmartDashboard::PutNumber("distance ", distance);
    return distance < 18.0;
  }
  void End() override{
    CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0.0,0.0,0.0);
    CommandBase::m_pSwerveDrivetrain->setIsOpenLoopFieldFrame(m_prevFieldCentric);
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_AUTOLIMELIGHTDRIVERDRIVECOMMAND