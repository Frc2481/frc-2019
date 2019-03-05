/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERSETOPENLOOPCOMMAND
#define SRC_CLIMBERSETOPENLOOPCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ClimberSetOpenLoopCommand : public frc::InstantCommand {
  private:
  double m_speed;
 public:
  ClimberSetOpenLoopCommand(double speed) : InstantCommand("ClimberSetOpenLoopCommand"){
      m_speed = speed;
      Requires(CommandBase::m_pClimber.get());
  }
  void Initialize() override{
    CommandBase::m_pClimber->SetOpenLoopSpeed(m_speed);
  }
};

#endif //SRC_CLIMBERSETOPENLOOPCOMMAND