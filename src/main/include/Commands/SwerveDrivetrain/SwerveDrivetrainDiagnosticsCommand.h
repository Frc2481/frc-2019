/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND
#define SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class SwerveDrivetrainDiagnosticsCommand : public frc::Command {
  private:
  bool isFLDrivePullingCurrent;
  bool isFRDrivePullingCurrent;
  bool isBLDrivePullingCurrent;
  bool isBRDrivePullingCurrent;
  bool isFLSteerPullingCurrent;
  bool isFRSteerPullingCurrent;
  bool isBLSteerPullingCurrent;
  bool isBRSteerPullingCurrent;

  public:
  SwerveDrivetrainDiagnosticsCommand() : Command("SwerveDrivetrainDiagnosticsCommand") {
    SetTimeout(2);
    isFLDrivePullingCurrent = false;
    isFRDrivePullingCurrent = false;
    isBLDrivePullingCurrent = false;
    isBRDrivePullingCurrent = false;
    isFLSteerPullingCurrent = false;
    isFRSteerPullingCurrent = false;
    isBLSteerPullingCurrent = false;
    isBRSteerPullingCurrent = false;
  }
  void Initialize() override {}
  void Execute() override {
    if(TimeSinceInitialized() < 1) {
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0, 1, 0);
    isFLDrivePullingCurrent = CommandBase::m_pPDP->GetCurrent(2) > 0.1;
    isFRDrivePullingCurrent = CommandBase::m_pPDP->GetCurrent(3) > 0.1;
    isBLDrivePullingCurrent = CommandBase::m_pPDP->GetCurrent(12) > 0.1;
    isBRDrivePullingCurrent = CommandBase::m_pPDP->GetCurrent(13) > 0.1;
    }
    else if(TimeSinceInitialized() < 2) {
      CommandBase::m_pSwerveDrivetrain->driveOpenLoopControl(0, 0, 1);
      isFLSteerPullingCurrent = CommandBase::m_pPDP->GetCurrent(7) > 0.1;
      isFRSteerPullingCurrent = CommandBase::m_pPDP->GetCurrent(6) > 0.1;
      isBLSteerPullingCurrent = CommandBase::m_pPDP->GetCurrent(5) > 0.1;
      isBRSteerPullingCurrent = CommandBase::m_pPDP->GetCurrent(4) > 0.1;
    }
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    CommandBase::m_pSwerveDrivetrain->stop();
    SmartDashboard::PutBoolean("FLDrivePullingCurrent", isFLDrivePullingCurrent);
    SmartDashboard::PutBoolean("FRDrivePullingCurrent", isFRDrivePullingCurrent);
    SmartDashboard::PutBoolean("BLDrivePullingCurrent", isBLDrivePullingCurrent);
    SmartDashboard::PutBoolean("BRDrivePullingCurrent", isBRDrivePullingCurrent);
    SmartDashboard::PutBoolean("FLSteerPullingCurrent", isFLSteerPullingCurrent);
    SmartDashboard::PutBoolean("FRSteerPullingCurrent", isFRSteerPullingCurrent);
    SmartDashboard::PutBoolean("BLSteerPullingCurrent", isBLSteerPullingCurrent);
    SmartDashboard::PutBoolean("BRSteerPullingCurrent", isBRSteerPullingCurrent);
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND