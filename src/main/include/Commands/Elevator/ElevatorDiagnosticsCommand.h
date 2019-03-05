/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORDIAGNOSTICSCOMMAND
#define SRC_ELEVATORDIAGNOSTICSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ElevatorDiagnosticsCommand : public frc::Command {
  private:
  bool isMasterPullingCurrent;
  bool isSlavePullingCurrent;

  public:
  ElevatorDiagnosticsCommand() : Command("ElevatorDiagnosticsCommand") {
    SetTimeout(2);
    isMasterPullingCurrent = false;
    isSlavePullingCurrent = false;
  }
  void Initialize() override {}
  void Execute() override {
    if(TimeSinceInitialized() < 1) {
      CommandBase::m_pElevator->SetMasterOpenLoopSpeed(0.5);
      isMasterPullingCurrent = CommandBase::m_pPDP->GetCurrent(1) > 0.1;
    }
    else if(TimeSinceInitialized() < 2) {
      CommandBase::m_pElevator->SetMasterOpenLoopSpeed(0);
      CommandBase::m_pElevator->SetSlaveOpenLoopSpeed(0.5);
      isSlavePullingCurrent = CommandBase::m_pPDP->GetCurrent(0) > 0.1;
    }
  }
  bool IsFinished() override {
    return IsTimedOut();
  }
  void End() override {
    CommandBase::m_pElevator->SetFollower();
    SmartDashboard::PutBoolean("MasterElevatorPullingCurrent", CommandBase::m_pPDP->GetCurrent(1) > 0.1);
    SmartDashboard::PutBoolean("SlaveElevatorPullingCurrent", CommandBase::m_pPDP->GetCurrent(0) > 0.1);
    CommandBase::m_pElevator->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_ELEVATORDIAGNOSTICSCOMMAND