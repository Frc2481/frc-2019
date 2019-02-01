/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORSWITCHTOOLTOCARGOCOMMAND
#define SRC_ELEVATORSWITCHTOOLTOCARGOCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"
#include "Subsystems/Elevator.h"

class ElevatorSwitchToolToCargoCommand : public frc::InstantCommand {
 public:
  ElevatorSwitchToolToCargoCommand() : InstantCommand("ElevatorSwitchToolToCargoCommand"){}
  void Initialize() override{
    CommandBase::m_pElevator->SwitchToCargo();
  }
};

#endif //SRC_ELEVATORSWITCHTOOLTOCARGOCOMMAND