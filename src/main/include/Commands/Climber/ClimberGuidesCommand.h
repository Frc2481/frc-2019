/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERGUIDESCOMMAND
#define SRC_CLIMBERGUIDESCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberRetractGuidesCommand : public frc::InstantCommand {
 public:
  ClimberRetractGuidesCommand() : InstantCommand("ClimberRetractGuidesCommand"){}
  void Initialize() override{
    CommandBase::m_pClimber->RetractGuides();
  }
};

class ClimberExtendGuidesCommand : public frc::InstantCommand{
  public:
  ClimberExtendGuidesCommand() : InstantCommand("ClimberExtendGuidesCommand"){}
  void Initialize() override{
    CommandBase::m_pClimber->ExtendGuides();
  }
};

#endif //SRC_CLIMBERGUIDESCOMMAND