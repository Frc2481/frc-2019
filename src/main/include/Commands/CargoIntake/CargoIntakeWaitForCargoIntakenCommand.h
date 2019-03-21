/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEWAITFORCARGOINTAKENCOMMAND
#define SRC_CARGOINTAKEWAITFORCARGOINTAKENCOMMAND
#include <frc/commands/Command.h>
#include "CommandBase.h"

class CargoIntakeWaitForCargoIntakenCommand : public frc::Command {
 public:
  CargoIntakeWaitForCargoIntakenCommand() : Command("CargoIntakeWaitForCargoIntakenCommand") {

  }
  bool IsFinished() override {
    return CommandBase::m_pCargoIntake->IsBallIntaken();
  }
};

#endif //SRC_CARGOINTAKEWAITFORCARGOINTAKENCOMMAND