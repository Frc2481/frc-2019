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
#include "Components/UserButton.h"

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
    frc::Button* m_acquireHatch;
    frc::Button* m_elevatorStow;
    frc::Button* m_scoreHigh;
    frc::Button* m_scoreMid;
    frc::Button* m_scoreLow;
    AnalogJoystickButton* m_scoreGamePiece;  
    frc::JoystickButton *m_pSetFieldFrameButton;

//operator
    frc::Button* m_shiftWeights;
    frc::Button* m_zeroGyro;
    frc::Button* m_prepAcquireHatch;
    // frc::Button* m_climberLittleFeet;
    // frc::Button* m_climberBigFoot;
    frc::Button* m_climbL1ToL2;
    frc::Button* m_climbL2ToL3;
    frc::Button* m_climbL1ToL3;
    frc::Button* m_climberGuides;
    AnalogJoystickButton* m_elevatorManual;
    frc::Button* m_toggleSlide;
    AnalogJoystickButton* m_slideOpenLoop;
    frc::Button* m_climberUp;
    frc::Button* m_climberDown;
    frc::Button* m_hatchExtend;
    // frc::Button* m_cargoShip;
    // frc::Button* m_climberFeetOp;

// RoboRio
    UserButton* m_userButton;
};

#endif // OI_H
