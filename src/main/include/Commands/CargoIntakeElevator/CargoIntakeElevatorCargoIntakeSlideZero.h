#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_ZERO_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_ZERO_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntakeSlideZero : public CommandBase {
public:
	CargoIntakeElevatorCargoIntakeSlideZero()
		: CommandBase("CargoIntakeElevatorCargoIntakeSlideZero") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntakeSlideZero() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->ZeroCargoIntakeSlide();
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_ZERO_H