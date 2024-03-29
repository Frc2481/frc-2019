/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERGUIDESSEQUENCECOMMANDGROUP
#define SRC_CLIMBERGUIDESSEQUENCECOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include <frc/commands/InstantCommand.h>
#include "Commands/Climber/ClimberGuidesCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/Elevator/ElevatorWaitForPositionCommand.h"
#include "CommandBase.h"

class ClimbGuidesSequenceCommandGroup : public frc::CommandGroup {
 public:
  ClimbGuidesSequenceCommandGroup() : CommandGroup("ClimbGuidesSequenceCommandGroup"){
    AddSequential(new ElevatorGuidesHeightCommand("ElevatorGuidesHeightCommand"));
    // AddSequential(new ElevatorWaitForPositionCommand(0)); // TODO set to the ElevatorInatakeBallHeightCommand Template
    AddSequential(new ClimberExtendGuidesCommand());
    AddSequential(new WaitCommand(0.5));
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
  }
};

#endif //SRC_CLIMBERGUIDESSEQUENCECOMMANDGROUP