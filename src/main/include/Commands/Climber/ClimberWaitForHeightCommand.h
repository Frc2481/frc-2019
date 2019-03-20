/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBERWAITFORHEIGHTCOMMAND
#define SRC_CLIMBERWAITFORHEIGHTCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class ClimberWaitForHeightCommand : public frc::Command {
 private:
  bool m_isGoingUp;
  int m_pos;
 public:
  ClimberWaitForHeightCommand(int pos) : Command("ClimberWaitForHeightCommand"){
    m_isGoingUp = false;
    m_pos = pos;
  }
  void Initialize() override{
    if(CommandBase::m_pClimber->GetPos() < m_pos){
      m_isGoingUp = true;
    }
  }
  void Execute() override{}
  bool IsFinished() override{
    if(CommandBase::m_pClimber->GetPos() > m_pos && m_isGoingUp){
        return true;
    }
    else if(CommandBase::m_pClimber->GetPos() < m_pos && !m_isGoingUp){
      return true;
    }
    else{
      return false;
    }
  }
  void End() override{}
  void Interrupted() override{}
};

#endif //SRC_CLIMBERWAITFORHEIGHTCOMMAND