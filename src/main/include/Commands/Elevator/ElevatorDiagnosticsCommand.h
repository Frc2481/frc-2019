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
#include "Subsystems/Elevator.h"
#include "RobotParameters.h"

class ElevatorDiagnosticsCommand : public frc::Command {
 private:
  double m_masterCurrent;
  double m_slaveCurrent;
  double m_masterSpeed;
 public:
  ElevatorDiagnosticsCommand() : Command("ElevatorDiagnosticsCommand") {
    Requires(CommandBase::m_pElevator.get());
    m_masterCurrent = 0;
    m_slaveCurrent = 0;
    m_masterSpeed = 0;
  }
  
  void Execute() override {
    // Master current
    if(TimeSinceInitialized() < 1) {
      CommandBase::m_pElevator->SetMasterOpenLoopSpeed(0.5);
      m_masterCurrent = CommandBase::m_pPDP->GetCurrent(1);
      m_masterSpeed = CommandBase::m_pElevator->GetMasterSpeed();
    }
    CommandBase::m_pElevator->SetMasterOpenLoopSpeed(0);

    else if(TimeSinceInitialized() < 2) {
      CommandBase::m_pElevator->SetSlaveOpenLoopSpeed(0.5);
      m_slaveCurrent = CommandBase::m_pPDP->GetCurrent(0);
    }
    CommandBase::m_pElevator->SetSlaveOpenLoopSpeed(0);
    SmartDashboard::PutBoolean("MasterElevCurrent", fabs(m_masterCurrent - RobotParameters::k_avgMasterElevatorCurrent) < 0); //make sure to put legit value
    SmartDashboard::PutBoolean("SlaveElevCurrent", fabs(m_slaveCurrent - RobotParameters::k_avgSlaveElevatorCurrent) < 0); //legit value
    SmartDashboard::PutBoolean("MasterElevSpeedDiag", fabs(m_masterSpeed - 0.5) < 0); //legit value
  }
  bool IsFinished() override {
    return TimeSinceInitialized() > 2;
  }
};

#endif //SRC_ELEVATORDIAGNOSTICSCOMMAND