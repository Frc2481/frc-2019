#ifndef COMMANDS_SWERVE_DRIVETRAIN_SHIFT_GEAR_H
#define COMMANDS_SWERVE_DRIVETRAIN_SHIFT_GEAR_H

#include "CommandBase.h"

class SwerveDrivetrainShiftGear : public CommandBase {
public:
	SwerveDrivetrainShiftGear(bool isHighGear)
		: CommandBase("SwerveDrivetrainShiftGear"),
		m_isHighGear(isHighGear) {
		
		Requires(CommandBase::m_pSwerveDrivetrain.get());
		SetInterruptible(false);
	}

	~SwerveDrivetrainShiftGear() {
	}

	void Initialize() {
		m_pSwerveDrivetrain->setShiftState(m_isHighGear);
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
	bool m_isHighGear;
};

#endif // COMMANDS_SWERVE_DRIVETRAIN_SHIFT_GEAR_H
