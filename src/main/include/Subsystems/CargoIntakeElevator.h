#ifndef CARGO_INTAKE_ELEVATOR_H
#define CARGO_INTAKE_ELEVATOR_H

#include <frc/WPILib.h>
#include "ctre/Phoenix.h"
#include "Utils/MotorPositionController.h"
#include "Components/CTREMagEncoder.h"

enum CargoIntakeSlidePositions { // factor of 10 greater to accept doubles
    IN = 0,
    OUT = 230
};

enum ElevatorPositions {
    LOW_HATCH = 60,
    MID_HATCH = 360,
    HIGH_HATCH = 650,
    INTAKE_CARGO = 25,
    LOW_CARGO = 110,
    MID_CARGO = 400,
    HIGH_CARGO = 680
};

class CargoIntakeElevator : public frc::Subsystem {
public:
    CargoIntakeElevator();
    ~CargoIntakeElevator();
    virtual void InitDefaultCommand();
    virtual void Periodic();

    double GetCargoIntakeSlidePosition();
    double GetElevatorPosition();
    
    void CheckIsCargoBeamBreakTriggered();
    bool IsCargoBeamBreakTriggered();
    
    void MoveCargoIntakeSlideToPosition(CargoIntakeSlidePositions refP);
    void MoveElevatorToPosition(ElevatorPositions refP);
    
    double GetCargoIntakeSlideRefPosition();
    double GetElevatorRefPosition();
    
    bool IsCargoIntakeSlideInProtectedZone();
    bool IsElevatorInProtectedZone();
    
    bool IsCargoIntakeSlideOnTarget();
    bool IsElevatorOnTarget();
    
    void ZeroCargoIntakeSlide();
    void ZeroElevator();
    
    void CheckCargoIntakeSlideZeroed();
    void CheckElevatorZeroed();
    
    bool IsCargoIntakeSlideZeroed();
    bool IsElevatorZeroed();
    
    bool IsCargoIntakeSlideConnected();
    bool IsElevatorConnected();
    
    void SetCargoIntakePercent(double percent);
    
    void StopCargoIntakeSlide();
    void StopElevator();
    void StopCargoIntake();

private:
    TalonSRX* m_pCargoIntakeSlideMotor;
    CTREMagEncoder* m_pCargoIntakeSlideEncoder;
    MotorPositionController* m_pCargoIntakeMotorController;
    MotorPositionController* m_pCargoIntakeSlideMotorController;
    TalonSRX* m_pElevatorMasterMotor;
    TalonSRX* m_pElevatorSlaveMotor;
    CTREMagEncoder* m_pElevatorEncoder;
    MotorPositionController* m_pElevatorMotorController;
    VictorSPX* m_pCargoIntakeMotor;
    frc::DigitalInput* m_pCargoIntakeBeamBreak;

    double m_cargoIntakeSlideMinGuard;
    double m_cargoIntakeSlideMaxGuard;
    double m_elevatorMinGuard;
    double m_elevatorMaxGuard;
    double m_cargoIntakeSlideOnTargetThresh;
    double m_elevatorOnTargetThresh;
    bool m_isCargoIntakeSlideZeroed;
    bool m_isElevatorZeroed;
    double m_cargoIntakeSlideRefP;
    double m_elevatorRefP;
    bool m_isCargoBeamBreakTriggered;
    double m_cargoIntakeSlidePulleyRad;
    double m_elevatorPulleyRad;
};

#endif // CARGO_INTAKE_ELEVATOR_H
