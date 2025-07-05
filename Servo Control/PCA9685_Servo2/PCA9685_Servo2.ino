#include "Servo1.h"        //导入头文件Servo1.h

TwoWire IIC = TwoWire(0);                   //初始化IIC的IO口
Servo1 pwm = Servo1(0x40, IIC);  //实例化pwm

#define S_SCL   33                //定义时钟线的IO口为GPIO33
#define S_SDA   32                //定义数据线的IO口为GPIO32

#define LEG0 0
#define LEG1 1

#define SERVO_FREQ 50

void ServoSetup(){                 
  IIC.begin(S_SDA, S_SCL, 26000000);        //打开IIC通道
  pwm.begin();
  pwm.setOscillatorFrequency(26000000);     
  pwm.setPWMFreq(SERVO_FREQ);      //刷新频率为50Hz
  Wire.setClock(100000);         //修改IIC的时钟频率为100KHz
  delay(10);
}

void setup() {
  ServoSetup();
  pwm.setPWM(1,0,386);       //为防止0号舵机摆动过程被1号舵机阻碍，需先将1号舵机设置到一定的角度给0号舵机预留空间
}

void loop() {
  pwm.setPWM(0,0,86);        //0号舵机摆到0度
  delay(1000);
  pwm.setPWM(0,0,186);        //0号舵机摆到45度
  delay(1000);
  pwm.setPWM(0,0,286);        //0号舵机摆到90度
  delay(1000);
  pwm.setPWM(0,0,386);        //0号舵机摆到135度
  delay(1000);
  pwm.setPWM(0,0,484);        //0号舵机摆到180度
  delay(1000);  
}
