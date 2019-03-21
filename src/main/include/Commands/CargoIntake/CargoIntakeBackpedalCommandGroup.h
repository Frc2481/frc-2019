/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEBACKPEDALCOMMANDGROUP
#define SRC_CARGOINTAKEBACKPEDALCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntake/CargoIntakeBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"

class CargoIntakeBackpedalCommandGroup : public frc::CommandGroup {
 public:
  CargoIntakeBackpedalCommandGroup() : CommandGroup("CargoIntakeBackpedalCommandGroup") {
    AddSequential(new CargoIntakeOutCommand("CargoIntakeOutCommand"));
    AddSequential(new CargoIntakeBallCommand(-1));
  }
};

#endif //SRC_CARGOINTAKEBACKPEDALCOMMANDGROUP