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
#include "Components/ComboJoystickButton.h"

class OI {
public:
    OI();
    ~OI();

    Joystick2481* GetDriverStick();
    Joystick2481* GetOperatorStick();

    Joystick2481 *m_pDriverStick;
    Joystick2481 *m_pOperatorStick;
    
//driver
	frc::Button* m_aDriverButton;
	frc::Button* m_bDriverButton;
	frc::Button* m_yDriverButton;
    frc::Button* m_xDriverButton;
    frc::Button* m_backButton;

    AnalogJoystickButton* m_acquireCargo;
    frc::Button* m_acquireHatch;
    frc::Button* m_elevatorStow;
    frc::Button* m_climbCheckpoint;
    frc::Button* m_climbL1ToL2;
    frc::Button* m_climbL2ToL3;
    frc::Button* m_climbL1ToL3;
    frc::JoystickButton *m_pSetFieldFrameButton;
    frc::Button* m_zeroGyro;
    AnalogJoystickButton* m_stopAll;

//operator
    frc::Button* m_shiftWeights;
    frc::Button* m_prepAcquireHatch;
    AnalogJoystickButton* m_scoreGamePiece;  

    frc::Button* m_climberGuides;
    AnalogJoystickButton* m_elevatorManual;
    frc::Button* m_enableSlide;
    AnalogJoystickButton* m_slideOpenLoop;
    frc::Button* m_climberUp;
    frc::Button* m_climberDown;
    AnalogJoystickButton* m_hatchExtend;
    frc::Button* m_backpedal;
    frc::Button* m_intakeOut;

    frc::Button* m_scoreCargoShip;
    frc::Button* m_scoreHigh;
    frc::Button* m_scoreMid;
    frc::Button* m_scoreLow;

// RoboRio
    UserButton* m_userButton;
};

#endif // OI_H
