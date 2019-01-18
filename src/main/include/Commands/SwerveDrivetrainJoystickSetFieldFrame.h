#ifndef COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H
#define COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H

#include "CommandBase.h"
#include "Components/Joystick2481.h"
#include "Components/XboxController2481.h"

class SwerveDrivetrainJoystickSetFieldFrame : public CommandBase {
public:
	SwerveDrivetrainJoystickSetFieldFrame()
		: CommandBase("SwerveDrivetrainJoystickSetFieldFrame") {
	
		Requires(CommandBase::m_pSwerveDrivetrain.get());
		SetInterruptible(true);
	}

	~SwerveDrivetrainJoystickSetFieldFrame() {
	}

	void Initialize() {
		m_pSwerveDrivetrain->SetIsOpenLoopFieldFrame(true);
	}

	void Execute() {
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return false;
	}

	void End() {
		m_pSwerveDrivetrain->SetIsOpenLoopFieldFrame(false);
	}

private:
	bool m_isFieldFrame;
};

#endif // COMMANDS_SWERVE_DRIVETRAIN_JOYSTICK_SET_FIELD_FRAME_H
