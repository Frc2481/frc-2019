#include "CommandBase.h"

std::unique_ptr<OI> CommandBase::m_pOI;
std::unique_ptr<SwerveDrivetrain> CommandBase::m_pSwerveDrivetrain;
std::unique_ptr<HatchSlide> CommandBase::m_pHatchSlide;
std::unique_ptr<Elevator> CommandBase::m_pElevator;
std::unique_ptr<CargoIntake> CommandBase::m_pCargoIntake;	
std::unique_ptr<ToolChanger> CommandBase::m_pToolChanger;
std::unique_ptr<Climber> CommandBase::m_pClimber;

CommandBase::CommandBase(const std::string &name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

void CommandBase::Init() {
	m_pSwerveDrivetrain.reset(new SwerveDrivetrain());
	m_pHatchSlide.reset(new HatchSlide());
	m_pElevator.reset(new Elevator());
	m_pCargoIntake.reset(new CargoIntake());
	m_pToolChanger.reset(new ToolChanger());
	m_pClimber.reset(new Climber());
	m_pOI.reset(new OI()); // OI must be last subsystem to reset

	Wait(1); // avoid race condition after constructing objects
}

void CommandBase::Periodic() {
	m_pSwerveDrivetrain->Periodic();
	m_pHatchSlide->Periodic();
	m_pElevator->Periodic();
	m_pCargoIntake->Periodic();
	m_pToolChanger->Periodic();
	m_pClimber->Periodic();
}
