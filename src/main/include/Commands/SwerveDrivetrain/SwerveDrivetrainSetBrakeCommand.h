/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINSETBRAKECOMMAND
#define SRC_SWERVEDRIVETRAINSETBRAKECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class SwerveDrivetrainSetBrakeCommand : public frc::InstantCommand {
 public:
  SwerveDrivetrainSetBrakeCommand() : InstantCommand("SwerveDrivetrainSetBrakeCommand") {}
  void Initialize() override {
    CommandBase::m_pSwerveDrivetrain->setBrakeMode();
  }
};

#endif //SRC_SWERVEDRIVETRAINSETBRAKECOMMAND