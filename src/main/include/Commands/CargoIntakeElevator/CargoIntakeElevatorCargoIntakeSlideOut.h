#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_OUT_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_OUT_H

#include "CommandBase.h"

class CargoIntakeElevatorCargoIntakeSlideOut : public CommandBase {
public:
	CargoIntakeElevatorCargoIntakeSlideOut()
		: CommandBase("CargoIntakeElevatorCargoIntakeSlideOut") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorCargoIntakeSlideOut() {
	}

	void Initialize() {
	}

	void Execute() {
        if(m_pCargoIntakeElevator->IsElevatorInProtectedZone()) {
            m_pCargoIntakeElevator->MoveElevatorToPosition(MID_HATCH);
        }
        else {
            m_pCargoIntakeElevator->MoveCargoIntakeSlideToPosition(OUT);
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_CARGO_INTAKE_SLIDE_OUT_H