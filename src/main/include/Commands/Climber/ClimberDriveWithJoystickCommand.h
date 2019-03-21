/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERDRIVEWITHJOYSTICKCOMMAND
#define SRC_CLIMBERDRIVEWITHJOYSTICKCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ClimberDriveWithJoystickCommand : public frc::Command {
 public:
  ClimberDriveWithJoystickCommand() : Command("ClimberDriveWithJoystickCommand"){
    Requires(CommandBase::m_pClimber.get());
  }
  void Initialize() override {
  }
  void Execute() override {
    // if(CommandBase::m_pClimber->IsClimberEnabled()){
          // get joystick input
      double percentVelY = -CommandBase::m_pOI->GetOperatorStick()->GetRawAxis(XBOX_LEFT_Y_AXIS);

      // // update climb
      CommandBase::m_pClimber->SetOpenLoopSpeed(percentVelY);
    // }
  }
  bool IsFinished() override{
    return false;
  }
  void End() override{
    CommandBase::m_pClimber->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_CLIMBERDRIVEWITHJOYSTICKCOMMAND