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

class ZeroAllCommandGroup : public frc::CommandGroup {
 public:
  ZeroAllCommandGroup() : CommandGroup("ZeroAllCommandGroup"){
    AddParallel(new CargoIntakeZeroCommand());
    AddParallel(new ElevatorZeroCommand());
    AddParallel(new HatchSlideZeroCommand());
  }

};

#endif //SRC_ZEROALLCOMMANDGROUP