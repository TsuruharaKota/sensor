#include<iostream>
#include<pigpiod_if2.h>
#include<chrono>

using std::cout;
using std::endl;

constexpr double resolution = 131.0;
int pi;

//setting
typedef enum{
    MPU_WHO_AM_I 0x75;
    MPU_SET 0x6B;
    MPU_ADDRESS 0x68;
    GYRO_ZOUT_H 0x47;
    GYRO_ZOUT_L 0x48;
}RegisterMap;

int main(){
    //setting i2c
    //get time_now
    //time_diff = time_now - time_prev;
    //get the each data
    //time_prev = time_now
    //calculate the sensor angle(degree);
    //display the result
}

