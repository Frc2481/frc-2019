#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_STOP_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_STOP_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntakeStop : public CommandBase {
public:
	CargoIntakeElevatorCargoIntakeStop()
		: CommandBase("CargoIntakeElevatorCargoIntakeStop") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntakeStop() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->StopCargoIntake();
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_STOP_H