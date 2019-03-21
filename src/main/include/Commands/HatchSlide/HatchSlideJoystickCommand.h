/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDEDRIVEWITHJOYSTICKCOMMAND
#define SRC_HATCHSLIDEDRIVEWITHJOYSTICKCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class HatchSlideJoystickCommand : public frc::Command {
 public:
  HatchSlideJoystickCommand() : Command("HatchSlideJoystickCommand"){
    Requires(CommandBase::m_pHatchSlide.get());
  }
  void Execute() override{
    // if(CommandBase::m_pHatchSlide->IsHatchSlideEnabled()){
      double percentVelY = -CommandBase::m_pOI->GetOperatorStick()->GetRawAxis(XBOX_RIGHT_X_AXIS);
      CommandBase::m_pHatchSlide->SetOpenLoopSpeed(percentVelY);    
    // }
  }
  bool IsFinished() override{
    return false;
  }
  void End() override{
    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0.0);
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_HATCHSLIDEDRIVEWITHJOYSTICKCOMMAND