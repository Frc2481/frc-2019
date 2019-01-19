#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <frc/WPILib.h>
#include "OI.h"
#include "Subsystems/SwerveDrivetrain.h"
#include "Subsystems/LineFinder.h"
#include "Subsystems/HatchSlide.h"

class CommandBase: public Command
{
public:
    CommandBase(const std::string &name);
    CommandBase();

    static void Init();
    static void Periodic();
	
    static std::unique_ptr<OI> m_pOI;
    static std::unique_ptr<SwerveDrivetrain> m_pSwerveDrivetrain;
    static std::unique_ptr<LineFinder> m_pLineFinder;
    static std::unique_ptr<HatchSlide> m_pHatchSlide;
};

#endif // COMMAND_BASE_H
