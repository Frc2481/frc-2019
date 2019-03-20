// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #ifndef SRC_CARGOINTAKEBALLCOMMAND
// #define SRC_CARGOINTAKEBALLCOMMAND

// #include <frc/commands/InstantCommand.h>
// #include "CommandBase.h"
// #include "RobotParameters.h"

// class CargoIntakeBallCommand : public frc::InstantCommand {
//   private:
//   double m_speed;
//  public:
//   CargoIntakeBallCommand(double speed) : InstantCommand("CargoIntakeBallCommand") {
//     m_speed = speed;
//   }
//   void Initialize() override {
//     // if(!CommandBase::m_pCargoIntake->IsBallIntaken()) {
//       CommandBase::m_pCargoIntake->SetSpeedIn(m_speed);
//     // }
//     // else {
//     //   CommandBase::m_pCargoIntake->SetSpeedIn(RobotParameters::k_intakeSpeedPartial);
//     // }
//   }
// };

// #endif // SRC_CARGOINTAKEBALLCOMMAND