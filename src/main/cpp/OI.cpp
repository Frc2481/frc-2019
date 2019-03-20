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
#include "Commands/HatchSlide/HatchSlideEnableCommand.h"
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
#include "Commands/Climber/ClimberToggleManualControlCommand.h"
#include "Commands/Elevator/ElevatorToggleManualControlCommand.h"
#include "Commands/CommandGroups/ZeroAllCommandGroup.h"
#include "Commands/CommandGroups/ElevatorStowCommandGroup.h"
#include "Commands/CommandGroups/RevertElevatorTestingCommandGroup.h"
#include "Commands/Climber/ClimberRaiseCommand.h"
#include "Commands/Climber/ClimberLowerCommand.h"
#include "Commands/CommandGroups/ClimbGuidesSequenceCommandGroup.h"
#include "Commands/CommandGroups/ClimbSequenceCommandGroup.h"
#include "Commands/Climber/ClimberReleaseWeightsCommand.h"
#include "Commands/Climber/CLimberDriveWithJoystickCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroGyroCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);
		
//driver
	m_acquireCargo = new AnalogJoystickButton(m_pDriverStick, XBOX_RIGHT_TRIGGER, 0.5);
	m_acquireCargo->WhenPressed(new AcquireCargoCommandGroup());

	m_acquireHatch = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	m_acquireHatch->WhenPressed(new PrepForAcquireHatchCommandGroup());
	m_acquireHatch->WhenReleased(new AcquireHatchCommandGroup());
	// m_acquireHatch->WhenPressed(new AcquireHatchCommandGroup());

    m_elevatorStow = new JoystickButton(m_pDriverStick, XBOX_X_BUTTON);
	m_elevatorStow->WhenPressed(new RevertElevatorTestingCommandGroup());

	m_climbL1ToL2 = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	m_climbL1ToL2->WhenPressed(new ClimbSequence1To2CommandGroup());

	m_climbL2ToL3 = new JoystickButton(m_pDriverStick, XBOX_B_BUTTON);
	m_climbL2ToL3->WhenPressed(new ClimbSequence2To3CommandGroup());

	m_climbL1ToL3 = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	m_climbL1ToL3->WhenPressed(new ClimbSequenceLevel3CommandGroup());

	m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(false));
	m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(true));

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);
	m_zeroGyro->WhenPressed(new SwerveDrivetrainZeroGyroCommand());

//operator
	m_shiftWeights = new JoystickButton(m_pOperatorStick, XBOX_BACK_BUTTON);
	m_shiftWeights->WhenPressed(new ClimberReleaseWeightsCommand());
	// m_zeroGyro = new JoystickButton(m_pOperatorStick, XBOX_START_BUTTON);
	// m_zeroGyro->WhenPressed(new SwerveDrivetrainZeroGyroCommand());	

    m_elevatorStowOp = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_elevatorStowOp->WhenPressed(new RevertElevatorTestingCommandGroup());

	m_scoreHighOp = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_scoreHighOp->WhenPressed(new ElevatorHighCommand("ElevatorHighCommand"));

	m_scoreMidOp = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_scoreMidOp->WhenPressed(new ElevatorMidCommand("ElevatorMidCommand"));

	m_scoreLowOp = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_scoreLowOp->WhenPressed(new ElevatorLowCommand("ElevatorLowCommand"));

	m_climberGuides = new JoystickButton(m_pOperatorStick, XBOX_START_BUTTON);
	m_climberGuides->WhenPressed(new ClimbGuidesSequenceCommandGroup());

	m_scoreGamePiece = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_TRIGGER, 0.5);
	m_scoreGamePiece->WhenPressed(new ToolChangerScoreCommand());

	// m_climbL1ToL2 = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	// m_climbL1ToL2->WhenPressed(new ClimbSequence1To2CommandGroup());

	// m_climbL2ToL3 = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	// m_climbL2ToL3->WhenPressed(new ClimbSequence2To3CommandGroup());

	// m_climbL1ToL3 = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	// m_climbL1ToL3->WhenPressed(new ClimbSequenceLevel3CommandGroup());
	// m_climberLittleFeet = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	// m_climberLittleFeet->ToggleWhenPressed(new ClimberToggleLittleFeetCommand());

	// m_climberBigFoot = new JoystickButton(m_pOperatorStick, XBOX_RIGHT_BUMPER);
	// m_climberBigFoot->ToggleWhenPressed(new ClimberToggleBigFootCommand());
	
	m_elevatorManual = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_Y_AXIS, -0.25);
	m_elevatorManual->WhileHeld(new ElevatorJoystickCommand());

	// m_elevatorManual = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_Y_AXIS, -0.25);
	// m_elevatorManual->WhileHeld(new ClimberDriveWithJoystickCommand());

	m_toggleSlide = new JoystickButton(m_pOperatorStick, XBOX_RIGHT_BUMPER);
	m_toggleSlide->WhileHeld(new HatchSlideEnableCommand());

	m_slideOpenLoop = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_X_AXIS, 0.25);
	m_slideOpenLoop->WhileHeld(new HatchSlideJoystickCommand());
	
	// m_hatchExtend = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	// m_hatchExtend->WhenPressed(new ToolChangerHatchExtendCommand());

	m_climberUp = new POVJoystickButton(m_pOperatorStick, 0, XBOX_DPAD_TOP);
	m_climberUp->WhileHeld(new ClimberRaiseCommand());

	m_climberDown = new POVJoystickButton(m_pOperatorStick, 0, XBOX_DPAD_BOTTOM);
	m_climberDown->WhileHeld(new ClimberLowerCommand());

	m_backpedal = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	m_backpedal->WhenPressed(new CargoIntakeBallCommand(-1));
	m_backpedal->WhenReleased(new CargoIntakeBallCommand(0));

	m_intakeOut = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	m_intakeOut->WhenPressed(new CargoIntakeOutCommand("CargoIntakeOutCommand"));

	// m_climberFeetOp = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	// m_climberFeetOp->ToggleWhenPressed(new ClimberToggleFeetCommand());

//RoboRio
	m_userButton = new UserButton();
	m_userButton->WhenPressed(new ZeroAllCommandGroup());

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