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
#include "Subsystems/CargoIntake.h"
#include "RobotParameters.h"

class CargoIntakeDiagnosticsCommand : public frc::Command {
 private:
  double m_extendCurrent;
  double m_intakeCurrent;
  double m_extendSpeed;
 public:
  CargoIntakeDiagnosticsCommand() : Command("CargoIntakeDiagnosticsCommand") {
    Requires(CommandBase::m_pElevator.get());
    Requires(CommandBase::m_pCargoIntake.get());
    m_extendCurrent = 0;
    m_intakeCurrent = 0;
    m_extendSpeed = 0;
  }
  
  void Execute() override {
    // Master current
    if(TimeSinceInitialized() < 1) {
      CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0.5);
      m_extendCurrent = CommandBase::m_pPDP->GetCurrent(9);
      m_extendCurrent = CommandBase::m_pCargoIntake->GetExtendSpeed();
    }
    else if(TimeSinceInitialized() < 2) {
      CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
      CommandBase::m_pCargoIntake->SetSpeedIn(0.5);
      m_intakeCurrent = CommandBase::m_pPDP->GetCurrent(15);
    }

    CommandBase::m_pCargoIntake->StopIntake();
    SmartDashboard::PutBoolean("CargoIntakeExtCurrent", fabs(m_extendCurrent - RobotParameters::k_avgCargoIntakeExtCurrent) < 0); //make sure to put legit value
    SmartDashboard::PutBoolean("CargoIntakeBallCurrent", fabs(m_intakeCurrent - RobotParameters::k_avgCargoIntakeBallCurrent) < 0); //legit value
    SmartDashboard::PutBoolean("CargoIntakeSpeedDiag", fabs(m_extendSpeed - 0.5) < 0); //legit value
  }
  bool IsFinished() override {
    return TimeSinceInitialized() > 2;
  }
};

#endif //SRC_CARGOINTAKEDIAGNOSTICSCOMMAND