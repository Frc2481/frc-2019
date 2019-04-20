#ifndef ROBOT_H
#define ROBOT_H

#include <frc/WPILib.h>
#include "CommandBase.h"

// enum Autos {
// 	LEFT = 1,
// 	RIGHT = 2,
// 	ROCKET = 4,
// 	CARGOSHIP = 8
// }

class Robot : public frc::TimedRobot {
public:
	Robot();
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	std::unique_ptr<Command> m_pVibrate;
	CameraServer* m_server;
	cs::UsbCamera m_usbCam1;
	Command* m_hatchExtend;
	Command* m_elevatorCargoShip;
	Command* m_zeroAll;
	Command* m_freeCargo;
	Command* m_autoCommand;
	Command* m_leftCargoShipAuto;
	Command* m_rightCargoShipAuto;
	Command* m_leftRocketAuto;
	Command* m_rightRocketAuto;
	// frc::SendableChooser<Autos>* m_posChooser;
	// frc::SendableChooser<Autos>* m_scoreChooser;
};

#endif // ROBOT_H
