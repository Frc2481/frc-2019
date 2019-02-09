/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGERRETRACTCOMMAND
#define SRC_TOOLCHANGERRETRACTCOMMAND

#include <frc/commands/InstantCommand.h>
#include "Subsystems/ToolChanger.h"
#include "Subsystems/Elevator.h"

class ToolChangerRetractCommand : public frc::InstantCommand {
 public:
  ToolChangerRetractCommand() : InstantCommand("ToolChangerRetractCommand") {}
  void Initialize() override {
    if(CommandBase::m_pToolChanger->HasHatch()) {
      //whatever's needed to retract hatch
    }
    else {
      //whatever's needed to retract cargo
    }
  }
};

#endif //SRC_TOOLCHANGERRETRACTCOMMAND