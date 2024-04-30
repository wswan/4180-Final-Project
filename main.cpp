#include "mbed.h"
#include "rtos.h"
#include "motordriver.h"
#include "ultrasonic.h"
#include "wave_player.h"
#include <cmath>

Motor A(p22, p6, p5, 0); // pwm, fwd, rev, can brake 
Motor B(p21, p7, p8, 0); // pwm, fwd, rev, can brake 
RawSerial blue(p28,p27);
Serial pc(USBTX,USBRX);
Mutex mtx;
LocalFileSystem local("local");
AnalogOut DACout(p18);
wave_player waver(&DACout);
PwmOut test1(LED1);
PwmOut test2(LED2);
PwmOut test3(LED3);
PwmOut test4(LED4);
int distance1 = 0;
int distance2 = 0;
FILE* wave_file;

void dist(int distance)
{
    printf("Distance %d mm\r\n", distance);
}

ultrasonic sonar(p12, p13, .1, 1, &dist);

void thread1(void const *args)
{
    char bnum=0;
    char bhit=0;
    while(true) {       // thread loop
        if (blue.readable()) {
            pc.printf("Somebody");
            mtx.lock();
            if (blue.getc()=='!') {
                pc.printf("once");
                if (blue.getc()=='B') { //button data packet
                    pc.printf("told");
                    bnum = blue.getc(); //button number
                    bhit = blue.getc(); //1=hit, 0=release
                    if (blue.getc()==char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                        pc.printf("me");
                        mtx.unlock();
                        switch (bnum) {
                            case '6': //button 5 up arrow
                                pc.printf("the");
                                if (bhit=='1') {
                                    pc.printf("world");
                                    A.speed(0.5);
                                    B.speed(0.5);
                                } else {
                                    A.coast();
                                    B.coast();
                                }
                                break;
                            case '8': //button 6 down arrow
                                if (bhit=='1') {
                                    A.speed(-0.5);
                                    B.speed(-0.5);
                                } else {
                                    A.coast();
                                    B.coast();
                                }
                                break;
                            case '5': //button 7 left arrow
                                if (bhit=='1') {
                                    A.speed(-0.5);
                                    B.speed(0.5);
                                } else {
                                    A.coast();
                                    B.coast();
                                }
                                break;
                            case '7': //button 8 right arrow
                                if (bhit=='1') {
                                    A.speed(0.5);
                                    B.speed(-0.5);
                                } else {
                                    A.coast();
                                    B.coast();
                                }
                                break;
                            default:
                                break;
                        }
                        mtx.lock();
                    }
                }
            }
            mtx.unlock();
        }
    }
}

void thread2(void const *args)
{
    while (1) { 
        test1 = 0;
        test2 = 0;
        test3 = 0;
        test4 = 0;
        wait(0.606);
        test1 = 1;
        test2 = 1;
        test3 = 1;
        test4 = 1;
        wait(0.606);
    }
}
int main() {
    Thread t1(thread1);
    Thread t2(thread2);
    while(1) {
        sonar.startUpdates();//start measuring the distance
        distance1 = sonar.getCurrentDistance();
        pc.printf("Distance %d mm\r\n", distance1);
        wait(0.1);
        distance2 = sonar.getCurrentDistance();
        pc.printf("Distance %d mm\r\n", distance2);
        if (distance1 - distance2 > 500) {
            wait(1);
            wave_file=fopen("/local/hel2.wav","r");
            if(wave_file==NULL) pc.printf("file open error!\n\n\r");
            waver.play(wave_file);
            fclose(wave_file);
        } 
    } 
}
