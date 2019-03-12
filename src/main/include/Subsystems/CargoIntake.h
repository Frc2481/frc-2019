/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGO_INTAKE_H
#define SRC_CARGO_INTAKE_H

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"
#include "Components/CTREMagEncoder.h"

class CargoIntake : public frc::Subsystem {
private:
  VictorSPX* m_intakeMotor;
  TalonSRX* m_extendMotor;
  CTREMagEncoder* m_extendEncoder;
  frc::DigitalInput* m_beamBreak;
  double m_desiredPosition;
  bool m_isZeroed;

public:
  CargoIntake();
  void InitDefaultCommand() override;
  virtual void Periodic();
  void SetSpeedIn(double speed);
  void SetSpeedOut(double speed);
  void StopIntake();
  bool HasBall();
  void SetPosition(double pos);
  double GetPosition();
  double GetDesiredPosition();
  double GetCargoIntakeError();
  double GetVelocity();
  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);
  bool IsIntakeOut();
  bool IsBallIntaken();
  void SetOpenLoopSpeed(double speed);
  bool IsOnTarget();
  void ZeroCargoIntake();
};

#endif // SRC_CARGO_INTAKE_H