// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_ELEVATORRISEIFNEEDEDCOMMAND
// #define SRC_ELEVATORRISEIFNEEDEDCOMMAND

// #include <frc/commands/ConditionalCommand.h>
// #include "CommandBase.h"
// #include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
// #include "Commands/Elevator/ElevatorBaseCommand.h"

// class ElevatorRiseForIntakeOutCommandGroup : public frc::CommandGroup {
//  public:
//   ElevatorRiseForIntakeOutCommandGroup() : CommandGroup("ElevatorRiseForIntakeOutCommandGroup") {
//     AddSequential(new ToolChangerHatchExtendCommand());
//     AddSequential(new ElevatorIntakeBallHeightCommand("ElevatorIntakeBallHeightCommand"));
//   }
// };

// class ElevatorRiseForIntakeOutCommand : public frc::ConditionalCommand {
//  public:
//   ElevatorRiseForIntakeOutCommand() : frc::ConditionalCommand("ElevatorRiseForIntakeOutCommand",
//        new ElevatorRiseForIntakeOutCommandGroup(), nullptr) {}
//   bool Condition() {
//     return !CommandBase::m_pCargoIntake->IsIntakeOut() && CommandBase::m_pElevator->GetElevatorPosition() < RobotParameters::k_elevatorCollisionMax;
//   }
// };

// class ElevatorRiseForIntakeInCommand : public frc::ConditionalCommand {
//  public:
//   ElevatorRiseForIntakeInCommand() : frc::ConditionalCommand("ElevatorRiseForIntakeInCommand",
//        new ElevatorRiseForIntakeOutCommandGroup(), nullptr) {}
//   bool Condition() {
//     return !CommandBase::m_pCargoIntake->IsIntakeIn() && CommandBase::m_pElevator->GetElevatorPosition() < RobotParameters::k_elevatorCollisionMax;
//   }
// };

// class ElevatorRiseForIntakeCommand : public frc::ConditionalCommand {
//  public:
//   ElevatorRiseForIntakeCommand() : frc::ConditionalCommand("ElevatorRiseForIntakeCommand",
//        new ElevatorRiseForIntakeOutCommandGroup(), nullptr) {}
//   bool Condition() {
//     return (!CommandBase::m_pCargoIntake->IsIntakeIn() || !CommandBase::m_pCargoIntake->IsIntakeOut()) 
//             && CommandBase::m_pElevator->GetElevatorPosition() < RobotParameters::k_elevatorCollisionMax;
//   }
// };

// #endif //SRC_ELEVATORRISEIFNEEDEDCOMMAND