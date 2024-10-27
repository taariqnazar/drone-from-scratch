#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu;
float rollAcc, pitchAcc;
float rollGyro, pitchGyro;
float roll, pitch, yaw;

float dt, currentTime, previousTime;

void setup() {
    Serial.begin(9600);
    mpu.begin();
    mpu.calibrate();
    delay(250);
}

void loop() {
    // Start Pose Estimate 
    previousTime = currentTime;
    mpu.readSensorData();
    
    currentTime = millis();
    dt = (currentTime - previousTime)/1000.0;
    
    pitchGyro = pitchGyro + dt*mpu.getGyroX();
    rollGyro = rollGyro + dt*mpu.getGyroY();

    pitchAcc = atanf(mpu.getAccelY() / mpu.getAccelZ())*RAD_TO_DEG;
    rollAcc = asinf(mpu.getAccelX())*RAD_TO_DEG;

    pitch = 0.90*pitchGyro + 0.10*pitchAcc;
    roll = 0.90*rollGyro + 0.10*rollAcc;
    Serial.print(pitch);Serial.print("/");Serial.println(roll);
    // End Pose Estimate

    // Start Compute Controll
    // Pitch, Roll, Yaw, Thrust control
    // End Compute Controll

    // Start Motor Mixing
    // End Motor Mixing

    // Start Change Motorspeed
    // End Change Motorspeed
}
