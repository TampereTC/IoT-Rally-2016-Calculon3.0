#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"
#include "Ultrasonic.h"
#include "MPU6050.h"

#define DEBUG true
#define TWO_PI 2 * M_PI
#define INV_RAD 180 / M_PI

Ultrasonic ultrasonic(10, 9);
int distance_sensor;

HMC5883L compass;
int16_t cx, cy, cz;
float forward_orientation;

MPU6050 gyro(0x69);
int16_t ax, ay, az;

int enA = 8;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int enB = 3;
int mspeed = 120;

void setup() {
    Wire.begin();
    delay(1000);
    Serial.begin(38400);

    if (gyro.testConnection()) {
        printMsg("Connected to gyro :)");
    } else {
        printErr("Cannot connect to gyro :(");
    }

    compass.initialize();
    if (compass.testConnection()) {
        printMsg("Connected to compass :)");
        calculate_forward_orientation();
    } else {
        printErr("Cannot connect to compass :(");
    }
}

void calculate_forward_orientation() {
    // Poll for some value in hope to reach a stable one:
    for(int i = 0; i < 5; i++) {
        forward_orientation = getHeading();
        delay(100);
    }
}

void printMsg(char* s) {
    #if DEBUG == true
        Serial.print("MSG: ");
        Serial.println(s);
    #endif
}

void printErr(char* s) {
    #if DEBUG == true
        Serial.print("ERR: ");
        Serial.println(s);
    #endif
}

float getHeading() {
    compass.getHeading(&cx, &cy, &cz);
    float data_in_rads = atan2(cy, cx);
    if (data_in_rads < 0) {
        data_in_rads += (2 * M_PI);
    }
    data_in_rads = data_in_rads * 180 / M_PI;
    return data_in_rads;
}

void driveStraight() {
    float orientation = getHeading() - forward_orientation;
    // +eve => a bit on the left while -eve => a bit on the right
    Serial.print(orientation); Serial.println(" degrees");
    int speedA = mspeed, speedB = mspeed;
    if ((int)orientation > 0) {
        // Turn a bit on the right:
        
    } else {
        // Turn a bit on the left:
    }

    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW); 
    analogWrite(enA, speedA); 
    analogWrite(enB, speedB);
}

void driveBack() {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH); 
    analogWrite(enA, mspeed * 0.8); 
    analogWrite(enB, mspeed * 0.8);
}

void turnRight() {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW); 
    analogWrite(enA, mspeed); 
    analogWrite(enB, mspeed);
}

void stop() {
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, LOW);  
}

void loop() {
    distance_sensor = ultrasonic.Ranging(CM);
    //Serial.print(distance_sensor); Serial.println(" cm");

    if (distance_sensor > 15) {
        driveStraight();
    } else {
        stop();
        delay(500);
        driveBack();
        delay(300);
        stop();
        delay(500);
        turnRight();
    }

    delay(1000);
}
