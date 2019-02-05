#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include <frc/WPILib.h>
#include "Commands/SwerveDrivetrain/SwerveDrivetrainZeroSteer.h"
#include "Commands/HatchSlide/HatchSlideZeroCommand.h"
#include "Commands/Elevator/ElevatorZeroCommand.h"
#include "Commands/VibrateCommand.h"
#include "Commands/Elevator/ElevatorHomeCommand.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
	m_server = CameraServer::GetInstance();
}

void Robot::RobotInit() {
	CommandBase::Init();

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("HatchSlideZeroCommand", new HatchSlideZeroCommand());
	SmartDashboard::PutData("ElevatorHomeCommand", new ElevatorHomeCommand());
	SmartDashboard::PutData("ElevatorZeroCommand", new ElevatorZeroCommand());

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
