/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_TOOLCHANGER
#define SRC_TOOLCHANGER

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include "RobotMap.h"
#include <frc/DigitalInput.h>

class ToolChanger : public frc::Subsystem {
 private:
  frc::DoubleSolenoid* m_hatchTool;
  frc::DoubleSolenoid* m_cargoTool;
  frc::DoubleSolenoid* m_hatchExtender;
  frc::DigitalInput* m_capacitiveSensor;
  bool m_isHatchToolHeld;
  bool m_isCargoToolHeld;
  bool m_hasCargo;
  bool m_hasHatch;
  bool m_isHatchExtended;

 public:
  ToolChanger();
  void Periodic();
  void InitDefaultCommand() override;
  void HoldHatch();
  void FreeHatch();
  void HoldCargo();
  void FreeCargo();
  void ExtendHatch();
  void RetractHatch();
  bool IsHatchToolHeld();
  bool IsCargoToolHeld();
  bool IsHatchExtended();
  bool HasCargo();
  bool HasHatch();
  void SetHasCargo(bool hasCargo);
  void SetHasHatch(bool hasHatch);
};

#endif //SRC_TOOLCHANGER