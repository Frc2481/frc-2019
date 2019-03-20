#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_STOP_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_STOP_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntakeSlideStop : public CommandBase {
public:
	CargoIntakeElevatorCargoIntakeSlideStop()
		: CommandBase("CargoIntakeElevatorCargoIntakeSlideStop") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntakeSlideStop() {
	}

	void Initialize() {
		m_pCargoIntakeElevator->StopCargoIntakeSlide();
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_STOP_H