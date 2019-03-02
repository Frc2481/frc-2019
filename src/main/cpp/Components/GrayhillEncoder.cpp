#include "Components/GrayhillEncoder.h"
#include <frc/WPILib.h>
#include "RobotParameters.h"
#include "Utils/MathConstants.h"
#include "Utils/NormalizeToRange.h"

GrayhillEncoder::GrayhillEncoder(TalonSRX* pTalon, const std::string &name)
	: m_pTalon(pTalon),
    m_encoderTicks(0),
    m_encoderTicksZero(0),
	m_encoderTickVel(0) {

	m_pTalon->SetStatusFramePeriod(Status_2_Feedback0, 10, 10);
}

GrayhillEncoder::~GrayhillEncoder() {
}

void GrayhillEncoder::update() {
    m_encoderTicks = m_pTalon->GetSelectedSensorPosition(0);
    m_encoderTickVel = m_pTalon->GetSelectedSensorVelocity(0);
}

void GrayhillEncoder::zero() {
    m_encoderTicksZero = m_pTalon->GetSelectedSensorPosition(0);
}

bool GrayhillEncoder::isZeroed() const {
    return m_encoderTicksZero != 0;
}

int GrayhillEncoder::getTicks() const {
	return m_encoderTicks - m_encoderTicksZero;
}

int GrayhillEncoder::getTickVelocity() const {
    return m_encoderTickVel * 10; // convert from talon native units
}

double GrayhillEncoder::getRevs() const {
    return getTicks() / (double)RobotParameters::k_grayhillEncoderTicksPerRev;
}

double GrayhillEncoder::getRevVelocity() const {
    return getTickVelocity() / (double)RobotParameters::k_grayhillEncoderTicksPerRev;
}

double GrayhillEncoder::getAngle() const {
    return normalizeToRange::normalizeToRange(std::fmod(getRevs(), 1) * 360.0, -180, 180, true);
}

double GrayhillEncoder::getWheelDistance(double wheelRadius, double gearRatioEncoderToWheel) const {
    return getRevs() * gearRatioEncoderToWheel * wheelRadius * 2.0 * MATH_CONSTANTS_PI;
}

double GrayhillEncoder::getWheelVelocity(double wheelRadius, double gearRatioEncoderToWheel) const {
    return getRevVelocity() * gearRatioEncoderToWheel * wheelRadius * 2.0 * MATH_CONSTANTS_PI;
}

int GrayhillEncoder::convertRevsToTicks(double revs) const {
    return revs * RobotParameters::k_grayhillEncoderTicksPerRev;
}

int GrayhillEncoder::convertRevsToTickSetpoint(double revs) const {
    return convertRevsToTicks(revs) + m_encoderTicksZero;
}

int GrayhillEncoder::convertAngleToTicks(double angle) const {
    return convertRevsToTicks(angle / 360.0);
}

int GrayhillEncoder::convertAngleToTickSetpoint(double angle) const {
    double error = normalizeToRange::rangedDifference(angle - getAngle(), -180, 180);

    return getTicks() + convertAngleToTicks(error) + m_encoderTicksZero;
}

double GrayhillEncoder::convertWheelDistanceToRevs(double wheelRadius, double wheelDistance) const {
    return wheelDistance / (wheelRadius * 2.0 * MATH_CONSTANTS_PI);
}

int GrayhillEncoder::convertWheelDistanceToTicks(double wheelRadius, double wheelDistance) const {
    return convertRevsToTicks(convertWheelDistanceToRevs(wheelRadius, wheelDistance));
}

int GrayhillEncoder::convertWheelDistanceToTickSetpoint(double wheelRadius, double wheelDistance) const {
    return convertWheelDistanceToTicks(wheelRadius, wheelDistance) + m_encoderTicksZero;
}

int GrayhillEncoder::getZero() const {
    return m_encoderTicksZero;
}
