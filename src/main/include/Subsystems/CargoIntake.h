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

  frc::DigitalInput* m_cargoPreIntakeSensor;
  // frc::Solenoid* m_extendIntakeSolenoid;
  double m_desiredPos;
  bool m_isZeroed;
  bool m_isBallIntaken;
  double m_scale;
  bool m_encoderConnected;

public:
  CargoIntake();
  void InitDefaultCommand() override;
  virtual void Periodic();
  void SetSpeedIn(double speed);
  void SetSpeedOut(double speed);
  void StopIntake();
  bool IsBallIntaken();
  void SetPosition(double pos);
  bool IsOnTarget();
  double GetPos();
  double GetDesiredPos();
  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);
  void ZeroCargoIntake();
  void SetOpenLoopSpeed(double speed);
  void SetSpeed(double scale);
};

#endif // SRC_CARGO_INTAKE_H