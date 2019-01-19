#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include "Commands/SwerveDrivetrainZeroSteer.h"
#include <frc/WPILib.h>
#include "Commands/TankDrivetrainZeroPose.h"
#include "Commands/TankDrivetrainFollowPath.h"
#include "Commands/TankDrivetrainCalibrate.h"
#include "Commands/TankDrivetrainRotateToAngle.h"
#include "Commands/HatchSlideZeroCommand.h"
#include "Commands/VibrateCommand.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
}

void Robot::RobotInit() {
	CommandBase::Init();

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("TankDrivetrainZeroPose", new TankDrivetrainZeroPose());
	SmartDashboard::PutData("HatchSlideZeroCommand", new HatchSlideZeroCommand());

	std::vector<TankDrivePathGenerator::waypoint_t> waypoints;
	waypoints.push_back(TankDrivePathGenerator::waypoint_t {0, 0, 0, 0});
	waypoints.push_back(TankDrivePathGenerator::waypoint_t {0, 250, 0, 0});

	SmartDashboard::PutData("TankDrivetrainFollowPath", new TankDrivetrainFollowPath(waypoints, false, 5));

	SmartDashboard::PutData("TankDrivetrainCalibrate", new TankDrivetrainCalibrate());

	SmartDashboard::PutData("TankDrivetrainRotateToAngle", new TankDrivetrainRotateToAngle(180));

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

	if(CommandBase::m_pLineFinder->isVibratable()) {
		m_pVibrate->Start();
		CommandBase::m_pLineFinder->resetVibratable();
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
