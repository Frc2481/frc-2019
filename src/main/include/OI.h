#ifndef OI_H
#define OI_H

#include "Components/XboxController2481.h"
#include "Components/Joystick2481.h"
#include "Components/AnalogJoystickButton.h"
#include "Components/POVJoystickButton.h"
#include "frc/buttons/JoystickButton.h"
#include "frc/WPILib.h"
#include "frc/XboxController.h"
#include "frc/buttons/trigger.h"

class OI {
public:
    OI();
    ~OI();

    Joystick2481* GetDriverStick();
    Joystick2481* GetOperatorStick();

    Joystick2481 *m_pDriverStick;
    Joystick2481 *m_pOperatorStick;

    frc::JoystickButton *m_pSetFieldFrameButton;

    frc::Button* m_centerHatch;

//driver
    frc::Button* m_intakeBall;
    frc::Button* m_acquireCargo;
    frc::Button* m_acquireHatch;
    frc::Button* m_zeroGyro;
    frc::Button* m_elevatorStow;
    frc::Button* m_fieldCentric;

//operator
    frc::Button* m_scoreHigh;
    frc::Button* m_scoreMid;
    frc::Button* m_scoreLow;
    AnalogJoystickButton* m_elevatorRaise;
    AnalogJoystickButton* m_elevatorLower;
    frc::Button* m_cargoShip;
};

#endif // OI_H
