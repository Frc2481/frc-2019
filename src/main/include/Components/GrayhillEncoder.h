#ifndef GRAYHILL_ENCODER_H
#define GRAYHILL_ENCODER_H

#include <string>
#include "ctre/Phoenix.h"

class GrayhillEncoder {
public:
    GrayhillEncoder(TalonSRX* pTalon, const std::string &name);
    ~GrayhillEncoder();

    void update();
    void zero();
    bool isZeroed() const;
    int getTicks() const;
    int getTickVelocity() const;
    double getRevs() const;
    double getRevVelocity() const;
    double getAngle() const;
    double getWheelDistance(double wheelRadius, double gearRatioEncoderToWheel) const;
    double getWheelVelocity(double wheelRadius, double gearRatioEncoderToWheel) const;
    int convertRevsToTicks(double revs) const;
    int convertRevsToTickSetpoint(double revs) const;
    int convertAngleToTicks(double angle) const;
    int convertAngleToTickSetpoint(double angle) const;
    double convertWheelDistanceToRevs(double wheelRadius,  double wheelDistance) const;
    int convertWheelDistanceToTicks(double wheelRadius, double wheelDistance) const;
    int convertWheelDistanceToTickSetpoint(double wheelRadius, double wheelDistance) const;
    int getZero() const;

private:
    TalonSRX* m_pTalon;
    int m_encoderTicks;
    int m_encoderTicksZero;
    std::string m_name;
    double m_encoderTickVel;
};

#endif // GRAYHILL_ENCODER_H
