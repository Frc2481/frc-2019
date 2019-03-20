// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_CONDITIONALINTAKECOMMANDGROUP
// #define SRC_CONDITIONALINTAKECOMMANDGROUP

// #include <frc/commands/CommandGroup.h>
// #include "Commands/Elevator/ElevatorRiseIfNeededCommand.h"
// #include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
// #include "Commands/ToolChanger/ToolChangerRetractCommand.h"
// #include "Commands/Elevator/ElevatorBaseCommand.h"
// #include <frc/commands/ConditionalCommand.h>

// class SafeIntakeExtendCommandGroup : public frc::CommandGroup {
//  public:
//   SafeIntakeExtendCommandGroup() : CommandGroup("SafeIntakeExtendCommandGroup") {
//     AddSequential(new ElevatorRiseForIntakeOutCommand()); //TODO check to see if height is acceptable
//     AddSequential(new CargoIntakeOutCommand("CargoIntakeOutCommand"));
//   }
// };

// class ExtendIntakeIfNeededCommand : public frc::ConditionalCommand {
//  public:
//   ExtendIntakeIfNeededCommand() : frc::ConditionalCommand("ExtendIntakeIfNeededCommand",
//        new SafeIntakeExtendCommandGroup(), nullptr) {}
//   bool Condition() {
//     return !CommandBase::m_pCargoIntake->IsIntakeOut();
//   }
// };

// #endif //SRC_CONDITIONALINTAKECOMMANDGROUP