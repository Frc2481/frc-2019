#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include "RobotMap.h"
#include <frc/WPILib.h>
#include <frc/LiveWindow/LiveWindow.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroSteer.h"
#include "Commands/HatchSlide/HatchSlideZeroCommand.h"
#include "Commands/Elevator/ElevatorZeroCommand.h"
// #include "Commands/VibrateCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchRetractCommand.h"
#include "Commands/CommandGroups/AcquireHatchCommandGroup.h"
#include "Commands/CommandGroups/AcquireCargoCommandGroup.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/CommandGroups/RevertElevatorTestingCommandGroup.h"
#include "Commands/CommandGroups/ZeroAllCommandGroup.h"
#include "Commands/Climber/ClimberToggleBigFootCommand.h"
#include "Commands/Climber/ClimberToggleLittleFeetCommand.h"
#include "Commands/CommandGroups/ClimbSequenceCommandGroup.h"
#include "Commands/Climber/ClimberGuidesCommand.h"
#include "Commands/ToolChanger/ToolChangerScoreCommand.h"
#include "Commands/CommandGroups/ZeroAllCommandGroup.h"
#include "Commands/Climber/ClimberReleaseWeightsCommand.h"
#include "Commands/Climber/ClimberSetPositionCommand.h"
#include "Commands/SetLEDsCommand.h"
#include "Commands/CommandGroups/StopAllCommand.h"
#include "Commands/CargoIntake/CargoIntakeExtensionCommand.h"
#include "Commands/CargoIntake/CargoIntakeZeroCommand.h"
#include "Commands/LimeLight/AutoLimeLightDriverDriveCommand.h"
#include "Commands/CommandGroups/AutoScoreHatchCommandGroup.h"
#include "Commands/CommandGroups/CargoAutoCommandGroup.h"
#include "Commands/SwerveDrivetrain/AutoDriveAndRotateCommand.h"
#include "Commands/CommandGroups/RocketAutoCommandGroup.h"
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroGyroCommand.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
	m_server = CameraServer::GetInstance();
}

void Robot::RobotInit() {
	CommandBase::Init();
	SmartDashboard::PutData("RocketAutoLeftCommandGroup", new RocketAutoLeftCommandGroup());
	SmartDashboard::PutData("CargoAutoRightCommandGroup", new CargoAutoRightCommandGroup());
	SmartDashboard::PutData("AutoLimeLightDriverDriveCommand" , new AutoScoreHatchCommandGroup());
	SmartDashboard::PutData("CargoIntakeExtendCommand", new CargoIntakeExtendCommand());
	SmartDashboard::PutData("CargoIntakeRetractCommand", new CargoIntakeRetractCommand());
	SmartDashboard::PutData("CargoIntakeZeroCommand", new CargoIntakeZeroCommand());

	SmartDashboard::PutData("LimeLightWaitForTargetSeenCommand", new LimeLightWaitForTargetSeenCommand());
	SmartDashboard::PutData("LimeLightWaitForLeftTargetSeenCommand", new LimeLightWaitForLeftTargetSeenCommand());

	SmartDashboard::PutData("Score Command", new ToolChangerScoreCommand());

	SmartDashboard::PutData("SetLEDsCommand", new SetLEDsCommand(5));

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("HatchSlideZeroCommand", new HatchSlideZeroCommand());
	SmartDashboard::PutData("ElevatorZeroCommand", new ElevatorZeroCommand());
	SmartDashboard::PutData("FreeCargoCommand", new ToolChangerFreeCargoCommand());
	SmartDashboard::PutData("HoldCargoCommand", new ToolChangerHoldCargoCommand());
	SmartDashboard::PutData("FreeHatchCommand", new ToolChangerFreeHatchCommand());
	SmartDashboard::PutData("HoldHatchCommand", new ToolChangerHoldHatchCommand());
	SmartDashboard::PutData("HatchExtendCommand", new ToolChangerHatchExtendCommand());
	SmartDashboard::PutData("HatchRetractCommand", new ToolChangerHatchRetractCommand());

	SmartDashboard::PutData("ClimberLittleFeetUpCommand", new ClimberLittleFeetUpCommand());
	SmartDashboard::PutData("ClimberLittleFeetDownCommand", new ClimberLittleFeetDownCommand());
	SmartDashboard::PutData("ClimberTiltBigFootCommand", new ClimberTiltBigFootCommand());
	SmartDashboard::PutData("ClimberUntiltBigFootCommand", new ClimberUntiltBigFootCommand());
	
	SmartDashboard::PutData("ClimberExtendGuidesCommand", new ClimberExtendGuidesCommand());
	SmartDashboard::PutData("ClimberRetractGuidesCommand", new ClimberRetractGuidesCommand());
	SmartDashboard::PutData("ClimberResetWeightsCommand", new ClimberResetWeightsCommand());
	
	SmartDashboard::PutData("ClimbSequence1To2CommandGroup", new ClimbSequence1To2CommandGroup());
	SmartDashboard::PutData("ClimbSequence2To3CommandGroup", new ClimbSequence2To3CommandGroup());
	SmartDashboard::PutData("ClimbSequenceLevel3CommandGroup", new ClimbSequenceLevel3CommandGroup());
	
	SmartDashboard::PutData("PrepForAcquireHatchCommandGroup", new PrepForAcquireHatchCommandGroup());
	SmartDashboard::PutData("AcquireHatchCommand", new AcquireHatchCommandGroup());
	SmartDashboard::PutData("AcquireCargoCommand", new AcquireCargoCommandGroup());

	SmartDashboard::PutData("ElevatorHighCommand", new ElevatorHighCommand("ElevatorHighCommand"));
	SmartDashboard::PutData("ElevatorMidCommand", new ElevatorMidCommand("ElevatorMidCommand"));
	SmartDashboard::PutData("ElevatorLowCommand", new ElevatorLowCommand("ElevatorLowCommand"));

	SmartDashboard::PutData("ElevatorCargoShipCommand", new ElevatorCargoShipCommand("ElevatorCargoShipCommand"));

	SmartDashboard::PutData("SetHasHatchCommand", new ToolChangerSetHasHatchCommand(true));
	SmartDashboard::PutData("SetHasCargoCommand", new ToolChangerSetHasCargoCommand(true));

	SmartDashboard::PutData("RevertElevatorCommand", new RevertElevatorTestingCommandGroup());

	SmartDashboard::PutData("ZeroAllCommandGroup", new ZeroAllCommandGroup());

	SmartDashboard::PutData("StopAllCommand", new StopAllCommand());
	
	SmartDashboard::PutData(frc::Scheduler::GetInstance());

	// m_pVibrate.reset(new VibrateCommand());

	m_usbCam1 = m_server->StartAutomaticCapture("cam1", 0);
	m_usbCam1.SetFPS(12);
	m_usbCam1.SetResolution(160, 90);
	
	m_zeroAll = new ZeroAllCommandGroup();
	m_hatchExtend = new ToolChangerHatchExtendCommand();
	m_elevatorCargoShip = new ElevatorCargoShipCommand("ElevatorLowCommand");
	m_freeCargo = new ToolChangerFreeCargoCommand();
	m_zeroAll->Start();

	frc::LiveWindow::GetInstance()->DisableAllTelemetry();

	m_leftCargoShipAuto = new CargoAutoLeftCommandGroup();
	// m_rightCargoShipAuto = new CargoAutoRightCommandGroup();
	m_leftRocketAuto = new RocketAutoLeftCommandGroup();
	// m_rightRocketAuto = new CargoAutoRightCommandGroup();
	
	m_autoChooser = new frc::SendableChooser<Command*>();
	m_autoChooser->SetDefaultOption("Left Cargoship Auto", m_leftCargoShipAuto);
	m_autoChooser->AddOption("Left Rocket Auto", m_leftRocketAuto);
	SmartDashboard::PutData("Auto Chooser", m_autoChooser);
	// m_autoChooser->AddOption("Right Cargoship Auto", RIGHT_CARGOSHIP);
	// m_autoChooser->AddOption("Right Rocket Auto", RIGHT_ROCKET);

	m_autoCommand = NULL;
}

void Robot::RobotPeriodic() {
	// double time0 = frc::Timer::GetFPGATimestamp();
	frc::Scheduler::GetInstance()->Run();
	// double time1 = frc::Timer::GetFPGATimestamp();
	// printf("dt = %0.1f ms\n", (time1 - time0) * 1000);
	// printf("LOGGER elevPos: %df, elevDesiredPos: %df, intakePos: %df\n", CommandBase::m_pElevator->GetElevatorPosition(), 
	// 		CommandBase::m_pElevator->GetDesiredPos(), CommandBase::m_pCargoIntake->GetPosition());
}

void Robot::AutonomousInit() {
	CommandBase::m_pSwerveDrivetrain->setGyroOffset(180);
	m_hatchExtend->Start();
	m_elevatorCargoShip->Start();
	m_freeCargo->Start();

	m_autoCommand = m_autoChooser->GetSelected();

	if(m_autoCommand != NULL) {
		m_autoCommand->Start();
	}
}

void Robot::DisabledInit() {
	CommandBase::m_pElevator->SetOpenLoopSpeed(0);
	CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0);
	CommandBase::m_pCargoIntake->SetSpeedIn(0);
	CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
	CommandBase::m_pClimber->SetOpenLoopSpeed(0);
	frc::Scheduler::GetInstance()->RemoveAll();
}


void Robot::TeleopInit() {
}

void Robot::AutonomousPeriodic() {
	// RobotPeriodic();
}

void Robot::TeleopPeriodic() {
	// RobotPeriodic();
	// if(CommandBase::m_pHatchSlide->IsVibratable()) {
	// 	m_pVibrate->Start();
	// 	CommandBase::m_pHatchSlide->ResetVibratable();
	// }

	SmartDashboard::PutBoolean("All Systems Go ", CommandBase::m_pSwerveDrivetrain->areAllSteerEncodersConnected() 
		&& CommandBase::m_pHatchSlide->SlideEncoderConnected() && CommandBase::m_pElevator->IsElevatorEncoderConnected());
}

void Robot::DisabledPeriodic() {
}

void Robot::TestPeriodic() {
}


#ifndef RUNNING_FRC_TESTS
int main() {
	return frc::StartRobot<Robot>();
}
#endif
