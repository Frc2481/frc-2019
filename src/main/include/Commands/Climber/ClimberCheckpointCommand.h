/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERCHECKPOINTCOMMAND
#define SRC_CLIMBERCHECKPOINTCOMMAND

#include <frc/commands/Command.h>
#include <frc/WPILib.h>

class ClimberCheckpointCommand : public frc::Command {
 private:
  frc::Button* m_primary;
  frc::Button* m_secondary;
 public:
  ClimberCheckpointCommand(frc::Button* primary, frc::Button* secondary) : Command("ClimberCheckpointCommand") {
    m_primary = primary;
    m_secondary = secondary;
  }
  bool IsFinished() override {
    return m_primary->Get() && m_secondary->Get();
  }
};

#endif //SRC_CLIMBERCHECKPOINTCOMMAND