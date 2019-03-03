/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND
#define SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND
#include <frc/commands/Command.h>
#include "Subsystems/SwerveDrivetrain.h"
#include "CommandBase.h"

class SwerveDrivetrainDiagnosticsCommand : public frc::Command {
 public:
  SwerveDrivetrainDiagnosticsCommand();
  void Initialize() override{}
  void Execute() override{
    if(TimeSinceInitialized() < 2){
      CommandBase::m_pSwerveDrivetrain->driveClosedLoopControl(0, 0.5, 0, 0.2, 0, 0);
    }
    else if(TimeSinceInitialized() < 4){
      CommandBase::m_pSwerveDrivetrain->driveClosedLoopControl(0, 0, 0, 0, 0.5, 0.2);
    }
    CommandBase::m_pSwerveDrivetrain->driveClosedLoopControl(0, 0, 0, 0, 0, 0);
    // SmartDashboard::PutBoolean("GetSteerCurrent", fabs(m_extendCurrent - PDPC::k_curre) < 0); //make sure to put legit value
    // SmartDashboard::PutBoolean("CargoIntakeBallCurrent", fabs(m_intakeCurrent - RobotParameters::k_avgCargoIntakeBallCurrent) < 0); //legit value
    // SmartDashboard::PutBoolean("CargoIntakeSpeedDiag", fabs(m_extendSpeed - 0.5) < 0); //legit value
  }
  bool IsFinished() override{}
  void End() override{}
  void Interrupted() override{}
};
#endif //SRC_SWERVEDRIVETRAINDIAGNOSTICSCOMMAND