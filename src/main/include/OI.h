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
    frc::JoystickButton *m_pDriveShiftButton;

    frc::Button* m_centerHatch;
};

#endif // OI_H
