#include "OI.h"
#include "RobotMap.h"
#include "Commands/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "frc/buttons/JoystickButton.h"
#include "frc/WPILib.h"
#include "frc/XboxController.h"
#include "Components/Joystick2481.h"
#include "Subsystems/HatchSlide.h"
#include "Components/XboxController2481.h"
#include "Commands/HatchSlideToCenterCommand.h"
#include "Subsystems/LineFinder.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);

	m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(true));
	m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(false));

	m_centerHatch = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	m_centerHatch->WhenPressed(new HatchSlideToCenterCommand(0));
}

OI::~OI() {
	delete m_pDriverStick;
	m_pDriverStick = nullptr;

	delete m_pOperatorStick;
	m_pOperatorStick = nullptr;

	delete m_pSetFieldFrameButton;
	m_pSetFieldFrameButton = nullptr;
}

Joystick2481* OI::GetDriverStick() {
	return m_pDriverStick;
}

Joystick2481* OI::GetOperatorStick() {
	return m_pOperatorStick;
}