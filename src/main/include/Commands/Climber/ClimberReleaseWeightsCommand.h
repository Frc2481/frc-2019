/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERRELEASEWEIGHTSCOMMAND
#define SRC_CLIMBERRELEASEWEIGHTSCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberReleaseWeightsCommand : public frc::InstantCommand {
 public:
  ClimberReleaseWeightsCommand() : InstantCommand("ClimberReleaseWeightsCommand") {}
  void Initialize() override {
    if(!CommandBase::m_pClimber->IsBigFootTilted()) {
      CommandBase::m_pClimber->ReleaseWeights();
    }
  }
};

class ClimberResetWeightsCommand : public frc::InstantCommand {
 public:
  ClimberResetWeightsCommand() : InstantCommand("ClimberResetWeightsCommand") {}
  void Initialize() override {
    if(!CommandBase::m_pClimber->IsBigFootTilted()) {
      CommandBase::m_pClimber->ResetWeights();
    }
  }
};

#endif //SRC_CLIMBERRELEASEWEIGHTSCOMMAND