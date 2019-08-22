#include<iostream>
#include<pigpiod_if2.h>
#include<chrono>
#include<sensor_msgs/Imu.h>

using std::cout;
using std::endl;

//constexpr double resolution = 131.0;
int pi;
double degree_x = 0;
double degree_y = 0;
double degree_z = 0;
/*typedef enum{
  MPU_WHO_AM_I = 0x75;
  MPU_SET = 0x6B;
  MPU_SIGNAL = 0x3B;
  MPU_ADDRESS = 0x68;
  GYRO_ZOUT_H = 0x47;
  GYRO_ZOUT_L = 0x48;
  }RegisterMap;
  */
int main(int argc, char **argv){
    ros::init(argc, argv, "gyro");
    ros::NodeHandle n;
    ros::Publisher gyro_pub = n.advertise<sensor_msgs::Imu>("gyro_info", 10);
    sensor_msgs::Imu imu;
    int pi = pigpio_start(0, 0);
    //  RegisterMap set = MPU_SET;
    //  RegisterMap add = MPU_ADDRESS;
    int handle_datum = i2c_open(pi, 1, 0x68, 0);
    i2c_write_byte_data(pi, handle_datum, 0x6B, 0x00);
    i2c_write_byte_data(pi, handle_datum, 0x1B, 0x00);
    i2c_write_byte_data(pi, handle_datum, 0x1c, 0x00);
    time_sleep(3);
    ros::Rate loop_rate(10);

    while(ros::ok()){
        auto time_start = std::chrono::system_clock::now();

        int16_t axRaw = i2c_read_byte_data(pi, handle_datum, 0X3B) << 8 | i2c_read_byte_data(pi, handle_datum, 0x3C);
        int16_t azRaw = i2c_read_byte_data(pi, handle_datum, 0X3D) << 8 | i2c_read_byte_data(pi, handle_datum, 0x3E);
        int16_t azRaw = i2c_read_byte_data(pi, handle_datum, 0X3F) << 8 | i2c_read_byte_data(pi, handle_datum, 0x40);

        double accel_x = axRaw / 16384;
        double accel_y = ayRaw / 16384;
        double accel_z = azRaw / 16384;

        imu.linear_acceleration_convariance.x = gyro_x;
        imu.linear_acceleration_convariance.y = gyro_y;
        imu.linear_acceleration_convariance.z = gyro_z;

        int16_t gxRaw = i2c_read_byte_data(pi, handle_datum, 0X43) << 8 | i2c_read_byte_data(pi, handle_datum, 0x44);
        int16_t gyRaw = i2c_read_byte_data(pi, handle_datum, 0X45) << 8 | i2c_read_byte_data(pi, handle_datum, 0x46);
        int16_t gzRaw = i2c_read_byte_data(pi, handle_datum, 0X47) << 8 | i2c_read_byte_data(pi, handle_datum, 0x48);

        double gyro_x = gxRaw / 131.0;
        double gyro_y = gyRaw / 131.0;
        double gyro_z = gzRaw / 131.0;

        imu.angular_velocity_convariance.x = gyro_x;
        imu.angular_velocity_convariance.y = gyro_y;
        imu.angular_velocity_convariance.z = gyro_z;

        gyro_pub.publish(imu);

        auto time_end = std::chrono::system_clock::now();
        double time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count();
        degree_x += gyro_x * (time_diff / 1000);
        degree_y += gyro_y * (time_diff / 1000);
        degree_z += gyro_z * (time_diff / 1000);
        cout << degree_x << ", " << degree_y << ", " << degree_z << endl;
        // cout << time_diff / 1000 << endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
    i2c_close(pi, handle_datum);
}

