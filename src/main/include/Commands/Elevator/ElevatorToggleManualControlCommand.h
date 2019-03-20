// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_ELEVATORTOGGLEMANUALCONTROLCOMMAND
// #define SRC_ELEVATORTOGGLEMANUALCONTROLCOMMAND

// #include <frc/commands/InstantCommand.h>
// #include "CommandBase.h"

// class ElevatorToggleManualControlCommand : public frc::InstantCommand {
//  public:
//   ElevatorToggleManualControlCommand() : InstantCommand("ElevatorToggleManualControlCommand"){}
//   void Initialize() override{
//     if(CommandBase::m_pElevator->IsElevatorManualEnabled()){
//       CommandBase::m_pElevator->DisableElevatorManual();
//     }
//     else{
//       CommandBase::m_pElevator->EnableElevatorManual();
//     }
//   }
// };

// #endif //SRC_ELEVATORTOGGLEMANUALCONTROLCOMMAND