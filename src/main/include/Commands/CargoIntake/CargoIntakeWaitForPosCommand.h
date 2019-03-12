/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEWAITFORPOSCOMMAND
#define SRC_CARGOINTAKEWAITFORPOSCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"

class CargoIntakeWaitForPosCommand : public frc::Command {
  private:
  bool m_isGoingForward = false;
  double m_setPoint;
 public:
  CargoIntakeWaitForPosCommand(double setPoint) : Command("CargoIntakeWaitForPosCommand") {  
    m_setPoint = setPoint;
    m_isGoingForward = CommandBase::m_pCargoIntake->GetVelocity() > 0;
  }
  bool IsFinished() override {
    if((m_isGoingForward) && (m_setPoint - CommandBase::m_pCargoIntake->GetPosition() < 1)){
      return true;
    }
    else if((!m_isGoingForward) && (CommandBase::m_pCargoIntake->GetPosition() - m_setPoint < 1)){
      return true;
    }
    else{
      return false;
    }
  }
};

#endif // SRC_CARGOINTAKEWAITFORPOSCOMMAND