/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBER_H
#define SRC_CLIMBER_H

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h"
#include "RobotParameters.h"

class Climber : public frc::Subsystem {
 private:
  rev::CANSparkMax* m_climber;
  rev::CANPIDController m_pidController;

 public:
  Climber();
  void InitDefaultCommand() override;
  void ClimberRetract();
  void ClimberLevel2();
  void ClimberLevel3();
  double ConvertInchesToTicks(int inches);
};

#endif //SRC_CLIMBER_H