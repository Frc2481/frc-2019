/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/LineFinder.h"
#include <math.h>
#include "Utils/MathConstants.h"
#include "Utils/Sign.h"

LineFinder::LineFinder()
    : Subsystem("LineFinder"),
    m_x(0),
    m_xVel(0),
    m_targetValid(false) {
    m_pLimeLightTable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
}

LineFinder::~LineFinder() { 
}

void LineFinder::InitDefaultCommand() {
}

void LineFinder::Periodic() {
    bool oldTargetValid = m_targetValid;
    m_targetValid = m_pLimeLightTable->GetNumber("tv", false);
    
    if(m_targetValid) {
        double targetYaw = m_pLimeLightTable->GetNumber("tx", 0) * MATH_CONSTANTS_PI / 180.0;
        double xOld = m_x;
        m_x = RobotParameters::k_limeLightHeight * tan(targetYaw);

        if(!oldTargetValid) {
            xOld = RobotParameters::k_limeLightHeight * tan(Sign::Sign(targetYaw) * LIMELIGHT_FOV_YAW / 2.0 * MATH_CONSTANTS_PI / 180.0);
        }

        m_xVel = (m_x - xOld) * RobotParameters::k_updateRate;
    }
    else {
        m_x = 0;
        m_xVel = 0;
    }

    frc::SmartDashboard::PutNumber("xTarget", m_x);
    frc::SmartDashboard::PutNumber("xVelTarget", m_xVel);
}

double LineFinder::getX() {
    return m_x;
}

double LineFinder::getXVel() {
    return m_xVel;
}
