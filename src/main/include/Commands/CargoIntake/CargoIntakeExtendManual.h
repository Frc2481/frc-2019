/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef COMMAND_CARGO_INTAKE_EXTEND_MANUAL
#define COMMAND_CARGO_INTAKE_EXTEND_MANUAL

#include <frc/commands/Command.h>
#include "Subsystems/CargoIntake.h"
#include "CommandBase.h"

class CargoIntakeExtendManual : public frc::Command {
 private:

 public:
  CargoIntakeExtendManual() : Command("CargoIntakeExtendManual") {
    Requires(CommandBase::m_pCargoIntake.get());
  }

  void Initialize() override {
  }

  void Execute() override {
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0.5);
  }

  bool IsFinished() override {
    return false;
  }
  void End() override {
    CommandBase::m_pCargoIntake->SetOpenLoopSpeed(0);
  }

  void Interrupted() override {
    End();
  }
};

#endif //COMMAND_CARGO_INTAKE_EXTEND_MANUAL
