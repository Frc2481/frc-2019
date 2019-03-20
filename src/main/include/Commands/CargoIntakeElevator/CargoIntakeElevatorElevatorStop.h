#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_STOP_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_STOP_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorStop : public CommandBase {
public:
	CargoIntakeElevatorElevatorStop()
		: CommandBase("CargoIntakeElevatorElevatorStop") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorStop() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->StopElevator();
	}

	void Execute() {
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return true;
	}

	void End() {
	}

private:

};

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_STOP_H