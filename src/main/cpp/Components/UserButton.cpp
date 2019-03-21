/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Components/UserButton.h"

UserButton::UserButton(){
}

UserButton::~UserButton() {
}

bool UserButton::Get() {
  return frc::RobotController::GetUserButton();
}
