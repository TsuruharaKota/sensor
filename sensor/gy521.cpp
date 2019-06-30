#include<iostream>
#include<pigpiod_if2.h>
#include<chrono>

using std::cout;
using std::endl;
using std::chrono;

constexpr double resolution = 131.0;
int pi;

typedef enum{
    MPU_WHO_AM_I = 0x75;
    MPU_SET = 0x6B;
    MPU_ADDRESS = 0x68;
    GYRO_ZOUT_H = 0x47;
    GYRO_ZOUT_L = 0x48;
}RegisterMap;

int main(){
    //setting i2c
    //open i2c
    namespace setting{
        int handle = i2cOpen(device, RegisterMap MPU_SET, 0);
            if(handle < 0){
                cout << "ERROR: can not open I2C." << endl;
                return -1;
            }
        RegisterMap set = MPU_SET;
        RegisterMap add = MPU_ADDRESS;
        int result = i2ci_write_block_data(handle, set, &add, 1);
        if(result){
            cout << "ERROR: can not set mpu_address." << endl;
            switch(result){
                case PI_BAD_HANDLE:
                    cout << "BAD_HANDLE" << endl;
                    break;
                case PI_BAD_PARAM:
                    cout << "BAD_PARAM" << endl;
                    break;
                case PI_I2C_WRITE_FAILED:
                    cout << "WRITE_FAILED" << endl;
                    break;
                default
                    cout << "UNKNOWN" << endl;
            }
            return -1;
        }
        i2cClose(handle);
    }
    namespace main
    //get time_now
    auto time_start = system_clock::now();
    //get the each data

    //time_prev = time_now
    auto time_end = system_clock::now();
    //time_diff = time_now - time_prev;
    auto time_diff = time_end - time_prev;
    //calculate the sensor angle(degree);
    //display the result
}

