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
  double m_yawRate;
  bool m_fieldCentric;
  double m_scaleDirection;

 public:
  AutoDriveAndRotateCommand(double duration, double direction, double yawRate, double angle, double scaleDirection) : Command("AutoDriveAndRotateCommand"){
    Requires(CommandBase::m_pSwerveDrivetrain.get());
    m_direction = 90 - direction;
    m_targetAngle = angle ;
    m_duration = duration;
    m_yawRate = yawRate;
    m_fieldCentric = false;
    m_scaleDirection = scaleDirection;
    SetTimeout(m_duration);
  }
  void Initialize() override{
    m_fieldCentric = CommandBase::m_pSwerveDrivetrain->getFieldFrame();
    CommandBase::m_pSwerveDrivetrain->setIsOpenLoopFieldFrame(true);
  }
  void Execute() override{
    double angleError = CommandBase::m_pSwerveDrivetrain->getGyroYaw() - m_targetAngle;
    angleError += (angleError > 180) ? -360 : (angleError<-180) ? 360 : 0;
    printf("Sin %f Cos %f\n", cos(m_direction * (M_PI / 180)), sin(m_direction * (M_PI / 180)));
    if(fabs(angleError) < 5)
    {
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(cos(m_direction * (M_PI / 180))*m_scaleDirection, sin(m_direction * (M_PI / 180))*m_scaleDirection, 0.0);
    }
    else
    {
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(cos(m_direction * (M_PI / 180))*m_scaleDirection, sin(m_direction * (M_PI / 180))*m_scaleDirection, ((angleError < 0) ? 1 : -1) * m_yawRate);
    }
  }
  bool IsFinished() override{
    return IsTimedOut();
  }
  void End() override{
    CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0,0,0);
    CommandBase::m_pSwerveDrivetrain->setIsOpenLoopFieldFrame(m_fieldCentric); // TODO: Remove this as needed.
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_AUTODRIVEANDROTATECOMMAND