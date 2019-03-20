// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_ELEVATORSTOWCOMMANDGROUP
// #define SRC_ELEVATORSTOWCOMMANDGROUP

// #include <frc/commands/CommandGroup.h>
// #include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
// #include "Commands/Elevator/ElevatorBaseCommand.h"

// class ElevatorStowCommandGroup : public frc::CommandGroup {
//  public:
//   ElevatorStowCommandGroup() : CommandGroup("ElevatorStowCommandGroup"){
//     AddSequential(new ToolChangerHatchExtendCommand());
//     AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
//   }
// };

// #endif //SRC_ELEVATORSTOWCOMMANDGROUP