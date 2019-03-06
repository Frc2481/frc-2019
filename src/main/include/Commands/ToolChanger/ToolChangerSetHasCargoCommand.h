/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERSETHASCARGOCOMMAND
#define SRC_TOOLCHANGERSETHASCARGOCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerSetHasCargoCommand: public frc::InstantCommand {
 private:
  bool m_hasCargo;
 public:
  ToolChangerSetHasCargoCommand(bool hasCargo) : InstantCommand("ToolChangerSetHasCargoCommand") {
    m_hasCargo = hasCargo;
  }
  void Initialize() override {
    CommandBase::m_pToolChanger->SetHasCargo(m_hasCargo);
  }
};
#endif //SRC_TOOLCHANGERSETHASCARGOCOMMAND