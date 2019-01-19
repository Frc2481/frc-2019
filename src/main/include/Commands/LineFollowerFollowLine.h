#ifndef COMMANDS_LINE_FOLLOWER_FOLLOW_LINE_H
#define COMMANDS_LINE_FOLLOWER_FOLLOW_LINE_H

#include "CommandBase.h"

class LineFollowerFollowLine : public CommandBase {
public:
	LineFollowerFollowLine()
		: CommandBase("LineFollowerFollowLine") {
		
		Requires(CommandBase::m_pLineFollower.get());
		SetInterruptible(false);
  }

	~LineFollowerFollowLine() {
	}

	void Initialize() {
	}

	void Execute() {
		m_pLineFollower->updateMotorController();
	}

	void Interrupted() {
		End();
	}

	bool IsFinished() {
		return false;
	}

	void End() {
	}

private:

};

#endif // COMMANDS_LINE_FOLLOWER_FOLLOW_LINE_H
