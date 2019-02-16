/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSCORECOMMAND
#define SRC_TOOLCHANGERSCORECOMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/ToolChanger.h"
#include "Subsystems/Elevator.h"

class ToolChangerScoreCommand : public frc::InstantCommand {
 public:
  ToolChangerScoreCommand() : InstantCommand("ToolChangerScoreCommand") {}
  void Initialize() override {
    if(CommandBase::m_pToolChanger->HasHatch()) {
      CommandBase::m_pToolChanger->ExtendHatch();
      Wait(0.3);
      CommandBase::m_pToolChanger->FreeHatch();
      CommandBase::m_pToolChanger->RetractHatch();
    }
    else {
      CommandBase::m_pToolChanger->FreeCargo();
      CommandBase::m_pToolChanger->ExtendHatch();
      CommandBase::m_pToolChanger->RetractHatch();
    }
  }
};

#endif //SRC_TOOLCHANGERSCORECOMMAND