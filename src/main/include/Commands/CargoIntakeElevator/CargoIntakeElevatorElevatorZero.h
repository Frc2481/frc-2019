#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_ZERO_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_ZERO_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorZero : public CommandBase {
public:
	CargoIntakeElevatorElevatorZero()
		: CommandBase("CargoIntakeElevatorElevatorZero") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorZero() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->ZeroElevator();
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_ZERO_H