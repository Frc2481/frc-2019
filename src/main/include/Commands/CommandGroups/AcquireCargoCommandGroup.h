/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ACQUIRECARGOCOMMANDGROUP
#define SRC_ACQUIRECARGOCOMMANDGROUP

#include <frc/commands/CommandGroup.h>
#include "Commands/CargoIntake/CargoIntakeBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeStopCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHoldCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerFreeHatchCommand.h"
#include "Commands/ToolChanger/ToolChangerSetHasCargoCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchRetractCommand.h"
#include "Commands/ToolChanger/ToolChangerHatchExtendCommand.h"
#include "Commands/Elevator/ElevatorBaseCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForBallCommand.h"
#include "Commands/CargoIntake/CargoIntakeWaitForCargoIntakenCommand.h"
#include "Commands/HatchSlide/HatchSlideEnableCommand.h"
#include "Commands/HatchSlide/HatchSlideToCenterCommand.h"
#include "Commands/SetLEDsCommand.h"
#include "Commands/Elevator/ElevatorWaitForPositionCommand.h"
#include "Commands/CargoIntake/CargoIntakeExtensionCommand.h"

class AcquireCargoCommandGroup : public frc::CommandGroup {
 public:
  AcquireCargoCommandGroup() : CommandGroup("AcquireCargoCommandGroup") {
    Requires(CommandBase::m_pElevator.get());
    Requires(CommandBase::m_pCargoIntake.get());
    Requires(CommandBase::m_pHatchSlide.get());

    AddParallel(new InstantCommand([]() {CommandBase::m_pCargoIntake->SetIsIntaking(true);}));
    //set up for command - hatch slide center
    AddParallel(new HatchSlideDisableCommand());
    AddParallel(new HatchSlideToCenterCommand());
    AddParallel(new ToolChangerFreeHatchCommand());
    AddParallel(new ToolChangerHatchRetractCommand());
    AddSequential(new ElevatorStowCommand("ElevatorStowCommand"));
    // AddSequential(new WaitCommand(0.35));

    //intake out
    AddSequential(new CargoIntakeExtendCommand());
    // AddSequential(new WaitCommand(0.75)); //TODO
    AddSequential(new ToolChangerFreeCargoCommand());

    //intake ball
    AddParallel(new CargoIntakeBallCommand(0.8));
    AddSequential(new CargoIntakeWaitForCargoIntakenCommand());
    AddSequential(new WaitCommand(0.5));
    // AddParallel(new CargoIntakeBallCommand(0.3));
    AddParallel(new CargoIntakeRetractCommand());
    AddSequential(new CargoIntakeWaitForBallCommand(), 1.0);
    AddParallel(new CargoIntakeStopCommand());
    AddParallel(new ToolChangerHoldCargoCommand());
    AddParallel(new ToolChangerSetHasCargoCommand(true));
    AddParallel(new InstantCommand([]() {CommandBase::m_pCargoIntake->SetIsIntaking(false);}));
    AddSequential(new WaitCommand(0.1));

    //leds & elevator back down
    AddParallel(new SetLEDsCommand(5));

    // state at end:
    // Elevator: Low
    // Cargo Intake: In
    // Cargo: Held
    // Hatch: Held
    // HatchExt: Retracted
  }

  void Interrupted() {
    CommandBase::m_pCargoIntake->SetIsIntaking(false);;
  }
};

class ManualFinishAquireCargoCommandGroup : public CommandGroup {
public:
  ManualFinishAquireCargoCommandGroup() : CommandGroup("ManualFinishAquireCargoCommandGroup") {
    AddParallel(new CargoIntakeRetractCommand());
    AddSequential(new CargoIntakeWaitForBallCommand(), 1.0);
    AddParallel(new CargoIntakeStopCommand());
    AddParallel(new ToolChangerHoldCargoCommand());
    AddParallel(new ToolChangerSetHasCargoCommand(true));
    AddParallel(new InstantCommand([]() {CommandBase::m_pCargoIntake->SetIsIntaking(false);}));
  }
};

#endif //SRC_ACQUIRECARGOCOMMANDGROUP