/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGER
#define SRC_TOOLCHANGER

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include "RobotMap.h"

class ToolChanger : public frc::Subsystem {
 private:
  frc::Solenoid* m_changer;
  bool m_isHatchFront;

 public:
  ToolChanger();
  void InitDefaultCommand() override;
  void SwitchToHatch();
  void SwitchToCargo();
  bool IsHatchToolFront();
};

#endif //SRC_TOOLCHANGER