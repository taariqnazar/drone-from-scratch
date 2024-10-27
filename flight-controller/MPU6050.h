// MPU6050.h
#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

class MPU6050 {
public:
    MPU6050();
    void begin();
    void readSensorData();
    void calibrate();  // Declare the new calibrate method

    float getAccelX();
    float getAccelY();
    float getAccelZ();
    float getGyroX();
    float getGyroY();
    float getGyroZ();

private:
    float accelX, accelY, accelZ;
    float temp;
    float gyroX, gyroY, gyroZ;

    float accelXOffset, accelYOffset, accelZOffset;
    float gyroXOffset, gyroYOffset, gyroZOffset;
};

#endif // MPU6050_H
 
