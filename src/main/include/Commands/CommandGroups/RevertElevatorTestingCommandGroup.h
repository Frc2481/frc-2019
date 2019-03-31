/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_REVERTELEVATORTESTINGCOMMANDGROUP
#define SRC_REVERTELEVATORTESTINGCOMMANDGROUP

#include "Commands/Elevator/ElevatorBaseCommand.h"
#include <frc/commands/CommandGroup.h>
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/CargoIntake/CargoIntakeExtensionCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"

class RevertElevatorTestingCommandGroup : public frc::CommandGroup {
 public:
  RevertElevatorTestingCommandGroup() : CommandGroup("RevertElevatorTestingCommandGroup") {
    AddParallel(new ToolChangerHoldCargoCommand());
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
    AddSequential(new CargoIntakeRetractCommand());
    AddSequential(new CargoIntakeStopCommand());

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }
};

#endif //SRC_REVERTELEVATORTESTINGCOMMANDGROUP