/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef VISION_LINE_FINDER_H
#define VISION_LINE_FINDER_H

#include <frc/WPILib.h>
#include "RobotParameters.h"
#include "networktables/NetworkTableInstance.h"

#define LIMELIGHT_FOV_YAW 54

class VisionLineFinder : public frc::Subsystem {
public:
    VisionLineFinder();
    ~VisionLineFinder();

    virtual void InitDefaultCommand();
    virtual void Periodic();

    double getX();
    double getXVel();

private:
    std::shared_ptr<nt::NetworkTable> m_pLimeLightTable;
    double m_x;
    double m_xVel;
    bool m_targetValid;
};

#endif // VISION_LINE_FINDER_H
