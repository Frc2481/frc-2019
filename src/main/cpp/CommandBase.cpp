#include "CommandBase.h"

std::unique_ptr<OI> CommandBase::m_pOI;
std::unique_ptr<SwerveDrivetrain> CommandBase::m_pSwerveDrivetrain;
std::unique_ptr<LineFollower> CommandBase::m_pLineFollower;

CommandBase::CommandBase(const std::string &name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

void CommandBase::Init() {
	m_pSwerveDrivetrain.reset(new SwerveDrivetrain());
	m_pLineFollower.reset(new LineFollower());
	m_pOI.reset(new OI()); // OI must be last subsystem to reset

	Wait(1); // avoid race condition after constructing objects
}

void CommandBase::Periodic() {
	m_pSwerveDrivetrain->Periodic();
	m_pLineFollower->Periodic();
}
