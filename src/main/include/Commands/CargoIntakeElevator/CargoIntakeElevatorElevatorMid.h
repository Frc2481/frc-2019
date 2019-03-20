#ifndef COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_MID_H
#define COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_MID_H

#include "CommandBase.h"

class CargoIntakeElevatorElevatorMid : public CommandBase {
public:
	CargoIntakeElevatorElevatorMid()
		: CommandBase("CargoIntakeElevatorElevatorMid") {
		
		Requires(CommandBase::m_pCargoIntakeElevator.get());
		SetInterruptible(true);
	}

	~CargoIntakeElevatorElevatorMid() {
	}

	void Initialize() {
	}

	void Execute() {
        if(true) { // TODO: get hatch/cargo status
            m_pCargoIntakeElevator->MoveElevatorToPosition(MID_HATCH);
        }
        else {
            m_pCargoIntakeElevator->MoveElevatorToPosition(MID_CARGO);
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

#endif // COMMANDS_CARGO_INTAKE_ELEVATOR_ELEVATOR_MID_H