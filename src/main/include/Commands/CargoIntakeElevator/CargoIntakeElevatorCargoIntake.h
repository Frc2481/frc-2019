#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntake : public CommandBase {
public:
	CargoIntakeElevatorCargoIntake()
		: CommandBase("CargoIntakeElevatorCargoIntake") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntake() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->SetCargoIntakePercent(1);
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_H