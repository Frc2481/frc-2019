/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef LINE_FINDER_H
#define LINE_FINDER_H

#include <frc/WPILib.h>
#include "RobotParameters.h"
#include "networktables/NetworkTableInstance.h"

#define LIMELIGHT_FOV_YAW 54

class LineFinder : public frc::Subsystem {
public:
    LineFinder();
    ~LineFinder();

    virtual void InitDefaultCommand();
    virtual void Periodic();

    double getX();
    double getXVel();
    bool isVibratable();
    void resetVibratable();

private:
    std::shared_ptr<nt::NetworkTable> m_pLimeLightTable;
    double m_x;
    double m_xVel;
    bool m_targetValid;
    bool m_isVibratable;
};

#endif // LINE_FINDER_H
