#ifndef ROBOT_H
#define ROBOT_H

#include <frc/WPILib.h>
#include "CommandBase.h"

class Robot : public frc::TimedRobot {
public:
	Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	std::unique_ptr<Command> m_pVibrate;
};

#endif // ROBOT_H
