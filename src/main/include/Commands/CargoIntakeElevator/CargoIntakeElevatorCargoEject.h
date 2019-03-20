#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_EJECT_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_EJECT_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoEject : public CommandBase {
public:
	CargoIntakeElevatorCargoEject()
		: CommandBase("CargoIntakeElevatorCargoEject") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoEject() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->SetCargoIntakePercent(-1);
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_EJECT_H