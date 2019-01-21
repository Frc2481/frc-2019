/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCH_SLIDE_H
#define SRC_HATCH_SLIDE_H

#include <frc/commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include <frc/WPILib.h>

class HatchSlide : public frc::Subsystem {
 private:
  TalonSRX* m_motor;
  double m_desiredSetpoint;
  double m_hatchPosition;
  bool m_isHatchZeroed;

 public:
  HatchSlide();
  void InitDefaultCommand() override;
  virtual void Periodic();
  void setSetPoint(int value);
  void ZeroHatchPosition();
  double GetHatchPosition();
  int ConvertInchesToTicks(double inches);
  double GetDesiredPos();
};

#endif //SRC_HATCH_SLIDE_H