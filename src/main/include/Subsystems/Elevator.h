/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATOR_H
#define SRC_ELEVATOR_H

#include <frc/commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include <frc/WPILib.h>
#include "RobotParameters.h"
#include "RobotMap.h"
#include "Components/CTREMagEncoder.h"

class Elevator : public frc::Subsystem {
 public:
  Elevator();
  void InitDefaultCommand() override;
  virtual void Periodic();

  void SetElevatorPosition(double pos, bool isMoving);
  void ZeroElevatorEncoder();

  double GetElevatorPosition();
  double GetElevatorError();

  bool IsElevatorEncoderZeroed();

  bool IsForwardLimitSwitchClosed();
  bool IsReverseLimitSwitchClosed();

  void SetOpenLoopSpeed(double speed);

  bool IsElevatorEncoderConnected();
  bool IsPositionInProtectedZone(double pos);

  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);

  bool IsOnTarget();

 private:
  TalonSRX* m_masterElevator;
  VictorSPX* m_slaveElevator;
  CTREMagEncoder* m_elevatorEncoder;

  bool m_isElevatorZeroed;
  
  double m_elevatorPosition;
  double m_desiredElevatorPosition;
  bool m_encoderConnected;
};

#endif //SRC_ELEVATOR_H