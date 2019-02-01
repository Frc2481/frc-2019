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
#include "networktables/NetworkTableInstance.h"

class HatchSlide : public frc::Subsystem {
 private:
  TalonSRX* m_motor;
  frc::Counter *m_irSensor;
  double m_desiredSetpoint;
  double m_hatchPosition;
  bool m_isHatchZeroed;
  double m_pulse;
  bool m_isVibratable;

 public:
  HatchSlide();
  void InitDefaultCommand() override;
  virtual void Periodic();
  void setSetPoint(int value);
  void ZeroHatchPosition();
  double GetHatchPosition();
  int ConvertInchesToTicks(double inches);
  double ConvertTicksToInches(int ticks);
  double GetDesiredPos();
  double GetPulseDist();
  bool IsLineVisible();
  bool IsSlideOnTarget();
  bool IsVibratable();
  void ResetVibratable();
};

#endif //SRC_HATCH_SLIDE_H