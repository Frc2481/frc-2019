/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHPLACEONHIGHCOMMANDGROUP
#define SRC_HATCHPLACEONHIGHCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Subsystems/Elevator.h"
#include "HatchAtTargetCommand.h"
#include "ElevatorBaseCommand.h"

class HatchPlaceOnHighCommandGroup : public frc::CommandGroup {
 public:
  HatchPlaceOnHighCommandGroup() : Command("HatchPlaceOnHighCommandGroup") {
    Requires(CommandBase::m_pElevator.get());
    AddParallel(new ElevatorHighHatchCommand());
    AddSequential(new HatchAtTargetCommand());
    // Score Hatch
    AddParallel(new ElevatorLowHatchCommand());
    // Retract Score Mech
  }
};

#endif //SRC_HATCHPLACEONHIGHCOMMANDGROUP