#include "Robot.h"
#include "CommandBase.h"
#include "RobotParameters.h"
#include "Commands/SwerveDrivetrainZeroSteer.h"
#include "Commands/LineFollowerZeroEncoder.h"
#include "Commands/LineFollowerFollowLine.h"

Robot::Robot() : TimedRobot(1.0 / RobotParameters::k_updateRate) {
}

void Robot::RobotInit() {
	CommandBase::Init();

	SmartDashboard::PutData("SwerveDrivetrainZeroSteer", new SwerveDrivetrainZeroSteer());
	SmartDashboard::PutData("LineFollowerZeroEncoder", new LineFollowerZeroEncoder());
	SmartDashboard::PutData("LineFollowerFollowLine", new LineFollowerFollowLine());
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
