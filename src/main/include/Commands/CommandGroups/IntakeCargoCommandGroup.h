#ifndef COMMANDS_INTAKE_CARGO_COMMAND_GROUP_H
#define COMMANDS_INTAKE_CARGO_COMMAND_GROUP_H

#include <frc/WPILib.h>
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorCargoIntakeSlideIn.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorCargoIntakeSlideOut.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorCargoIntakeSlideStop.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorCargoIntake.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorCargoIntakeStop.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorElevatorIntake.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorElevatorLow.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorElevatorMid.h"

class IntakeCargoCommandGroup : public CommandGroup {
public:
	IntakeCargoCommandGroup()
		: CommandGroup("IntakeCargoCommandGroup") {
		
		AddSequential(new CargoIntakeElevatorElevatorMid());
        AddSequential(new CargoIntakeElevatorCargoIntakeSlideOut());
        AddSequential(new CargoIntakeElevatorElevatorIntake());
        AddSequential(new CargoIntakeElevatorCargoIntake());
        AddSequential(new CargoIntakeElevatorCargoIntakeStop());
        AddSequential(new CargoIntakeElevatorElevatorMid());
        AddSequential(new CargoIntakeElevatorCargoIntakeSlideIn());
        AddSequential(new CargoIntakeElevatorElevatorLow());
	}

private:

};

#endif // COMMANDS_INTAKE_CARGO_COMMAND_GROUP_H