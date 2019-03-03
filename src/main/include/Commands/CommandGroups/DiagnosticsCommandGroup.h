/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_DIAGNOSTICSCOMMANDGROUP
#define SRC_DIAGNOSTICSCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
// #include "Commands/SwerveDrivetrain/SwerveDrivetrainDiagnosticsCommand.h"
class DiagnosticsCommandGroup : public frc::CommandGroup {
 public:
  DiagnosticsCommandGroup() : CommandGroup("DiagnosticsCommandGroup.h"){
    // AddParallel()
  }
};
#endif //SRC_DIAGNOSTICSCOMMANDGROUP
