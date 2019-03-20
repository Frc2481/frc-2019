#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_IN_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_IN_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntakeSlideIn : public CommandBase {
public:
	CargoIntakeElevatorCargoIntakeSlideIn()
		: CommandBase("CargoIntakeElevatorCargoIntakeSlideIn") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntakeSlideIn() {
	}

	void Initialize() {
	}

	void Execute() {
        if(m_pCargoIntakeElevator->IsElevatorInProtectedZone()) {
            m_pCargoIntakeElevator->MoveElevatorToPosition(MID_HATCH);
        }
        else {
            m_pCargoIntakeElevator->MoveCargoIntakeSlideToPosition(IN);
        }
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return m_pCargoIntakeElevator->IsCargoIntakeSlideOnTarget();
	}

	void End() {
        m_pCargoIntakeElevator->StopCargoIntakeSlide();
        m_pCargoIntakeElevator->StopElevator();
	}

private:

};

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_IN_H