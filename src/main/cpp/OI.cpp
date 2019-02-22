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
#include "Commands/HatchSlide/HatchSlideToggleCommand.h"
#include "Commands/Climber/ClimberLevel2Command.h"
#include "Commands/Climber/ClimberLevel3Command.h"
#include "Commands/Climber/ClimberRetractCommand.h"
#include "Commands/Climber/ClimberToggleFeetCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroGyroCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);
	m_pTestStick = new Joystick2481(TEST_XBOX_CONTROLLER_ID);
	
//driver
	m_acquireCargo = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	m_acquireCargo->WhenPressed(new AcquireCargoCommandGroup());

	m_acquireHatch = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_acquireHatch->WhenPressed(new AcquireHatchCommandGroup());

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);
	m_zeroGyro->WhenPressed(new SwerveDrivetrainZeroGyroCommand());

    m_elevatorStow = new JoystickButton(m_pDriverStick, XBOX_X_BUTTON);
	m_elevatorStow->WhenPressed(new ElevatorStowCommand("ElevatorStowCommand"));

	m_climbLevel3 = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	// m_climbLevel3->WhenPressed(new ClimberLevel3Command());
	m_climbLevel3->WhenPressed(new ElevatorHighCommand("ElevatorHighCommand"));

	m_climbLevel2 = new JoystickButton(m_pDriverStick, XBOX_B_BUTTON);
	// m_climbLevel2->WhenPressed(new ClimberLevel2Command());
		m_climbLevel3->WhenPressed(new ElevatorMidCommand("ElevatorHighCommand"));


	m_climbRetract = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	// m_climbRetract->WhenPressed(new ClimberRetractCommand());
		m_climbLevel3->WhenPressed(new ElevatorLowCommand("ElevatorHighCommand"));


	// m_climberFeet = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	// m_climberFeet->ToggleWhenPressed(new ClimberToggleFeetCommand());

	// m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	// m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(true));
	// m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(false));

//operator
	m_scoreHigh = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_scoreHigh->WhenPressed(new AutoPlaceCommandGroup(new ElevatorHighCommand("ElevatorHighCommand")));

	m_scoreMid = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_scoreMid->WhenPressed(new AutoPlaceCommandGroup(new ElevatorMidCommand("ElevatorMidCommand")));

	m_scoreLow = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_scoreLow->WhenPressed(new AutoPlaceCommandGroup(new ElevatorLowCommand("ElevatorLowCommand")));

	m_cargoShip = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_cargoShip->WhenPressed(new AutoPlaceCommandGroup(new ElevatorCargoShipCommand("ElevatorCargoShipCommand")));

	m_elevatorRaise = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, -0.25); //right stick up
	m_elevatorRaise->WhileHeld(new ElevatorRaiseCommand());

	m_elevatorLower = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_Y_AXIS, 0.25); //right stick down
	m_elevatorLower->WhileHeld(new ElevatorLowerCommand());

	m_toggleSlide = new JoystickButton(m_pOperatorStick, XBOX_RIGHT_BUMPER);
	m_toggleSlide->WhenPressed(new HatchSlideToggleCommand());

	//CLIMBER MANUAL OPERATOR XBOX_LEFT_AXIS

	m_climberFeetOp = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	m_climberFeetOp->ToggleWhenPressed(new ClimberToggleFeetCommand());

	// TEST
	m_freeHatch = new JoystickButton(m_pTestStick, XBOX_B_BUTTON);
	m_freeHatch->WhenPressed(new ToolChangerFreeHatchCommand());

    m_holdHatch = new JoystickButton(m_pTestStick, XBOX_A_BUTTON);
	m_freeHatch->WhenPressed(new ToolChangerHoldHatchCommand());

    m_freeCargo = new JoystickButton(m_pTestStick, XBOX_Y_BUTTON);
	m_freeCargo->WhenPressed(new ToolChangerFreeCargoCommand());

    m_holdCargo = new JoystickButton(m_pTestStick, XBOX_X_BUTTON);
	m_holdCargo->WhenPressed(new ToolChangerHoldCargoCommand());

    m_extendHatch = new JoystickButton(m_pTestStick, XBOX_LEFT_BUMPER);
	m_extendHatch->WhenPressed(new ToolChangerHatchExtendCommand());

    m_retractHatch = new JoystickButton(m_pTestStick, XBOX_RIGHT_BUMPER);
	m_retractHatch->WhenPressed(new ToolChangerRetractCommand());

	m_intakeCargo = new JoystickButton(m_pTestStick, XBOX_RIGHT_TRIGGER);
	// m_intakeCargo->WhileHeld(new CargoIntakeBallCommand());
}

OI::~OI() {
	delete m_pDriverStick;
	m_pDriverStick = nullptr;

	delete m_pOperatorStick;
	m_pOperatorStick = nullptr;

	delete m_pTestStick;
	m_pTestStick = nullptr;

	delete m_pSetFieldFrameButton;
	m_pSetFieldFrameButton = nullptr;
}

Joystick2481* OI::GetDriverStick() {
	return m_pDriverStick;
}

Joystick2481* OI::GetOperatorStick() {
	return m_pOperatorStick;
}