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
#include "Commands/Elevator/ElevatorJoystickCommand.h"
#include "Commands/Auto/AutoPlaceCommandGroup.h"
#include "Commands/HatchSlide/HatchSlideToggleCommand.h"
#include "Commands/Climber/ClimberLevel2Command.h"
#include "Commands/Climber/ClimberLevel3Command.h"
#include "Commands/Climber/ClimberRetractCommand.h"
#include "Commands/Climber/ClimberToggleLittleFeetCommand.h"
#include "Commands/Climber/ClimberToggleBigFootCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroGyroCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerScoreCommand.h"
#include "Commands/HatchSlide/HatchSlideJoystickCommand.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);
		
//driver
	m_acquireCargo = new AnalogJoystickButton(m_pDriverStick, XBOX_RIGHT_TRIGGER, 0.5);
	m_acquireCargo->WhenPressed(new AcquireCargoCommandGroup());

	m_acquireHatch = new AnalogJoystickButton(m_pDriverStick, XBOX_LEFT_TRIGGER, 0.5);
	m_acquireHatch->WhenPressed(new AcquireHatchCommandGroup());

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);
	m_zeroGyro->WhenPressed(new SwerveDrivetrainZeroGyroCommand());

    m_elevatorStow = new JoystickButton(m_pDriverStick, XBOX_X_BUTTON);
	m_elevatorStow->WhenPressed(new ElevatorStowCommand("ElevatorStowCommand"));

	// m_climbLevel3 = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	// m_climbLevel3->WhenPressed(new ClimberLevel3Command());
	
	// m_climbLevel2 = new JoystickButton(m_pDriverStick, XBOX_B_BUTTON);
	// m_climbLevel2->WhenPressed(new ClimberLevel2Command());
	
	// m_climbRetract = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	// m_climbRetract->WhenPressed(new ClimberRetractCommand());
	
	m_climberLittleFeet = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_climberLittleFeet->ToggleWhenPressed(new ClimberToggleLittleFeetCommand());

	m_climberBigFoot = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	m_climberBigFoot->ToggleWhenPressed(new ClimberToggleBigFootCommand());

	// m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	// m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(true));
	// m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(false));

//operator
	m_scoreHigh = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_scoreHigh->WhenPressed(new ElevatorHighCommand("ElevatorHighCommand"));

	m_scoreMid = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_scoreMid->WhenPressed(new ElevatorMidCommand("ElevatorMidCommand"));

	m_scoreLow = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_scoreLow->WhenPressed(new ElevatorLowCommand("ElevatorLowCommand"));

	m_cargoShip = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_cargoShip->WhenPressed(new ElevatorCargoShipCommand("ElevatorCargoShipCommand"));

	m_elevatorManual = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, -0.25);
	m_elevatorManual->WhileHeld(new ElevatorJoystickCommand());

	// m_slideOpenLoop = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_X_AXIS, 0.25);
	// m_slideOpenLoop->WhileHeld(new HatchSlideJoystickCommand());

	m_toggleSlide = new JoystickButton(m_pOperatorStick, XBOX_RIGHT_BUMPER);
	m_toggleSlide->WhenPressed(new HatchSlideToggleCommand());

	// m_climberFeetOp = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	// m_climberFeetOp->ToggleWhenPressed(new ClimberToggleFeetCommand());

	m_scoreGamePiece = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_TRIGGER, 0.5);
	m_scoreGamePiece->WhenPressed(new ToolChangerScoreCommand());
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