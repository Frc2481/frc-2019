// #ifndef COMMANDS_TANK_DRIVETRAIN_SHIFT_GEAR_H
// #define COMMANDS_TANK_DRIVETRAIN_SHIFT_GEAR_H

// #include "CommandBase.h"

// class TankDrivetrainShiftGear : public CommandBase {
// public:
// 	TankDrivetrainShiftGear(bool isHighGear)
// 		: CommandBase("TankDrivetrainShiftGear"),
//         m_isHighGear(isHighGear) {

// 		Requires(CommandBase::m_pTankDrivetrain.get());
// 		SetInterruptible(false);
// 	}

// 	~TankDrivetrainShiftGear() {
// 	}

// 	void Initialize() {
// 		m_pTankDrivetrain->setShiftState(m_isHighGear);
// 	}

// 	void Execute() {
// 	}

// 	void Interrupted() {
// 		End();
// 	}

// 	bool IsFinished() {
// 		return true;
// 	}

// 	void End() {
// 	}

// private:
//     bool m_isHighGear;
// };

// #endif // COMMANDS_TANK_DRIVETRAIN_SHIFT_HIGH_GEAR_H
