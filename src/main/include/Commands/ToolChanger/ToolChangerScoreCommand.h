/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSCORECOMMAND
#define SRC_TOOLCHANGERSCORECOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerScoreCommand : public frc::InstantCommand {
 public:
  ToolChangerScoreCommand() : InstantCommand("ToolChangerScoreCommand") {}
  void Initialize() override {
    if(CommandBase::m_pToolChanger->HasHatch()) {
      CommandBase::m_pToolChanger->FreeCargo();
      Wait(0.1);
      CommandBase::m_pToolChanger->FreeHatch();
      Wait(0.3);
      CommandBase::m_pToolChanger->HoldCargo();
    }
    else {
      CommandBase::m_pToolChanger->FreeCargo();
      CommandBase::m_pToolChanger->ExtendHatch();
      Wait(0.3);
      CommandBase::m_pToolChanger->RetractHatch();
      // Wait(1.0);
      // CommandBase::m_pToolChanger->HoldCargo();
    }
    CommandBase::m_pHatchSlide->SetLEDs(false);
    CommandBase::m_pToolChanger->SetHasCargo(false);
    CommandBase::m_pToolChanger->SetHasHatch(false);
  }
};

    // state at end:
    // Elevator: elevatorBaseCommand
    // Cargo Intake: in
    // Cargo: Held
    // Hatch: Free
    // HatchExt: Retracted

#endif //SRC_TOOLCHANGERSCORECOMMAND