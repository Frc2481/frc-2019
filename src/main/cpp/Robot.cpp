#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include "Commands/SwerveDrivetrainZeroSteer.h"
#include <frc/WPILib.h>
#include "Commands/HatchSlideZeroCommand.h"
#include "Commands/VibrateCommand.h"
#include "Commands/ElevatorHomeCommand.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
}

void Robot::RobotInit() {
	CommandBase::Init();

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("HatchSlideZeroCommand", new HatchSlideZeroCommand());
	SmartDashboard::PutData("ElevatorHomeCommand", new ElevatorHomeCommand());

	SmartDashboard::PutData(frc::Scheduler::GetInstance());

	m_pVibrate.reset(new VibrateCommand());
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
