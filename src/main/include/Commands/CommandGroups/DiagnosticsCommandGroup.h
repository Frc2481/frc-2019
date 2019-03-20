// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_DIAGNOSTICSCOMMANDGROUP
// #define SRC_DIAGNOSTICSCOMMANDGROUP

// #include <frc/commands/CommandGroup.h>
// #include "Commands/SwerveDrivetrain/SwerveDrivetrainDiagnosticsCommand.h"
// #include "Commands/HatchSlide/HatchSlideDiagnosticsCommand.h"
// #include "Commands/CargoIntake/CargoIntakeDiagnosticsCommand.h"
// #include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
// #include "Commands/Elevator/ElevatorDiagnosticsCommand.h"
// #include "Commands/Elevator/ElevatorBaseCommand.h"
// #include "Commands/Climber/ClimberDiagnosticsCommand.h"

// class DiagnosticsCommandGroup : public frc::CommandGroup {
//  public:
//   DiagnosticsCommandGroup() : CommandGroup("DiagnosticsCommandGroup") {
//     AddSequential(new SwerveDrivetrainDiagnosticsCommand());
//     AddSequential(new ElevatorDiagnosticsCommand());
//     AddSequential(new ElevatorMidCommand("ElevatorMidCommand"));
//     AddSequential(new CargoIntakeDiagnosticsCommand());
//     AddSequential(new CargoIntakeInCommand("CargoIntakeInCommand"));
//     AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
//     AddSequential(new HatchSlideDiagnosticsCommand());
//     AddSequential(new ClimberDiagnosticsCommand());
//   }
// };

// #endif //SRC_DIAGNOSTICSCOMMANDGROUP