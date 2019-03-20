// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_ELEVATORHOMECOMMAND
// #define SRC_ELEVATORHOMECOMMAND 

// #include <frc/commands/Command.h>
// #include "CommandBase.h"

// class ElevatorHomeCommand : public frc::Command {
//  private:

//  public:
//   ElevatorHomeCommand() : Command("ElevatorHomeCommand"){
//     }
//   void Initialize() override {
//     CommandBase::m_pElevator->SetOpenLoopSpeed(-0.75); //might need to change direction
//   }
//   bool IsFinished() override {
//     return CommandBase::m_pElevator->IsReverseLimitSwitchClosed();
//   }
//   void End() override {
//    CommandBase::m_pElevator->SetOpenLoopSpeed(0); 
//    CommandBase::m_pElevator->ZeroElevatorEncoder();
//   }
//   void Interrupted() override {
//     End();
//   }
// };

// #endif // SRC_ELEVATORHOMECOMMAND