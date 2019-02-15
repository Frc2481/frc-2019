/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORSLIDETOPOSITIONCOMMAND
#define SRC_ELEVATORSLIDETOPOSITIONCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/Elevator.h"

class ElevatorSlideToPositionCommand : public frc::InstantCommand {
 private:
 Elevator::elevator_slide_position m_position;
 public:
  ElevatorSlideToPositionCommand(Elevator::elevator_slide_position position) : InstantCommand("ElevatorSlideToPositionCommand") {
    m_position = position;
  }
  void Initialize() override {
    CommandBase::m_pElevator->SetElevatorSlidePosition(m_position);
  }
};

#endif // SRC_ELEVATORSLIDETOPOSITIONCOMMAND