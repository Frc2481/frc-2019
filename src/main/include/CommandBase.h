#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <frc/WPILib.h>
#include "OI.h"
#include "Subsystems/SwerveDrivetrain.h"
#include "Subsystems/HatchSlide.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/CargoIntake.h"
#include "Subsystems/ToolChanger.h"
#include "Subsystems/Climber.h"

class CommandBase: public Command
{
public:
    CommandBase(const std::string &name);
    CommandBase();

    static void Init();
	
    static std::unique_ptr<OI> m_pOI;
    static std::unique_ptr<SwerveDrivetrain> m_pSwerveDrivetrain;
    static std::unique_ptr<HatchSlide> m_pHatchSlide;
    static std::unique_ptr<Elevator> m_pElevator;
    static std::unique_ptr<CargoIntake> m_pCargoIntake;
    static std::unique_ptr<ToolChanger> m_pToolChanger;
    static std::unique_ptr<Climber> m_pClimber;
    static std::unique_ptr<PowerDistributionPanel> m_pPDP;
};

#endif // COMMAND_BASE_H
