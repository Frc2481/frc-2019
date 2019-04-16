/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINDRIVEANDROTATE
#define SRC_SWERVEDRIVETRAINDRIVEANDROTATE

#include <frc/commands/Command.h>
#include "Subsystems/SwerveDrivetrain.h"
#include "CommandBase.h"

class SwerveDrivetrainDriveAndRotateCommand : public frc::Command {
 private:
  double m_desiredTime;
  double m_xVel;
  double m_yVel;
  double m_yawRate;
  double m_targetAngle;

 public:
  SwerveDrivetrainDriveAndRotateCommand(double desiredTime, double xVel, double yVel, double yawRate, double targetAngle) : Command("SwerveDrivetrainDriveAndRotateCommand"){
    Requires(CommandBase::m_pSwerveDrivetrain.get());
    m_desiredTime = desiredTime;
    m_xVel = xVel;
    m_yVel = yVel;
    m_yawRate = yawRate;
    m_targetAngle = targetAngle;
    SetTimeout(m_desiredTime);
  }
  void Initialize() override {
    
  }
  void Execute() override {
    double angleError = CommandBase::m_pSwerveDrivetrain->getGyroYaw() - m_targetAngle;
    angleError += (angleError > 180) ? -360 : (angleError<-180) ? 360 : 0;
    if(fabs(angleError) < 5)
    {
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(m_xVel, m_yVel, 0.0);
    }
    else
    {
      
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(m_xVel, m_yVel, ((angleError < 0) ? 1 : -1) * m_yawRate);
    }
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    CommandBase::m_pSwerveDrivetrain->stop();
  }
  void Interrupted() override {
    End();
  }
};

#endif //
