#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_HIGH_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_HIGH_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorHigh : public CommandBase {
public:
	CargoIntakeElevatorElevatorHigh()
		: CommandBase("CargoIntakeElevatorElevatorHigh") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorHigh() {
	}

	void Initialize() {
	}

	void Execute() {
        if(true) { // TODO: get hatch/cargo status
            m_pCargoIntakeElevator->MoveElevatorToPosition(HIGH_HATCH);
        }
        else {
            m_pCargoIntakeElevator->MoveElevatorToPosition(HIGH_CARGO);
        }
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return m_pCargoIntakeElevator->IsElevatorOnTarget();
	}

	void End() {
        m_pCargoIntakeElevator->StopCargoIntakeSlide();
        m_pCargoIntakeElevator->StopElevator();
	}

private:

};

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_HIGH_H