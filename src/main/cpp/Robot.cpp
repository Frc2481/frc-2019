#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include <frc/WPILib.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroSteer.h"
#include "Commands/HatchSlide/HatchSlideZeroCommand.h"
#include "Commands/Elevator/ElevatorZeroCommand.h"
#include "Commands/VibrateCommand.h"
#include "Commands/Elevator/ElevatorHomeCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include "Commands/CommandGroups/AcquireHatchCommandGroup.h"
#include "Commands/CommandGroups/AcquireCargoCommandGroup.h"
#include "Commands/ToolChanger/ToolChangerScoreHatchCommandGroup.h"
#include "Commands/ToolChanger/ToolChangerScoreCargoCommandGroup.h"
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/CommandGroups/RevertElevatorTestingCommandGroup.h"
#include "Commands/CargoIntake/CargoIntakeZeroCommand.h"
#include "Commands/CommandGroups/ZeroAllCommandGroup.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
	m_server = CameraServer::GetInstance();
}

void Robot::RobotInit() {
	CommandBase::Init();

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("HatchSlideZeroCommand", new HatchSlideZeroCommand());
	SmartDashboard::PutData("ElevatorHomeCommand", new ElevatorHomeCommand());
	SmartDashboard::PutData("ElevatorZeroCommand", new ElevatorZeroCommand());
	SmartDashboard::PutData("FreeCargoCommand", new ToolChangerFreeCargoCommand());
	SmartDashboard::PutData("HoldCargoCommand", new ToolChangerHoldCargoCommand());
	SmartDashboard::PutData("FreeHatchCommand", new ToolChangerFreeHatchCommand());
	SmartDashboard::PutData("HoldHatchCommand", new ToolChangerHoldHatchCommand());
	SmartDashboard::PutData("HatchExtendCommand", new ToolChangerHatchExtendCommand());
	SmartDashboard::PutData("HatchRetractCommand", new ToolChangerRetractCommand());

	SmartDashboard::PutData("CargoIntakeInCommand", new CargoIntakeInCommand("CargoIntakeInCommand"));
	SmartDashboard::PutData("CargoIntakeOutCommand", new CargoIntakeOutCommand("CargoIntakeOutCommand"));


	SmartDashboard::PutData("AcquireHatchCommand", new AcquireHatchCommandGroup());
	SmartDashboard::PutData("AcquireCargoCommand", new AcquireCargoCommandGroup());
	SmartDashboard::PutData("ScoreHatchCommand", new ToolChangerScoreHatchCommandGroup());
	SmartDashboard::PutData("ScoreCargoCommand", new ToolChangerScoreCargoCommandGroup());

	SmartDashboard::PutData("ElevatorHighCommand", new ElevatorHighCommand("ElevatorHighCommand"));
	SmartDashboard::PutData("ElevatorMidCommand", new ElevatorMidCommand("ElevatorMidCommand"));
	SmartDashboard::PutData("ElevatorLowCommand", new ElevatorLowCommand("ElevatorLowCommand"));

	SmartDashboard::PutData("ElevatorCargoShipCommand", new ElevatorCargoShipCommand("ElevatorCargoShipCommand"));

	SmartDashboard::PutData("SetHasHatchCommand", new ToolChangerSetHasHatchCommand(true));
	SmartDashboard::PutData("SetHasCargoCommand", new ToolChangerSetHasCargoCommand(true));

	SmartDashboard::PutData("RevertElevatorCommand", new RevertElevatorTestingCommandGroup());

	SmartDashboard::PutData("CargoIntakeZeroCommand", new CargoIntakeZeroCommand());
	
	SmartDashboard::PutData("ZeroAllCommandGroup", new ZeroAllCommandGroup());
	
	SmartDashboard::PutData(frc::Scheduler::GetInstance());

	m_pVibrate.reset(new VibrateCommand());

	m_usbCam1 = m_server->StartAutomaticCapture("cam1", 0);
	m_usbCam1.SetFPS(15);
	m_usbCam1.SetResolution(320, 180);

	m_usbCam2 = m_server->StartAutomaticCapture("cam2", 1);
	m_usbCam2.SetFPS(15);
	m_usbCam2.SetResolution(320, 180);
}

void Robot::AutonomousInit() {
}

void Robot::DisabledInit() {
	CommandBase::m_pElevator->SetOpenLoopSpeed(0);
	CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
	CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0);
	CommandBase::m_pCargoIntake->SetSpeedIn(0);
}

void Robot::TeleopInit() {
}

void Robot::AutonomousPeriodic() {
	CommandBase::Periodic();
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	CommandBase::Periodic();

	if(CommandBase::m_pHatchSlide->IsVibratable()) {
		m_pVibrate->Start();
		CommandBase::m_pHatchSlide->ResetVibratable();
	}

	SmartDashboard::PutBoolean("All Systems Go ", CommandBase::m_pSwerveDrivetrain->areAllSteerEncodersConnected() 
		&& CommandBase::m_pHatchSlide->SlideEncoderConnected() && CommandBase::m_pElevator->IsElevatorEncoderConnected());
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	CommandBase::Periodic();

	frc::SmartDashboard::PutBoolean("ball intook", CommandBase::m_pCargoIntake->IsBallIntaken());
}

void Robot::TestPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	CommandBase::Periodic();
}

#ifndef RUNNING_FRC_TESTS
int main() {
	return frc::StartRobot<Robot>();
}
#endif
