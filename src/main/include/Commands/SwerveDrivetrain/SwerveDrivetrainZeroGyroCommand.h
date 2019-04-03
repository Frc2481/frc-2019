/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_SWERVEDRIVETRAINZEROGYROCOMMAND
#define SRC_SWERVEDRIVETRAINZEROGYROCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class SwerveDrivetrainZeroGyroCommand : public frc::InstantCommand {
public:
	SwerveDrivetrainZeroGyroCommand() : InstantCommand("SwerveDrivetrainZeroGyroCommand") {
		SetRunWhenDisabled(true);
	}
	void Initialize() override {
		CommandBase::m_pSwerveDrivetrain->zeroGyroYaw();
	}
};

#endif //SRC_SWERVEDRIVETRAINZEROGYROCOMMAND
