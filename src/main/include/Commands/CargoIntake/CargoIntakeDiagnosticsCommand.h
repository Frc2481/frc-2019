/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEDIAGNOSTICSCOMMAND
#define SRC_CARGOINTAKEDIAGNOSTICSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class CargoIntakeDiagnosticsCommand : public frc::Command {
  private:
  bool isExtensionPullingCurrent;
  bool isIntakePullingCurrent;

  public:
  CargoIntakeDiagnosticsCommand() : Command("CargoIntakeDiagnosticsCommand") {
    SetTimeout(2);
    isExtensionPullingCurrent = false;
    isIntakePullingCurrent = false;
  }
  void Initialize() override {}
  void Execute() override {
    if(TimeSinceInitialized() < 1) {
      CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0.5);
      isExtensionPullingCurrent = CommandBase::m_pPDP->GetCurrent(9) > 0.1;
    }
    else if(TimeSinceInitialized() < 2) {
      CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
      CommandBase::m_pCargoIntake->SetSpeedIn(0.5);
      isIntakePullingCurrent = CommandBase::m_pPDP->GetCurrent(15) < 0.1;
    }
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    SmartDashboard::PutBoolean("isIntakeExtPullingCurrent", isExtensionPullingCurrent);
    SmartDashboard::PutBoolean("isBallIntakePullingCurrent", isIntakePullingCurrent);
    CommandBase::m_pCargoIntake->SetSpeedIn(0);
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_CARGOINTAKEDIAGNOSTICSCOMMAND