/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHPLACEMIDCOMMANDGROUP
#define SRC_HATCHPLACEMIDCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Subsystems/Elevator.h"
#include "HatchAtTargetCommand.h"
#include "ElevatorBaseCommand.h"

class HatchPlaceMidCommandGroup : public frc::CommandGroup {
 public:
  HatchPlaceMidCommandGroup() : CommandGroup("HatchPlaceMidCommandGroup") {
    Requires(CommandBase::m_pElevator.get());
    AddParallel(new ElevatorMidHatchCommand());
    AddSequential(new HatchAtTargetCommand());
    // Score Hatch
    AddParallel(new ElevatorLowHatchCommand());
    // Retract Score Mech
  }
};

#endif SRC_HATCHPLACEMIDCOMMANDGROUP