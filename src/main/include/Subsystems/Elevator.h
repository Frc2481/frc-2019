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
  double GetDesiredPos();
  double GetVelocity();
  
  bool IsElevatorEncoderZeroed();

  bool IsForwardLimitSwitchClosed();
  bool IsReverseLimitSwitchClosed();

  void SetOpenLoopSpeed(double speed);
  void SetMasterOpenLoopSpeed(double speed);
  void SetSlaveOpenLoopSpeed(double speed);  
  void SetFollower();

  bool IsElevatorEncoderConnected();
  bool IsPositionInProtectedZone(double pos);

  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);

  bool IsOnTarget();
  void EnableElevatorManual();
  void DisableElevatorManual();
  bool IsElevatorManualEnabled();

 private:
  TalonSRX* m_masterElevator;
  TalonSRX* m_slaveElevator;
  // VictorSPX* m_slaveElevator; // make sure to change back
  CTREMagEncoder* m_elevatorEncoder;

  bool m_isMasterZeroed;
  
  double m_elevatorPosition;
  double m_desiredElevatorPosition;
  bool m_encoderConnected;
  bool m_isElevatorManualEnabled;
};

#endif //SRC_ELEVATOR_H