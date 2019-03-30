/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERFREECARGOCOMMAND
#define SRC_TOOLCHANGERFREECARGOCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class ToolChangerFreeCargoCommand : public frc::InstantCommand {
 public:
  ToolChangerFreeCargoCommand() : InstantCommand("ToolChangerFreeCargoCommand"){}
  void Initialize() override{
    CommandBase::m_pToolChanger->FreeCargo();
  }
};

#endif //SRC_TOOLCHANGERFREECARGOCOMMAND