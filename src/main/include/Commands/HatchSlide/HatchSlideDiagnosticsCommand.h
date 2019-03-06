/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEDIAGNOSTICSCOMMAND
#define SRC_HATCHSLIDEDIAGNOSTICSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class HatchSlideDiagnosticsCommand : public frc::Command {
  private:
  bool isPullingCurrent;

  public:
  HatchSlideDiagnosticsCommand() : Command("HatchSlideDiagnosticsCommand") {
    SetTimeout(0.5);
    isPullingCurrent = false;
  }
  void Initialize() override {
    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0.5);
  }
  void Execute() override {
    isPullingCurrent = CommandBase::m_pPDP->GetCurrent(10) > 0.1;
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    SmartDashboard::PutBoolean("HatchSlidePullingCurrent", isPullingCurrent);
    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_HATCHSLIDEDIAGNOSTICSCOMMAND