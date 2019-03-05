/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_CLIMBER_H
#define SRC_CLIMBER_H

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <frc/WPILib.h>
#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h"
#include "RobotParameters.h"

class Climber : public frc::Subsystem {
 private:
  rev::CANSparkMax* m_climberMotor;
  rev::CANEncoder* m_encoder;
  frc::DoubleSolenoid* m_climberBigFootSolenoid;
  frc::DoubleSolenoid* m_climberLittleFeetSolenoid;
  frc::DoubleSolenoid* m_climberGuidesSolenoid;
  frc::Solenoid* m_weightsSolenoid;

  rev::CANPIDController m_pidController;
  bool m_littleFeetActivated;
  bool m_bigFootActivated;

 public:
  Climber();
  void InitDefaultCommand() override;
  void Periodic();
  void ClimberRetract();
  void ClimberLevel2();
  void ClimberLevel3();
  double ConvertInchesToTicks(int inches);
  void ActivateLittleFeet();
  void DeactivateLittleFeet();
  void ActivateBigFoot();
  void DeactivateBigFoot();
  bool IsBigFootToggleActivated();
  bool IsLittleFeetToggleActivated();
  void ActivateBigFootToggle();
  void DeactivateBigFootToggle();
  bool IsBigFootTilted();
  void ActivateLittleFeetToggle();
  void DeactivateLittleFeetToggle();
  void SetOpenLoopSpeed(double speed);
  double GetSpeed();
  double GetPos();
  void ZeroClimber();
  void ExtendGuides();
  void RetractGuides();
  void ReleaseWeights();
};

#endif //SRC_CLIMBER_H