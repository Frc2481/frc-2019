/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_HATCHSLIDESETOOPENLOOPCOMMAND
#define SRC_HATCHSLIDESETOOPENLOOPCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"
#include "Subsystems/HatchSlide.h"

class HatchSlideSetOpenLoopCommand : public frc::Command {
 public:
  HatchSlideSetOpenLoopCommand() : Command("HatchSlideSetOpenLoopCommand"){
    Requires(CommandBase::m_pHatchSlide.get());
  }
  void Initialize() override {

  }
  void Execute() override {
		double percentVelY = -CommandBase::m_pOI->GetOperatorStick()->GetRawAxis(XBOX_LEFT_Y_AXIS);

    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(percentVelY);
  }
  bool IsFinished() override {
    return false;
  }
  void End() override {
    CommandBase::m_pHatchSlide->SetOpenLoopSpeed(0);   
  }
  void Interrupted() override {
    End();
  }
};

#endif //SRC_HATCHSLIDESETOOPENLOOPCOMMAND