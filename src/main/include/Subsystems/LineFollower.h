#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <frc/WPILib.h>
#include "RobotParameters.h"
#include "networktables/NetworkTableInstance.h"
#include "Utils/MotorPositionController.h"

#define LIMELIGHT_FOV_YAW 54

class LineFollower : public frc::Subsystem {
public:
    LineFollower();
    ~LineFollower();

    virtual void InitDefaultCommand();
    virtual void Periodic();

    void updateTargetPose();
    double getTargetPos();
    double getTargetVel();
    void zeroEncoder();
    void updateMotorController();

private:
    std::shared_ptr<nt::NetworkTable> m_pLimeLightTable;
    double m_targetPos;
    double m_targetVel;
    bool m_targetValid;
    TalonSRX* m_pLineFollowerMotor;
    MotorPositionController* m_pLineFollowerMotorController;
    CTREMagEncoder* m_pLineFollowerEncoder;
};

#endif // LINE_FOLLOWER_H
