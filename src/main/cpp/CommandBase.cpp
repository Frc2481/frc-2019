#include "CommandBase.h"

std::unique_ptr<OI> CommandBase::m_pOI;
std::unique_ptr<SwerveDrivetrain> CommandBase::m_pSwerveDrivetrain;
std::unique_ptr<VisionLineFinder> CommandBase::m_pVisionLineFinder;

CommandBase::CommandBase(const std::string &name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

void CommandBase::Init() {
	m_pSwerveDrivetrain.reset(new SwerveDrivetrain());
	m_pVisionLineFinder.reset(new VisionLineFinder());
	m_pOI.reset(new OI()); // OI must be last subsystem to reset

	Wait(1); // avoid race condition after constructing objects

	CommandBase::m_pSwerveDrivetrain->zeroDriveEncoders();
	CommandBase::m_pSwerveDrivetrain->zeroGyroYaw();
}

void CommandBase::Periodic() {
	m_pSwerveDrivetrain->Periodic();
	m_pVisionLineFinder->Periodic();
}
