#include<iostream>
#include<pigpiod_if2.h>

using std::cout;
using std::endl;

int main(){
    int pi = pigpio_start(0, 0);

