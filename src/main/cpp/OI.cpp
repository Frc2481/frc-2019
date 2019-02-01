#include "OI.h"
#include "RobotMap.h"
#include "Commands/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "frc/buttons/JoystickButton.h"
#include "frc/WPILib.h"
#include "frc/XboxController.h"
#include "Components/Joystick2481.h"
#include "Components/XboxController2481.h"

#include "Commands/ElevatorBaseCommand.h"
#include "Commands/CargoEjectBallCommand.h"
#include "Commands/CargoIntakeBallCommand.h"
#include "Commands/CargoEjectBallCommand.h"
#include "Commands/CargoIntakeAcquireBallCommandGroup.h"
#include "Commands/HatchSlideToCenterCommand.h"
#include "Commands/ElevatorRaiseCommand.h"
#include "Commands/ElevatorLowerCommand.h"
#include "Commands/AutoPlaceHighCommandGroup.h"
#include "Commands/AutoPlaceMidCommandGroup.h"
#include "Commands/AutoPlaceLowCommandGroup.h"
#include "Commands/AutoPlaceCargoShipCommandGroup.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);

	m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(true));
	m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(false));

	m_centerHatch = new JoystickButton(m_pDriverStick, XBOX_B_BUTTON);
	m_centerHatch->WhenPressed(new HatchSlideToCenterCommand());

//driver
	m_intakeBall = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	m_intakeBall->WhenPressed(new CargoIntakeBallCommand(0)); //change speed

	m_acquireBall = new JoystickButton(m_pDriverStick, XBOX_RIGHT_TRIGGER);
	m_acquireBall->WhenPressed(new CargoIntakeAcquireBallCommandGroup());

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);

    m_elevatorHome = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	m_elevatorHome->WhenPressed(new ElevatorLowHatchCommand("ElevatorLowHatchCommand"));

	m_fieldCentric = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);

//operator
	m_ejectBall = new JoystickButton(m_pOperatorStick, XBOX_LEFT_TRIGGER);
	m_ejectBall->WhenPressed(new CargoEjectBallCommand(0)); //change speed
	
	m_elevatorHigh = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_elevatorHigh->WhenPressed(new AutoPlaceHighCommandGroup());

	m_elevatorMid = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_elevatorMid->WhenPressed(new AutoPlaceMidCommandGroup());

	m_elevatorLow = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_elevatorLow->WhenPressed(new AutoPlaceLowCommandGroup());

	m_elevatorRaise = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, -0.25); //right stick up
	m_elevatorRaise->WhileHeld(new ElevatorRaiseCommand());

	m_elevatorLower = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, 0.25); //right stick down
	m_elevatorLower->WhileHeld(new ElevatorLowerCommand());

	m_cargoShip = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_cargoShip->WhenPressed(new AutoPlaceCargoShipCommandGroup());
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