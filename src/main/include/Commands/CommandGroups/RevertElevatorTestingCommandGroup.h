/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_REVERTELEVATORTESTINGCOMMANDGROUP
#define SRC_REVERTELEVATORTESTINGCOMMANDGROUP

#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include <frc/commands/CommandGroup.h>
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/Elevator/ElevatorRiseIfNeededCommand.h"

class RevertElevatorTestingCommandGroup : public frc::CommandGroup {
 public:
  RevertElevatorTestingCommandGroup() : CommandGroup("RevertElevatorTestingCommandGroup") {
    AddSequential(new ElevatorRiseForIntakeInCommand());
    AddSequential(new CargoIntakeInCommand("CargoIntakeBackCommand"));
    AddSequential(new ToolChangerHatchExtendCommand());
    AddSequential(new ElevatorCargoLowCommand("ElevatorCargoLowCommand"));

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_REVERTELEVATORTESTINGCOMMANDGROUP