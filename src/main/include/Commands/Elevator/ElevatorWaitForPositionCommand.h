// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_ELEVATORWAITFORPOSITIONCOMMAND
// #define SRC_ELEVATORWAITFORPOSITIONCOMMAND

// #include <frc/commands/Command.h>
// #include "CommandBase.h"

// class ElevatorWaitForPositionCommand : public frc::Command {
//   private:
//   bool m_isGoingUp = false;
//   double m_setPoint;
//  public:
//   ElevatorWaitForPositionCommand(double setPoint) : Command("ElevatorWaitForPositionCommand") {  
//     m_setPoint = setPoint;
//     m_isGoingUp = CommandBase::m_pElevator->GetVelocity() > 0;
//   }
//   bool IsFinished() override {
//     if((m_isGoingUp) && (m_setPoint - CommandBase::m_pElevator->GetElevatorPosition() < 1)){
//       return true;
//     }
//     else if((!m_isGoingUp) && (CommandBase::m_pElevator->GetElevatorPosition() - m_setPoint < 1)){
//       return true;
//     }
//     else{
//       return false;
//     }
//   }
// };

// #endif // SRC_ELEVATORWAITFORPOSITIONCOMMAND