/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINDISTANCE
#define SRC_SWERVEDRIVETRAINDISTANCE

#include <frc/commands/Command.h>
#include "Subsystems/SwerveDrivetrain.h"
#include "CommandBase.h"

class SwerveDrivetrainDistance : public frc::Command {
 private:
  double m_desiredTime;

 public:
  SwerveDrivetrainDistance(double desiredTime) : Command("SwerveDrivetrainDistance"){
    m_desiredTime = desiredTime;
  }
  void Initialize() override {
    SetTimeout(m_desiredTime);
  }
  void Execute() override {
    CommandBase::m_pSwerveDrivetrain->driveClosedLoopControl(0, 0.3, 0, 0, 0, 0);
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

#endif //SRC_SWERVEDRIVETRAINDISTANCE
