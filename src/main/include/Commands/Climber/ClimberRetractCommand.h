/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERRETRACTCOMMAND
#define SRC_CLIMBERRETRACTCOMMAND
#include <frc/commands/InstantCommand.h>
#include "Subsystems/Climber.h"

class ClimberRetractCommand : public frc::InstantCommand {
 public:
  ClimberRetractCommand() : InstantCommand("ClimberRetractCommand") {

  }
  void Initialize() override {
    CommandBase::m_pClimber->ClimberRetract();
  }
};

#endif //SRC_CLIMBERRETRACTCOMMAND