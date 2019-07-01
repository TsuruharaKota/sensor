#include<iostream>
#include<pigpiod_if2.h>
#include<chrono>

using std::cout;
using std::endl;
using std::chrono;

constexpr double resolution = 131.0;
int pi;
double degree = 0;
typedef enum{
    MPU_WHO_AM_I = 0x75;
    MPU_SET = 0x6B;
    MPU_SIGNAL = 0x3B;
    MPU_ADDRESS = 0x68;
    GYRO_ZOUT_H = 0x47;
    GYRO_ZOUT_L = 0x48;
}RegisterMap;

int main(){
    int pi = pigpio_start(0, 0);
    RegisterMap set = MPU_SET;
    RegisterMap add = MPU_ADDRESS;
    while(1){
        int handle_data = i2cOpen(pi, device, RegisterMap MPU_ADDRESS, 0);
        i2c_write_byte(pi, handle_data, &MPU_SET, 0x00);
        int16_t gzRaw = i2c_read_byte_data(pi, handle_data, 0X47) << 8 | i2c_read_byte_data(pi, handle_data, 0x48);
        double gyro_z = gzRaw / 131.0;
        auto time_end = system_clock::now();
        auto time_diff = time_end - time_start;
        degree += gyro_z * time_diff
            cout << degree << endl;
        auto time_start = system_clock::now();
    }
    i2c_close(pi, handle_data);
}

