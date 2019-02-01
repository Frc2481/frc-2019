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

class Elevator : public frc::Subsystem {
 private:
  TalonSRX* m_masterElevator;
  TalonSRX* m_slaveElevator;
  frc::Solenoid* m_elevatorSlide;

  bool m_isElevatorZeroed;
  bool m_isSlideForward;
  
  double m_elevatorPosition;
  double m_desiredElevatorPosition;

 public:
  Elevator();
  void InitDefaultCommand() override;
  virtual void Periodic();

  void SetElevatorPosition(double setPos);
  void ZeroElevatorEncoder();

  double GetElevatorPosition();
  double GetElevatorError();

  bool IsElevatorEncoderZeroed();

  bool IsForwardLimitSwitchClosed();
  bool IsReverseLimitSwitchClosed();

  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);

  void SetOpenLoopSpeed(double speed);

  void SlideElevatorFront();
  void SlideElevatorBack();
  bool IsSlideFront();

};

#endif //SRC_ELEVATOR_H