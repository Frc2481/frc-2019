/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef SRC_LIMELIGHTWAITFORTARGETSEENCOMMAND
#define SRC_LIMELIGHTWAITFORTARGETSEENCOMMAND

#include <frc/commands/Command.h>
#include "CommandBase.h"
#include "networktables/NetworkTableInstance.h"

using namespace nt;

class LimeLightWaitForTargetSeenCommand : public frc::Command {
 private:
  double tv;
  int count;
 public:
  LimeLightWaitForTargetSeenCommand() : Command("LimeLightWaitForTargetSeenCommand"){}
  void Initialize() override{
    count = 0;
  }
  void Execute() override{
    tv = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv",0);
  }
  bool IsFinished() override{
    if(((bool)tv)){
      count++;
    }
    else{
      count = 0;
    }
    return count > 2;
  }
  void End() override{
    
  }
  void Interrupted() override{
    End();
  }
};

class LimeLightWaitForLeftTargetSeenCommand : public frc::Command {
 private:
  double tv;
  double tvPrev;
  double txPrev;
  double tx;
 public:
  LimeLightWaitForLeftTargetSeenCommand() : Command("LimeLightWaitForLeftTargetSeenCommand"){}
  void Initialize() override{
    txPrev = 0.0;
    tv = 0.0;
    tx = 0.0;
    tvPrev = 0.0;
  }
  void Execute() override{
    tx = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0);
    tv = NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0);
  }
  bool IsFinished() override{
    if((bool)tv && (bool)tvPrev && fabs(tx - txPrev) > 10) {
      return true;
    }
    else {
      txPrev = tx;
      tvPrev = tv;
      return false;
    }
  }
  void End() override{
    
  }
  void Interrupted() override{
    End();
  }
};

#endif //SRC_LIMELIGHTWAITFORTARGETSEENCOMMAND