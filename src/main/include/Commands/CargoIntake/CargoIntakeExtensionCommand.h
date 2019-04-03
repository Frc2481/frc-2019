/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CARGOINTAKEEXTENSIONCOMMAND
#define SRC_CARGOINTAKEEXTENSIONCOMMAND

#include <frc/commands/InstantCommand.h>
#include "CommandBase.h"

class CargoIntakeExtendCommand : public frc::InstantCommand {
 public:
  CargoIntakeExtendCommand() : InstantCommand("CargoIntakeExtendCommand") {}
  void Initialize() override {
    CommandBase::m_pCargoIntake->SetSpeed(1);
    CommandBase::m_pCargoIntake->SetPosition(14275); //TODO
  }
  bool IsFinished() override {
    return CommandBase::m_pCargoIntake->IsOnTarget();
  }
  void End() override {
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
  }
};

class CargoIntakeRetractCommand : public frc::InstantCommand {
 public:
  CargoIntakeRetractCommand() : InstantCommand("CargoIntakeRetractCommand") {}
  void Initialize() override {
    CommandBase::m_pCargoIntake->SetSpeed(0.7);
    CommandBase::m_pCargoIntake->SetPosition(0); //TODO
  }
  bool IsFinished() override {
    return CommandBase::m_pCargoIntake->IsOnTarget();
  }
  void End() override {
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
  }
};

#endif //SRC_CARGOINTAKEEXTENSIONCOMMAND