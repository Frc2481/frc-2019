#include "CommandBase.h"

std::unique_ptr<OI> CommandBase::m_pOI;
std::unique_ptr<SwerveDrivetrain> CommandBase::m_pSwerveDrivetrain;
std::unique_ptr<LineFinder> CommandBase::m_pLineFinder;
std::unique_ptr<HatchSlide> CommandBase::m_pHatchSlide;
std::unique_ptr<Elevator> CommandBase::m_pElevator;

CommandBase::CommandBase(const std::string &name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

void CommandBase::Init() {
	m_pSwerveDrivetrain.reset(new SwerveDrivetrain());
	m_pLineFinder.reset(new LineFinder());
	m_pHatchSlide.reset(new HatchSlide());
	m_pElevator.reset(new Elevator());
	m_pOI.reset(new OI()); // OI must be last subsystem to reset

	Wait(1); // avoid race condition after constructing objects
}

void CommandBase::Periodic() {
	m_pSwerveDrivetrain->Periodic();
	m_pLineFinder->Periodic();
	m_pHatchSlide->Periodic();
	m_pElevator->Periodic();
}
