#ifndef COMMANDS_LINE_FOLLOWER_ZERO_ENCODER_H
#define COMMANDS_LINE_FOLLOWER_ZERO_ENCODER_H

#include "CommandBase.h"

class LineFollowerZeroEncoder : public CommandBase {
public:
	LineFollowerZeroEncoder()
		: CommandBase("LineFollowerZeroEncoder") {
		
		Requires(CommandBase::m_pLineFollower.get());
		SetInterruptible(false);
		SetRunWhenDisabled(true);
  }

	~LineFollowerZeroEncoder() {
	}

	void Initialize() {
		m_pLineFollower->zeroEncoder();
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

#endif // COMMANDS_LINE_FOLLOWER_ZERO_ENCODER_H
