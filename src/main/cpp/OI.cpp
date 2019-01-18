#include "OI.h"
#include "RobotMap.h"
#include "Commands/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/SwerveDrivetrainShiftGear.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);

	m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(true));
	m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(false));

	m_pDriveShiftButton = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	m_pDriveShiftButton->WhenPressed(new SwerveDrivetrainShiftGear(false));
	m_pDriveShiftButton->WhenReleased(new SwerveDrivetrainShiftGear(true));
}

OI::~OI() {
	delete m_pDriverStick;
	m_pDriverStick = nullptr;

	delete m_pOperatorStick;
	m_pOperatorStick = nullptr;

	delete m_pSetFieldFrameButton;
	m_pSetFieldFrameButton = nullptr;

	delete m_pDriveShiftButton;
	m_pDriveShiftButton = nullptr;
}

Joystick2481* OI::GetDriverStick() {
	return m_pDriverStick;
}

Joystick2481* OI::GetOperatorStick() {
	return m_pOperatorStick;
}
