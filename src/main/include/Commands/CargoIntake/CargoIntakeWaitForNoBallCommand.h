/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEWAITFORNOBALLCOMMAND
#define SRC_CARGOINTAKEWAITFORNOBALLCOMMAND

#include "CommandBase.h"
#include <frc/commands/Command.h>

class CargoIntakeWaitForNoBallCommand : public frc::Command {
 public:
  CargoIntakeWaitForNoBallCommand() : Command("CargoIntakeWaitForNoBallCommand") {

  }
  bool IsFinished() override {
    return !CommandBase::m_pCargoIntake->IsBallIntaken();
  }
};

#endif //SRC_CARGOINTAKEWAITFORNOBALLCOMMAND