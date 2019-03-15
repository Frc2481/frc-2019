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
#include "Components/CTREMagEncoder.h"

class HatchSlide : public frc::Subsystem {
 private:
  TalonSRX* m_motor;
  CTREMagEncoder* m_slideEncoder;
  frc::Counter *m_irSensorBright;
  frc::Counter *m_irSensorDim;
  double m_desiredSetpoint;
  double m_hatchPosition;
  bool m_isHatchZeroed;
  double m_pulseBright;
  double m_pulseDim;
  bool m_isVibratable;
  bool m_encoderConnected;
  bool m_hatchSlideEnabled;
  bool m_oldTargetValid;
  bool m_hasResetOccurred;
  
 public:
  HatchSlide();
  void InitDefaultCommand() override;
  virtual void Periodic();
  void setSetPoint(int value);
  void ZeroHatchPosition();
  double GetHatchPosition();
  int ConvertInchesToTicks(double inches);
  double ConvertTicksToInches(int ticks);
  double GetSuggestedPos();
  double GetBrightPulseDist();
  double GetDimPulseDist();
  bool IsLineVisible();
  bool IsSlideOnTarget();
  bool IsVibratable();
  void ResetVibratable();
  bool SlideEncoderConnected();
  void EnableHatchSlide();
  void DisableHatchSlide();
  bool IsHatchSlideEnabled();
  void SetOpenLoopSpeed(double speed);
  bool isZeroed();
  bool IsLimitSwitchHit(); //NOTE: this is for cargo intake and on the tool changer but more convenient here
};

#endif //SRC_HATCH_SLIDE_H