/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_ELEVATORJOYSTICKCOMMAND
#define SRC_ELEVATORJOYSTICKCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"
#include "RobotParameters.h"

class ElevatorJoystickCommand : public frc::Command {
 public:
  ElevatorJoystickCommand() : Command("ElevatorJoystickCommand") {
      Requires(CommandBase::m_pElevator.get());
  }
  void Initialize() override {
  }
  void Execute() override {
    if(CommandBase::m_pElevator->IsElevatorManualEnabled()){
      double percentVelY = -CommandBase::m_pOI->GetOperatorStick()->GetRawAxis(XBOX_RIGHT_Y_AXIS);

      // update climb
      CommandBase::m_pElevator->SetOpenLoopSpeed(percentVelY);
    } 
  }
  void End() {
    CommandBase::m_pElevator->SetOpenLoopSpeed(0);
  }
  void Interrupted() override {
    End();
  }
  bool IsFinished() override {
    //if traveling through protected zone while cargoIntake out, don't allow movement
    if(CommandBase::m_pElevator->IsElevatorManualEnabled()){
      if(CommandBase::m_pCargoIntake->IsIntakeOut() &&
          CommandBase::m_pElevator->IsPositionInProtectedZone(CommandBase::m_pElevator->GetElevatorPosition())) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return true;
    }
  }
};

#endif //SRC_ELEVATORJOYSTICKCOMMAND