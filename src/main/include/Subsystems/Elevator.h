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
  enum elevator_slide_position {
    FRONT,
    MID,
    BACK
  };

  Elevator();
  void InitDefaultCommand() override;
  virtual void Periodic();

  void SetElevatorPosition(double pos);
  void ZeroElevatorEncoder();

  double GetElevatorPosition();
  double GetElevatorError();

  bool IsElevatorEncoderZeroed();

  bool IsForwardLimitSwitchClosed();
  bool IsReverseLimitSwitchClosed();

  void SetOpenLoopSpeed(double speed);

  void SetElevatorSlidePosition(elevator_slide_position pos);
  elevator_slide_position GetElevatorSlidePosition();

  bool IsElevatorEncoderConnected();

  double ConvertTicksToInches(int ticks);
  int ConvertInchesToTicks(double inches);

 private:
  TalonSRX* m_masterElevator;
  VictorSPX* m_slaveElevator;
  frc::DoubleSolenoid* m_elevatorSlideA;
  frc::DoubleSolenoid* m_elevatorSlideB;
  CTREMagEncoder* m_elevatorEncoder;

  bool m_isElevatorZeroed;
  bool m_isSlideForward;
  
  double m_elevatorPosition;
  double m_desiredElevatorPosition;
  bool m_encoderConnected;

  elevator_slide_position m_slidePos;
};

#endif //SRC_ELEVATOR_H