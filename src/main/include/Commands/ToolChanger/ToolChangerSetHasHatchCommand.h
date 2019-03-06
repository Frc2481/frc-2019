/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSETHASHATCHCOMMAND
#define SRC_TOOLCHANGERSETHASHATCHCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerSetHasHatchCommand: public frc::InstantCommand {
 private:
  bool m_hasHatch;
 public:
  ToolChangerSetHasHatchCommand(bool hasHatch) : InstantCommand("ToolChangerSetHasHatchCommand") {
    m_hasHatch = hasHatch;
  }
  void Initialize() override {
    CommandBase::m_pToolChanger->SetHasHatch(m_hasHatch);
  }
};
#endif //SRC_TOOLCHANGERSETHASHATCHCOMMAND