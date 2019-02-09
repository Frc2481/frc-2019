#ifndef COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H
#define COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H

#include "CommandBase.h"
#include "Components/Joystick2481.h"
#include "Components/XboxController2481.h"

class SwerveDrivetrainJoystickSetFieldFrame : public CommandBase {
public:
	SwerveDrivetrainJoystickSetFieldFrame(bool isFieldFrame)
		: CommandBase("SwerveDrivetrainJoystickSetFieldFrame"),
		m_isFieldFrame(isFieldFrame) {
	
		Requires(CommandBase::m_pSwerveDrivetrain.get());
		SetInterruptible(true);
	}

	~SwerveDrivetrainJoystickSetFieldFrame() {
	}

	void Initialize() {
		m_pSwerveDrivetrain->setIsOpenLoopFieldFrame(m_isFieldFrame);
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
	bool m_isFieldFrame;
};

#endif // COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H
