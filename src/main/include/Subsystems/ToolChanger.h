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
  frc::Solenoid* m_hatchTool;
  frc::Solenoid* m_cargoTool;
  frc::DigitalInput* m_limitSwitch;
  bool m_isHatchToolOpen;
  bool m_isCargoToolOpen;
  bool m_hasCargo;
  bool m_hasHatch;

 public:
  ToolChanger();
  void InitDefaultCommand() override;
  void OpenHatch();
  void CloseHatch();
  void OpenCargo();
  void CloseCargo();
  bool IsHatchToolOpen();
  bool IsCargoToolOpen();
  bool HasCargo();
  bool HasHatch();
  void SetHasCargo(bool hasCargo);
  void SetHasHatch(bool hasHatch);
  bool GetIsLimitSwitchTriggered();
};

#endif //SRC_TOOLCHANGER