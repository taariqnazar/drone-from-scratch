// MPU6050.cpp
#include "MPU6050.h"

#define MPU6050_ADDR 0x68

MPU6050::MPU6050() : accelXOffset(0), accelYOffset(0), accelZOffset(0),gyroXOffset(0), gyroYOffset(0), gyroZOffset(0) {}

void MPU6050::begin() {
    Wire.begin();
    // DLPF
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x1A);
    Wire.write(0x5);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x1B);
    Wire.write(0x8);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();
}

void MPU6050::readSensorData() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 14, true);

    accelX = (Wire.read() << 8 | Wire.read())/16384.0 - accelXOffset;
    accelY = (Wire.read() << 8 | Wire.read())/16384.0 - accelYOffset;
    accelZ = (Wire.read() << 8 | Wire.read())/16384.0 - accelZOffset;
    temp = Wire.read() << 8 | Wire.read();
    gyroX = (Wire.read() << 8 | Wire.read())/65.5 - gyroXOffset;
    gyroY = (Wire.read() << 8 | Wire.read())/65.5 - gyroYOffset;
    gyroZ = (Wire.read() << 8 | Wire.read())/65.5 - gyroZOffset;
}

void MPU6050::calibrate() {
    float sumAccelX = 0.0, sumAccelY = 0.0, sumAccelZ = 0.0;
    float sumGyroX = 0.0, sumGyroY = 0.0, sumGyroZ = 0.0;
    const int numReadings = 2000;

    // Take multiple readings for calibration
    for (int i = 0; i < numReadings; i++) {
        readSensorData(); // Read the current sensor data
        sumAccelX += accelX;
        sumAccelY += accelY;
        sumAccelZ += accelZ;
        sumGyroX += gyroX;
        sumGyroY += gyroY;
        sumGyroZ += gyroZ;
    }

    // Calculate average offsets
    accelXOffset = sumAccelX / numReadings;
    accelYOffset = sumAccelY / numReadings;
    accelZOffset = sumAccelZ / numReadings - 1; //Account for 1g
    gyroXOffset = sumGyroX / numReadings;
    gyroYOffset = sumGyroY / numReadings;
    gyroZOffset = sumGyroZ / numReadings ;
}

float MPU6050::getAccelX() { return accelX; }
float MPU6050::getAccelY() { return accelY; }
float MPU6050::getAccelZ() { return accelZ; }
float MPU6050::getGyroX() { return gyroX; }
float MPU6050::getGyroY() { return gyroY; }
float MPU6050::getGyroZ() { return gyroZ; }