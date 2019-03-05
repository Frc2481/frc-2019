/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERDIAGNOSTICSCOMMAND
#define SRC_CLIMBERDIAGNOSTICSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ClimberDiagnosticsCommand : public frc::Command {
  private:
  bool isPullingCurrent;

  public:
  ClimberDiagnosticsCommand() : Command("ClimberDiagnosticsCommand"){
    SetTimeout(1);
    isPullingCurrent = false;
  }
  void Initialize() override {
    CommandBase::m_pClimber->SetOpenLoopSpeed(0.5);
  }
  void Execute() override {
    isPullingCurrent = CommandBase::m_pPDP->GetCurrent(14) > 0.1;
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    SmartDashboard::PutBoolean("ClimberPullingCurrent", isPullingCurrent);
    CommandBase::m_pClimber->SetOpenLoopSpeed(0.0);     
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_CLIMBERDIAGNOSTICSCOMMAND