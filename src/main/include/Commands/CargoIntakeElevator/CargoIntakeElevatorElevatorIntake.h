#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_INTAKE_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_INTAKE_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorIntake : public CommandBase {
public:
	CargoIntakeElevatorElevatorIntake()
		: CommandBase("CargoIntakeElevatorElevatorIntake") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorIntake() {
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
                m_pCargoIntakeElevator->MoveElevatorToPosition(INTAKE_CARGO);
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_INTAKE_H