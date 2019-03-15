/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef USER_BUTTON
#define USER_BUTTON

#include <frc/WPILib.h>

class UserButton : public frc::Button {
public:
    UserButton();
    virtual ~UserButton();

    virtual bool Get();
};

#endif // USER_BUTTON
