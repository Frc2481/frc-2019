/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_RETRACTINTAKEIFNEEDEDCOMMANDGROUP
#define SRC_RETRACTINTAKEIFNEEDEDCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/ToolChanger/ToolChangerRetractCommand.h"
#include <frc/commands/ConditionalCommand.h>

class SafeIntakeRetractCommandGroup : public frc::CommandGroup {
 public:
  SafeIntakeRetractCommandGroup() : CommandGroup("SafeIntakeRetractCommandGroup") {
    AddSequential(new CargoIntakeInCommand("CargoIntakeInCommand"));
  }
};

class RetractIntakeIfNeededCommand : public frc::ConditionalCommand {
 public:
  RetractIntakeIfNeededCommand() : frc::ConditionalCommand("RetractIntakeIfNeededCommand",
       new SafeIntakeRetractCommandGroup(), nullptr) {}
  bool Condition() {
    return !CommandBase::m_pCargoIntake->IsIntakeIn();
  }
};
#endif //SRC_RETRACTINTAKEIFNEEDEDCOMMANDGROUP