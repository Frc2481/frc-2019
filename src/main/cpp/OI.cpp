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
#include "Commands/ToolChanger/ToolChangerHatchRetractCommand.h"
#include "Commands/CommandGroups/ScoreCommandGroup.h"
#include "Commands/HatchSlide/HatchSlideJoystickCommand.h"
#include "Commands/CommandGroups/ZeroAllCommandGroup.h"
#include "Commands/CommandGroups/RevertElevatorTestingCommandGroup.h"
#include "Commands/Climber/ClimberRaiseCommand.h"
#include "Commands/Climber/ClimberLowerCommand.h"
#include "Commands/CommandGroups/ClimbGuidesSequenceCommandGroup.h"
#include "Commands/CommandGroups/ClimbSequenceCommandGroup.h"
#include "Commands/Climber/ClimberReleaseWeightsCommand.h"
#include "Commands/Climber/CLimberDriveWithJoystickCommand.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroGyroCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeBackpedalCommandGroup.h"
#include "Commands/CommandGroups/StopAllCommand.h"
#include "Commands/LimeLight/LimeLightDriverDriveCommand.h"
#include "Commands/CommandGroups/AutoScoreHatchCommandGroup.h"
#include "Commands/CommandGroups/LimeLightAbortCommandGroup.h"
#include "Commands/CommandGroups/CargoAutoCommandGroup.h"

class LockOutWhenIntakingCommand : public ConditionalCommand {
  public:
  LockOutWhenIntakingCommand(Command* cmd) : ConditionalCommand(cmd->GetName(), cmd) {
  }
  bool Condition() {
    return !CommandBase::m_pCargoIntake->IsIntaking();
  }
}; 

OI::OI() {
	m_pDriverStick = new Joystick2481(DRIVER_XBOX_CONTROLLER_ID);
	m_pOperatorStick = new Joystick2481(OPERATOR_XBOX_CONTROLLER_ID);
		
//driver
	m_aDriverButton = new JoystickButton(m_pDriverStick, XBOX_A_BUTTON);
	m_bDriverButton = new JoystickButton(m_pDriverStick, XBOX_B_BUTTON);
	m_yDriverButton = new JoystickButton(m_pDriverStick, XBOX_Y_BUTTON);
	m_xDriverButton = new JoystickButton(m_pDriverStick, XBOX_X_BUTTON);
	m_backButton = new JoystickButton(m_pDriverStick, XBOX_BACK_BUTTON);

	m_acquireCargo = new AnalogJoystickButton(m_pDriverStick, XBOX_RIGHT_TRIGGER, 0.5);
	m_acquireCargo->WhenPressed(new AcquireCargoCommandGroup());

	m_acquireHatch = new JoystickButton(m_pDriverStick, XBOX_RIGHT_BUMPER);
	m_acquireHatch->WhenPressed(new PrepForAcquireHatchCommandGroup());
	m_acquireHatch->WhenReleased(new AcquireHatchCommandGroup());

    m_elevatorStow = new ComboJoystickButton(m_xDriverButton, m_backButton, false);
	m_elevatorStow->WhenPressed(new RevertElevatorTestingCommandGroup());

	m_climbL1ToL2 = new ComboJoystickButton(m_aDriverButton, m_backButton, true);
	m_climbL1ToL2->WhenPressed(new ClimbSequence1To2CommandGroup());

	m_climbL2ToL3 = new ComboJoystickButton(m_bDriverButton, m_backButton, true);
	m_climbL2ToL3->WhenPressed(new ClimbSequence2To3CommandGroup());

	m_climbL1ToL3 = new ComboJoystickButton(m_yDriverButton, m_backButton, true);
	m_climbL1ToL3->WhenPressed(new ClimbSequenceLevel3CommandGroup());

	m_pSetFieldFrameButton = new JoystickButton(m_pDriverStick, XBOX_LEFT_BUMPER);
	m_pSetFieldFrameButton->WhenPressed(new SwerveDrivetrainJoystickSetFieldFrame(false));
	m_pSetFieldFrameButton->WhenReleased(new SwerveDrivetrainJoystickSetFieldFrame(true));

	m_zeroGyro = new JoystickButton(m_pDriverStick, XBOX_START_BUTTON);
	m_zeroGyro->WhenPressed(new SwerveDrivetrainZeroGyroCommand());

	m_stopAll = new AnalogJoystickButton(m_pDriverStick, XBOX_LEFT_TRIGGER, 0.5);
	m_stopAll->WhenPressed(new StopAllCommand());
	
	m_AutoPlace = new ComboJoystickButton(m_bDriverButton, m_backButton, false);
	m_AutoPlace->WhileHeld(new AutoScoreHatchCommandGroup());
	// m_AutoPlace->WhenReleased(new LimeLightAbortCommandGroup());

	m_AutoPickup = new ComboJoystickButton(m_yDriverButton, m_backButton, false);
	m_AutoPickup->WhileHeld(new AutoAquireHatchCommandGroup());

//operator
	m_shiftWeights = new JoystickButton(m_pOperatorStick, XBOX_BACK_BUTTON);
	m_shiftWeights->WhenPressed(new ClimberReleaseWeightsCommand());

    m_scoreCargoShip = new JoystickButton(m_pOperatorStick, XBOX_X_BUTTON);
	m_scoreCargoShip->WhenPressed(new LockOutWhenIntakingCommand(new ElevatorCargoShipCommand("ElevatorCargoShipCommand")));

	m_scoreHigh = new JoystickButton(m_pOperatorStick, XBOX_Y_BUTTON);
	m_scoreHigh->WhenPressed(new LockOutWhenIntakingCommand(new ElevatorHighCommand("ElevatorHighCommand")));

	m_scoreMid = new JoystickButton(m_pOperatorStick, XBOX_B_BUTTON);
	m_scoreMid->WhenPressed(new LockOutWhenIntakingCommand(new ElevatorMidCommand("ElevatorMidCommand")));

	m_scoreLow = new JoystickButton(m_pOperatorStick, XBOX_A_BUTTON);
	m_scoreLow->WhenPressed(new LockOutWhenIntakingCommand(new ElevatorLowCommand("ElevatorLowCommand")));

	m_climberGuides = new JoystickButton(m_pOperatorStick, XBOX_START_BUTTON);
	m_climberGuides->WhenPressed(new ClimbGuidesSequenceCommandGroup());

	m_scoreGamePiece = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_TRIGGER, 0.5);
	m_scoreGamePiece->WhenPressed(new ScoreCommand());
	m_scoreGamePiece->WhenReleased(new ToolChangerHatchRetractCommand());
	
	m_elevatorManual = new AnalogJoystickButton(m_pOperatorStick, XBOX_LEFT_Y_AXIS, -0.25);
	m_elevatorManual->WhileHeld(new ElevatorJoystickCommand());

	m_enableSlide = new JoystickButton(m_pOperatorStick, XBOX_RIGHT_BUMPER);
	m_enableSlide->WhileHeld(new HatchSlideEnableCommand());

	m_slideOpenLoop = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_X_AXIS, 0.25);
	m_slideOpenLoop->WhileHeld(new HatchSlideJoystickCommand());
	
	m_hatchExtend = new AnalogJoystickButton(m_pOperatorStick, XBOX_RIGHT_TRIGGER, 0.5);
	m_hatchExtend->WhenPressed(new ToolChangerHatchExtendCommand());

	m_climberUp = new POVJoystickButton(m_pOperatorStick, 0, XBOX_DPAD_TOP);
	m_climberUp->WhileHeld(new ClimberRaiseCommand());

	m_climberDown = new POVJoystickButton(m_pOperatorStick, 0, XBOX_DPAD_BOTTOM);
	m_climberDown->WhileHeld(new ClimberLowerCommand());

	// m_backpedal = new JoystickButton(m_pOperatorStick, XBOX_LEFT_BUMPER);
	// m_backpedal->WhenPressed(new CargoIntakeBackpedalCommandGroup());
	// m_backpedal->WhenReleased(new CargoIntakeBallCommand(0));

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