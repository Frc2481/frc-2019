/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORSWITCHTOOLTOHATCHCOMMAND
#define SRC_ELEVATORSWITCHTOOLTOHATCHCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/Elevator.h"

class ElevatorSwitchToolToHatchCommand : public frc::InstantCommand {
 public:
  ElevatorSwitchToolToHatchCommand() : InstantCommand("ElevatorSwitchTooolToHatchCommand"){}
  void Initialize() override {
    CommandBase::m_pElevator->SwitchToHatch();
  }
};

#endif // SRC_ELEVATORSWITCHTOOLTOHATCHCOMMAND