#include "Compass.h"
#include <math.h>

void Compass::quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees) {
float sqr = qr * qr;
float sqi = qi * qi;
float sqj = qj * qj;
float sqk = qk * qk;

  ypr->yaw   = atan2f(2.0f * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
  ypr->pitch = asinf(-2.0f * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
  ypr->roll  = atan2f(2.0f * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));

  if (degrees) {
    ypr->yaw   *= RAD_TO_DEG;
    ypr->pitch *= RAD_TO_DEG;
    ypr->roll  *= RAD_TO_DEG;
  }
}

float Compass::getNorthDirection(float yaw) {
  return (yaw < 0) ? (360.0f + yaw) : yaw;
}

float Compass::ConvertToShownDirection(float AbsDir, int degree_shift) {
  return (float)((int(AbsDir) + degree_shift) % 360);
}

void Compass::quaternionToEulerRV(sh2_RotationVectorWAcc_t* rv, euler_t* ypr, bool degrees) {
  quaternionToEuler(rv->real, rv->i, rv->j, rv->k, ypr, degrees);
}

void Compass::quaternionToEulerGI(sh2_GyroIntegratedRV_t* gi, euler_t* ypr, bool degrees) {
  quaternionToEuler(gi->real, gi->i, gi->j, gi->k, ypr, degrees);
}

void Compass::updateFromSensor(const sh2_SensorValue_t& value) {
  sensorValue_1 = value;
  update_sensor_1 = true;
}

float Compass::getHeading(int degree_shift) {
  if (update_sensor_1) {
    // Choose conversion based on the actual arriving sensorId
    switch (sensorValue_1.sensorId) {
      case SH2_ROTATION_VECTOR:
        quaternionToEulerRV(&sensorValue_1.un.rotationVector, &ypr_1, true);
        break;

      case SH2_GAME_ROTATION_VECTOR: {
        // gameRotationVector has no accuracy field type; use raw components
        const auto& grv = sensorValue_1.un.gameRotationVector;
        quaternionToEuler(grv.real, grv.i, grv.j, grv.k, &ypr_1, true);
        break;
      }

      case SH2_GYRO_INTEGRATED_RV:
        quaternionToEulerGI(&sensorValue_1.un.gyroIntegratedRV, &ypr_1, true);
        break;

      default:
        // leave ypr_1 unchanged
        break;
    }
    update_sensor_1 = false;
  }

  float absDir   = getNorthDirection(ypr_1.yaw);
  float shownDir = ConvertToShownDirection(absDir, degree_shift);
  return shownDir;
}

void Compass::setReports(BNO08x* imu, sh2_SensorId_t rptType, long report_interval) {
  if (!imu->enableReport(rptType, report_interval)) {
    Serial.println("Could not enable report on BNO08x");
  }
}