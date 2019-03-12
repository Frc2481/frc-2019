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
    
//driver
    AnalogJoystickButton* m_acquireCargo;
    AnalogJoystickButton* m_acquireHatch;
    frc::Button* m_zeroGyro;
    frc::Button* m_elevatorStow;
    frc::Button* m_climbRetract;
    frc::Button* m_climbLevel2;
    frc::Button* m_climbLevel3;
    frc::Button* m_climberLittleFeet;
    frc::Button* m_climberBigFoot;
    frc::JoystickButton *m_pSetFieldFrameButton;

//operator
    frc::Button* m_scoreHigh;
    frc::Button* m_scoreMid;
    frc::Button* m_scoreLow;
    AnalogJoystickButton* m_elevatorManual;
    AnalogJoystickButton* m_slideOpenLoop;
    frc::Button* m_cargoShip;
    frc::Button* m_toggleSlide;
    frc::Button* m_climberFeetOp;
    frc::Button* m_prepAcquireHatch;
    frc::Button* m_climberToggleManual;
    frc::Button* m_elevatorToggleManual;
    AnalogJoystickButton* m_scoreGamePiece;

};

#endif // OI_H
