#ifndef COMMANDS_INTAKE_HATCH_COMMAND_GROUP_H
#define COMMANDS_INTAKE_HATCH_COMMAND_GROUP_H

#include <frc/WPILib.h>
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorElevatorIntake.h"
#include "Commands/CargoIntakeElevator/CargoIntakeElevatorElevatorLow.h"

class IntakeHatchCommandGroup : public CommandGroup {
public:
	IntakeCargoCommandGroup()
		: CommandGroup("IntakeCargoCommandGroup") {
		
        AddSequential(new CargoIntakeElevatorElevatorIntake());
        AddSequential(new CargoIntakeElevatorElevatorLow());
	}

private:

};

#endif // COMMANDS_INTAKE_HATCH_COMMAND_GROUP_H