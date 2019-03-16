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
#include <frc/Compressor.h>
#include "RobotParameters.h"

class HatchSlide : public frc::Subsystem {
 private:
  TalonSRX* m_motor;
  CTREMagEncoder* m_slideEncoder;
  frc::Counter *m_irSensorBright;
  frc::Counter *m_irSensorDim;
  frc::Solenoid* m_hatchSensor;
	frc::DigitalOutput* m_LED;

  double m_desiredSetpoint;
  double m_hatchPosition;
  bool m_isHatchZeroed;
  double m_pulseBright;
  double m_pulseDim;
  bool m_isVibratable;
  bool m_encoderConnected;
  bool m_hatchSlideUserEnabled;
  bool m_hatchSlideSafetyEnabled;
  bool m_oldTargetValid;
  bool m_hasResetOccurred;
  bool m_ledDesiredState;
  int m_noLineCounter;
  
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
  void EnableUserHatchSlide();
  void DisableUserHatchSlide();
  void EnableSafetyHatchSlide();
  void DisableSafetyHatchSlide();
  bool IsHatchSlideUserEnabled();
  bool IsHatchSlideSafetyEnabled();
  void SetOpenLoopSpeed(double speed);
  bool isZeroed();
  bool IsCargoLimitSwitchHit(); //NOTE: this is for tool changer but more convenient here
  bool IsHatchSeen();
  void SetLEDs(bool led);
  bool GetLEDs();
};

#endif //SRC_HATCH_SLIDE_H

//leds:

//HATCH
// sense: turn on     hatchslide sensor reads hatch   hatchslide
// have: turn off     end of acquire hatch            commandgroup

//CARGO
// sense: on           limit switch hit               hatchslide
// have: off           end of cargo intake motion     commandgroup

//on target: turn on    hatch slide on target         hatchslide
//released: turn off     end of score                 command