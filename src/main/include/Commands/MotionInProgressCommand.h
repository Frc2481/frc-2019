/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_MOTIONINPROGRESSCOMMAND
#define SRC_MOTIONINPROGRESSCOMMAND

#include <frc/commands/ConditionalCommand.h>

class MotionInProgressCommand : public frc::ConditionalCommand {
  private:
  Command* m_command;
 public:
  MotionInProgressCommand(Command* command) : ConditionalCommand("MotionInProgressCommand") {
    m_command = command;
  }
  bool Condition() {

  }
};

#endif //SRC_MOTIONINPROGRESSCOMMAND