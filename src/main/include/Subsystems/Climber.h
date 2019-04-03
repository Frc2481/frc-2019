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
  bool m_isClimberZeroed;
  bool m_areClimberGuidesExtended;
  double m_desiredSetpoint;

 public:
  Climber();
  void InitDefaultCommand() override;
  void Periodic();
  void SetPosition(double setPoint);
  double ConvertInchesToTicks(int inches);
  void ActivateLittleFeet();
  void DeactivateLittleFeet();
  void ActivateBigFoot();
  void DeactivateBigFoot();
  bool IsBigFootToggleActivated();
  bool IsLittleFeetToggleActivated();
  bool IsBigFootTilted();
  void SetOpenLoopSpeed(double speed);
  double GetSpeed();
  double GetSensorSpeed();
  double GetPos();
  double GetDesiredPos();
  void ZeroClimber();
  void ExtendGuides();
  void RetractGuides();
  bool IsGuidesExtended();
  void ReleaseWeights();
  void ResetWeights();
  bool IsClimberZeroed();
  bool IsOnTarget();
};

#endif //SRC_CLIMBER_H