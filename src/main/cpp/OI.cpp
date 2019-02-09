#include "OI.h"
#include "RobotMap.h"
#include "frc/buttons/JoystickButton.h"
#include "frc/WPILib.h"
#include "frc/XboxController.h"
#include "Components/Joystick2481.h"
#include "Components/XboxController2481.h"

#include "Commands/SwerveDrivetrain/SwerveDrivetrainJoystickSetFieldFrame.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeEjectCommand.h"
#include "Commands/CommandGroups/AcquireCargoCommandGroup.h"
#include "Commands/CommandGroups/AcquireHatchCommandGroup.h"
#include "Commands/HatchSlide/HatchSlideToCenterCommand.h"
#include "Commands/Elevator/ElevatorRaiseCommand.h"
#include "Commands/Elevator/ElevatorLowerCommand.h"
#include "Commands/Auto/AutoPlaceCommandGroup.h"

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

	m_acquireCargo = new JoystickButton(m_pDriverStick, XBOX_RIGHT_TRIGGER);
	m_acquireCargo->WhenPressed(new AcquireCargoCommandGroup());

	m_acquireHatch = new JoystickButton(m_pDriverStick, XBOX_LEFT_TRIGGER);

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);

    m_elevatorStow = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	m_elevatorStow->WhenPressed(new ElevatorStowCommand("ElevatorStowCommand"));

	m_fieldCentric = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);

//operator
	m_scoreHigh = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_scoreHigh->WhenPressed(new AutoPlaceCommandGroup(new ElevatorHighCommand("ElevatorHighCommand")));

	m_scoreMid = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_scoreMid->WhenPressed(new AutoPlaceCommandGroup(new ElevatorMidCommand("ElevatorMidCommand")));

	m_scoreLow = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_scoreLow->WhenPressed(new AutoPlaceCommandGroup(new ElevatorLowCommand("ElevatorLowCommand")));

	m_elevatorRaise = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, -0.25); //right stick up
	m_elevatorRaise->WhileHeld(new ElevatorRaiseCommand());

	m_elevatorLower = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, 0.25); //right stick down
	m_elevatorLower->WhileHeld(new ElevatorLowerCommand());

	m_cargoShip = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_cargoShip->WhenPressed(new AutoPlaceCommandGroup(new ElevatorCargoShipCommand("ElevatorCargoShipCommand")));
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