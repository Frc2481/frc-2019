/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERTOGGLEMANUALCONTROLCOMMAND
#define SRC_CLIMBERTOGGLEMANUALCONTROLCOMMAND
 
#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberToggleManualControlCommand : public frc::InstantCommand {
 public:
  ClimberToggleManualControlCommand() : InstantCommand("ClimberToggleManualControlCommand"){}
  void Initialize() override{
    if(CommandBase::m_pClimber->IsClimberEnabled()){
      CommandBase::m_pClimber->DisableClimberManual();
    }
    else{
      CommandBase::m_pClimber->EnableClimberManual();
    }
  }
};

#endif //SRC_CLIMBERTOGGLEMANUALCONTROLCOMMAND