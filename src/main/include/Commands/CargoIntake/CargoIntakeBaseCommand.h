// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_CARGOINTAKEBASECOMMAND
// #define SRC_CARGOINTAKEBASECOMMAND

// #include <frc/commands/Command.h>
// #include <frc/commands/CommandGroup.h>
// #include "CommandBase.h"
// #include "RobotParameters.h"

// template <int INTAKE_POS>
// class CargoIntakeBaseCommand : public frc::Command {
//  public:
//   CargoIntakeBaseCommand(std::string name) : Command(name) {
//     Requires(CommandBase::m_pCargoIntake.get());
//   }
//   void Initialize() override {
//     if(IsPositionSetPointAllowed()) {
//       // printf("set pos first time *************\n");
//       CommandBase::m_pCargoIntake->SetPosition(INTAKE_POS);
//     }
//     // printf("command is running *************\n");
//   }
//   // void Execute() override {
//     // if(TimeSinceInitialized() > 3 && INTAKE_POS == 0) {
//     //   CommandBase::m_pCargoIntake->SetOpenLoopSpeed(-0.8);
//     // }
//   // }
  
//   bool IsFinished() override {
//     return CommandBase::m_pCargoIntake->IsOnTarget();
//   }

//   bool IsPositionSetPointAllowed() {
//     //if elevator in protected zone, don't move
//     if(CommandBase::m_pElevator->IsPositionInProtectedZone(CommandBase::m_pElevator->GetElevatorPosition())) {
//       return false;
//     }
//     else {
//       return true;
//     }
//     // printf("GetElevatorPosition IsPositionSetPointAllowed %0.01f\n", CommandBase::m_pElevator->GetElevatorPosition());
//   }

//   void End() override {
//     CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0); //slide
//     printf("finished cargo intake\n");
//   }
//   void Interrupted() override {
//     End();
//   }
// };

// template <int INTAKE_POS>
// class CargoIntakeBaseCommandGroup : public CommandGroup {
//   public:
//   CargoIntakeBaseCommandGroup(std::string name) : CommandGroup(name) {
//     // AddSequential(new ElevatorRiseForIntakeCommand());
//     AddSequential(new CargoIntakeBaseCommand<INTAKE_POS>(name));
//   }
// }; 

// typedef CargoIntakeBaseCommandGroup<17700> CargoIntakeOutCommand;
// typedef CargoIntakeBaseCommandGroup<0> CargoIntakeInCommand;

// #endif //SRC_CARGOINTAKEBASECOMMAND