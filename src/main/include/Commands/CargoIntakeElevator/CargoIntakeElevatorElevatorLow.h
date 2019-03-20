#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_LOW_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_LOW_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorLow : public CommandBase {
public:
	CargoIntakeElevatorElevatorLow()
		: CommandBase("CargoIntakeElevatorElevatorLow") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorLow() {
	}

	void Initialize() {
	}

	void Execute() {
        if(m_pCargoIntakeElevator->IsCargoIntakeSlideInProtectedZone()) {
            m_pCargoIntakeElevator->MoveCargoIntakeSlideToPosition(IN);
        }
        else {
            if(true) { // TODO: get hatch/cargo status
                m_pCargoIntakeElevator->MoveElevatorToPosition(LOW_HATCH);
            }
            else {
                m_pCargoIntakeElevator->MoveElevatorToPosition(LOW_CARGO);
            }
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_LOW_H