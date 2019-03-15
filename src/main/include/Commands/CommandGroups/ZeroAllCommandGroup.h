/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ZEROALLCOMMANDGROUP
#define SRC_ZEROALLCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntake/CargoIntakeZeroCommand.h"
#include "Commands/Elevator/ElevatorZeroCommand.h"
#include "Commands/HatchSlide/HatchSlideZeroCommand.h"
// #include "Commands/Climber/ClimberZeroCommand.h"

class ZeroAllCommandGroup : public frc::CommandGroup {
 public:
  ZeroAllCommandGroup() : CommandGroup("ZeroAllCommandGroup"){
    SetRunWhenDisabled(true);
    AddSequential(new CargoIntakeZeroCommand());
    AddSequential(new ElevatorZeroCommand());
    AddSequential(new HatchSlideZeroCommand());
    // AddParallel(new ClimberZeroCommand());
  }
};

#endif //SRC_ZEROALLCOMMANDGROUP