/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_AUTODRIVEANDROTATECOMMAND
#define SRC_AUTODRIVEANDROTATECOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
class AutoDriveAndRotateCommand : public frc::Command {
 private:
  double m_duration;
  double m_direction;
  double m_targetAngle;

 public:
  AutoDriveAndRotateCommand(double duration, double direction, double angle) : Command("AutoDriveAndRotateCommand"){
    Requires(CommandBase::m_pSwerveDrivetrain.get());
    m_direction = direction;
    m_targetAngle = angle;
    SetTimeout(m_duration);
  }
  void Initialize() override{
    SwerveDrivetrainJoystickSetFieldFrame(true);
  }
  void Execute() override{
    double angleError = CommandBase::m_pSwerveDrivetrain->getGyroYaw() - m_targetAngle;
    angleError += (angleError > 180) ? -360 : (angleError<-180) ? 360 : 0;
    CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(cos(m_direction), sin(m_direction), angleError);
  }
  bool IsFinished() override{
    return IsTimedOut();
  }
  void End() override{
    CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0,0,0);
    SwerveDrivetrainJoystickSetFieldFrame(false);
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_AUTODRIVEANDROTATECOMMAND