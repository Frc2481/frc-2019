#ifndef COMMANDS_SWERVE_DRIVETRAIN_ZERO_STEER_H
#define COMMANDS_SWERVE_DRIVETRAIN_ZERO_STEER_H

#include "CommandBase.h"

class SwerveDrivetrainZeroSteer : public CommandBase {
public:
	SwerveDrivetrainZeroSteer()
		: CommandBase("SwerveDrivetrainZeroSteer") {
		
		Requires(CommandBase::m_pSwerveDrivetrain.get());
		SetInterruptible(false);
		SetRunWhenDisabled(true);
  }

	~SwerveDrivetrainZeroSteer() {
	}

	void Initialize() {
		m_pSwerveDrivetrain->zeroSteerEncoders();
	}

	void Execute() {
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return true;
	}

	void End() {
	}

private:

};

#endif // COMMANDS_SWERVE_DRIVETRAIN_ZERO_STEER_H
